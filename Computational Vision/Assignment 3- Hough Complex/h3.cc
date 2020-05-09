#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "image.h"

const double PI = 3.14159265358979323846;

using namespace std;
using namespace ComputerVisionProjects;

void createOutputVotingArray(vector<vector<double>> accumulator, const string& output_file){

  ofstream fout(output_file);

  for(int i = 0; i < accumulator.size(); ++i){
    for(int j= 0; j < accumulator[i].size(); ++j){
      fout << "p: " << i << ", t: " << j << ", votes: " << accumulator[i][j] << "\n";
    }
  }
  fout.close();
}

void drawImageWithThreshold(Image& output_image,  vector<vector<double>> accumulator, const int& threshold){

  output_image.AllocateSpaceAndSetSize(accumulator.size(), accumulator[0].size());
  output_image.SetNumberGrayLevels(255);

  for(int i = 0; i < accumulator.size(); ++i){
    for(int j= 0; j < accumulator[i].size(); ++j){
      // if(accumulator[i][j] >= threshold && i < output_image.num_rows() && j < output_image.num_columns()){
        output_image.SetPixel(i, j, (int)(accumulator[i][j]>255? 255: accumulator[i][j]));
      // }
    }
  }
}

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

  // cout << "thetamin" << acc_thetaMin << endl;
  // cout << "thetamax" << acc_thetaMax << endl;
  // cout << "rhoMin" << acc_rhoMin << endl;
  // cout << "rhoMax" << acc_rhoMax << endl;

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
          
          double thetaVal = acc_thetaMin + k * (acc_thetaMax - acc_thetaMin) / acc_thetaVal;
          double r = j * std::sin(thetaVal) + i * std::cos(thetaVal);

          r = (r - acc_rhoMin) * acc_rhoVal / (acc_rhoMax - acc_rhoMin);
          
          accumulator[(int)r][k] = accumulator[(int)r][k] + 1;
          maxVal = accumulator[(int)r][k] > maxVal? accumulator[(int)r][k]: maxVal; 
        }
      }
    }
  }

  for(int i = 0; i < accumulator.size(); ++i){
    for(int j = 0; j < accumulator[i].size(); ++j){
      accumulator[i][j] *= 255 / maxVal;
    }
  }

  createOutputVotingArray(accumulator, output_array);
  drawImageWithThreshold(output_image, accumulator, 80);      

  return;
}



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

  createHoughImage(an_image, hough_image, output_array);

  if(!WriteImage(output_file, hough_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }

  cout << "Image manipulation Completed Successfully!\n";
  cout << "==========================================\n";

  return 0;
}