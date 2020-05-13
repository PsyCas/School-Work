/*
Assignment 3 - Program 3

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 

Program that implements the hough transform for an input image
====================================================================================================================
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "image.h"

// setting the value of PI
const double PI = 3.14159265358979323846;

using namespace std;
using namespace ComputerVisionProjects;

/*
 *  Writes the values stored in the output voting array into a text file. 
 */
void createOutputVotingArray(vector<vector<double>> accumulator, const string& output_file){

  // creating ofstream object
  ofstream fout(output_file);
  if(fout.fail()){
    cout << "Failed to open file: " << output_file <<  endl;
    return;
  }

  // writing the values of the voting array to file
  for(int i = 0; i < accumulator.size(); ++i){
    for(int j= 0; j < accumulator[i].size(); ++j){
      fout << "rho: " << i << " theta: " << j << " votes: " << accumulator[i][j] << "\n";
    }
  }

  // closing fout object
  fout.close();
}

/*
 *  Uses the voting array to update the values of pixel in the final output image. 
 */
void drawImage(Image& output_image, vector<vector<double>> accumulator){

  output_image.AllocateSpaceAndSetSize(accumulator.size(), accumulator[0].size());
  output_image.SetNumberGrayLevels(255);

  // setting the value of evey individual pixel
  for(int i = 0; i < accumulator.size(); ++i){
    for(int j= 0; j < accumulator[i].size(); ++j){
        output_image.SetPixel(i, j, (int)(accumulator[i][j]>255? 255: accumulator[i][j]));
    }
  }
}

/*
 *  Function that craetes the voting array that is required to get the hough image
 */
void createHoughImage(Image& input_image, Image& output_image, const string& output_array){

  int h = input_image.num_rows(), w = input_image.num_columns();
  double limitVal = sqrt(pow(h, 2) + pow(w, 2));

  double acc_thetaMin = 0;
  double acc_thetaMax = PI;

  double acc_rhoMin = limitVal * -1;
  double acc_rhoMax = limitVal;

  //modify value to change the output of the hough image. Default set to size of image  
  int acc_rhoVal = h;
  int acc_thetaVal = w;

  // int acc_rhoVal = sqrt(2.0) * (h>w? h : w);
  // int acc_thetaVal = 180;

  double maxVal = 1;

  // creating accumulator dataset
  vector<vector<double>> accumulator(acc_rhoVal, vector<double> (acc_thetaVal, 0));

  for(int i = 0; i < h; ++i){
    for(int j = 0; j < w; ++j){
      int pixel = input_image.GetPixel(i, j);
      
      // prepare the output image to turn it into a hough greyscale image
      output_image.SetPixel(i, j, 0);

      //hough transform logic
      if(pixel > 0){
        
        for(int k = 0; k < acc_thetaVal; ++k){
          
          // setting values of theta and rho
          double thetaVal = acc_thetaMin + k * (acc_thetaMax - acc_thetaMin) / acc_thetaVal;
          double r = j * std::sin(thetaVal) + i * std::cos(thetaVal);

          r = (r - acc_rhoMin) * acc_rhoVal / (acc_rhoMax - acc_rhoMin);
          
          accumulator[(int)r][k] = accumulator[(int)r][k] + 1;
          maxVal = accumulator[(int)r][k] > maxVal? accumulator[(int)r][k]: maxVal; 
        }
      }
    }
  }

  // normalizing the values in the accumluator vector
  for(int i = 0; i < accumulator.size(); ++i){
    for(int j = 0; j < accumulator[i].size(); ++j){
      accumulator[i][j] *= 255 / maxVal;
    }
  }

  createOutputVotingArray(accumulator, output_array); 
  drawImage(output_image, accumulator);      

  return;
}


/*
 * Driver function
 * Reads in input from the CLI and does input validation
 * Read in and writes image and file output
 * Makes calls to helper function to perform the assigned tasks. 
 */
int main(int argc, char **argv){

  if(argc != 4){
    cout << "Usage: %s <input binary image> <grey level hough image> <output Hough voting array>\n";
    return 0;
  }

  const string input_file(argv[1]);
  const string output_file(argv[2]);
  const string output_array(argv[3]);

  Image an_image, hough_image;
  // read image for both an_image and hough image
  if(!ReadImage(input_file, &an_image) || !ReadImage(input_file, &hough_image)){
    cout << "Can't open file " << input_file << endl;
    return 0;
  }

  // helper function that transform an_image to hough image and stores it in hough_image
  createHoughImage(an_image, hough_image, output_array);

  if(!WriteImage(output_file, hough_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }

  cout << "Image manipulation Completed Successfully!\n";
  cout << "==========================================\n";

  return 0;
}