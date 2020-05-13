/*
Assignment 3 - Program 4

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 

Program that locates the lines in the original image using its hough transformation.
====================================================================================================================
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "image.h"
#include "labelImages.cc"
#include "createEdgeImage.cc"

using namespace std;
using namespace ComputerVisionProjects;

// setting the value of PI
const double PI = 3.14159265358979323846;


// if index exists for label in the dataset, return index
// else return -1
int getIndexFromLabel(const vector<vector<double>> &databaseVec, const int &pixel){

    for(int i = 0; i < databaseVec.size(); ++i){
        if(databaseVec[i][0] == pixel) return i; 
    }
    return -1;
}

// called if label does not exist in dataset. Creates label and returns its index.
int createIndexForLabel(vector<vector<double>> &databaseVec, const int &pixel){
    double temp = pixel;
    databaseVec.push_back(vector<double> {temp, 0, 0, 0, 0, 0, 0, 0, 0});
    return databaseVec.size()-1;
}

// helper function that finds the center of the givem image. 
void findCenter(const Image& inputImage, const Image& originalImage, vector<vector<double>> &databaseVec){
  for(int i = 0; i < inputImage.num_rows(); ++i){
    for(int j = 0; j < inputImage.num_columns(); ++j){

      int pixel = inputImage.GetPixel(i, j);
      if(pixel != 0){
        int originalValue = originalImage.GetPixel(i, j);  
        int index = getIndexFromLabel(databaseVec, pixel);
        index = index == -1? createIndexForLabel(databaseVec, pixel): index;

        databaseVec[index][1] += 1 * originalValue; // area
        databaseVec[index][2] += i * originalValue; // row
        databaseVec[index][3] += j * originalValue; // column
      }                     
    }
  }
  // computing the centers by dividing with area
  for(int i = 0; i < databaseVec.size(); ++i){
      databaseVec[i][2] = databaseVec[i][2]/ databaseVec[i][1];
      databaseVec[i][3] = databaseVec[i][3]/ databaseVec[i][1];
  }
  return;
}

/*
 * Function that creates the hough transformation using the voting array and the threshold
 * @return Image that consists of the hough transformation.  
 */
Image* drawImage(const vector<vector<double>> &accumulator, const int& threshold){

  // creating and allocation output image object
  Image *output_image = new Image();
  output_image -> AllocateSpaceAndSetSize(accumulator.size(), accumulator[0].size());
  output_image -> SetNumberGrayLevels(255);

  // writing the values of each pixel into the final image
  for(int i = 0; i < accumulator.size(); ++i){
    for(int j= 0; j < accumulator[i].size(); ++j){
      output_image -> SetPixel(i, j, (int)( accumulator[i][j]> threshold? accumulator[i][j]: 0));
    }
  }

  // return final image
  return output_image;
}

/*
 *  Function that reads in the file for the voting array and saves them into the accumulator vector
 */
void importAccumulator(const string& file, vector<vector<double>>& accumulator){

  // create ifstream object
  ifstream fin(file);
  // error handling
  if(fin.fail()){
    cout << "Failed to open file: " << file <<  endl;
    return;
  }

  string rhoLabel, thetaLabel, voteLabel;
  double rhoVal, thetaVal, voteVal, previousVal = -1;

  // read in each value which exists in the following form.
  while(fin >> rhoLabel >> rhoVal >> thetaLabel >> thetaVal >> voteLabel >> voteVal){
    if(previousVal < rhoVal){
      previousVal = rhoVal;
      accumulator.push_back(vector<double> {});
    }
    accumulator[rhoVal].push_back(voteVal);
  }

  // close file object
  fin.close();
}

/*
 * Function that merges the original image with the line image to get the final output image  
 */
void mergeOriginalImage(Image& input_image, const Image& output){

  //iterating through the image and changing the pixel value if the edge is 255.
  for(int i = 0; i < output.num_rows(); ++i){
    for(int j = 0; j < output.num_columns(); ++j){
      if(output.GetPixel(i, j) == 255){
        input_image.SetPixel(i, j, 255);
      }
    }
  }
}

/*
 * Driver function
 * Reads in input from the CLI and does input validation
 * Read in and writes image and file output
 * Makes calls to helper function to perform the assigned tasks. 
 */
int main(int argc, char **argv){

  if(argc != 5){
    cout << "Usage: %s <input original image> <input hough voting array> <input Hough threshold value> <output line image>\n";
    return 0;
  }

  const string input_original_image(argv[1]);
  const string input_hough_array(argv[2]);
  const string input_hough_threshold(argv[3]);
  const string output_line_image(argv[4]);

  //input validation for threshold
  int thresholdVal; 
  try{
    thresholdVal = stoi(input_hough_threshold);
  }
  catch(int err){ 
    cout << "Invalid Threshold Value";
    return 0;
  }

  // create image objects
  Image input_image, copy_image;  

  // read images from input file
  if(!ReadImage(input_original_image, &input_image) || !ReadImage(input_original_image, &copy_image)){
    cout << "Can't open the input image " << input_original_image << endl;
    return 0;
  }

  // create and populate accumulator vector from file.
  vector<vector<double>> accumulator;
  importAccumulator(input_hough_array, accumulator);
  
  // get hough image and its copy
  Image *inputHough = drawImage(accumulator, thresholdVal);
  Image *inputHoughCopy = drawImage(accumulator, thresholdVal);

  // perform labeling
  sequentialLabeling(*inputHoughCopy);  

  // create vector to store center and area of objects
  vector<vector<double>> databaseVec;
  findCenter(*inputHoughCopy, *inputHough, databaseVec);

  // use the hough transform to create the edge images.
  double maxVal = 0;
  vector<vector<double>> imageVec;
  imageVec.reserve(copy_image.num_rows() * copy_image.num_columns());
  calculateImage(copy_image, imageVec, maxVal); 
  getFinalImage(copy_image, imageVec, maxVal);  //final Image
  
  // convert the image to binary
  createBinaryImage(copy_image, 21);

  // merge it with the original image
  mergeOriginalImage(input_image, copy_image);

  // write the image to the file
  if(!WriteImage(output_line_image, input_image)){
    cout << "Can't write to file " << output_line_image << endl;
    return 0;
  }

  cout << "Image manipulation Completed Successfully!\n";
  cout << "==========================================\n";

  return 0;
}