/*
Assignment 3 - Program 1

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 

Locating edges in a gray-level image 
====================================================================================================================
*/

#include <iostream>
#include <vector>
#include <math.h>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;


// function that multiplies the neighbors of the i,j pixel with its kernel values to find the sobel value for that pixel.
// @return magnitude of the point after performing the sobel operation
double calculateSobel(const int &row, const int &col, const Image& input_image, const vector<vector<int>> kernelX, const vector<vector<int>> kernelY){

  double totalX = 0, totalY = 0;

  // getting the value of pixels from the image
  // input is validated for the edge cases
  int topLeft = (row != 0 && col != 0)? input_image.GetPixel(row-1, col-1): 0;
  totalX += topLeft * kernelX[0][0];
  totalY += topLeft * kernelY[0][0];
  
  int top = row != 0? input_image.GetPixel(row-1, col): 0;
  totalX += top * kernelX[0][1];
  totalY += top * kernelY[0][1];
  

  int topRight = (row != 0 && col != input_image.num_columns()-1)? input_image.GetPixel(row-1, col+1): 0;
  totalX += topRight * kernelX[0][2];
  totalY += topRight * kernelY[0][2];
  
  
  int left = col != 0? input_image.GetPixel(row, col-1): 0;
  totalX += left * kernelX[1][0];
  totalY += left * kernelY[1][0];
  

  int center = input_image.GetPixel(row, col);
  totalX += center * kernelX[1][1];
  totalY += center * kernelY[1][1];
  
  int right = col != input_image.num_columns()-1? input_image.GetPixel(row, col+1): 0;
  totalX += right * kernelX[1][2];
  totalY += right * kernelY[1][2];
  
 
  int bottomLeft = (row != input_image.num_rows()-1 && col != 0)? input_image.GetPixel(row+1, col-1): 0;
  totalX += bottomLeft * kernelX[2][0];
  totalY += bottomLeft * kernelY[2][0];
  

  int bottom = row != input_image.num_rows()-1? input_image.GetPixel(row+1, col): 0;
  totalX += bottom * kernelX[2][1];
  totalY += bottom * kernelY[2][1];
  

  int bottomRight = (row != input_image.num_rows()-1 && col != input_image.num_columns()-1)? input_image.GetPixel(row+1, col+1): 0;
  totalX += bottomRight * kernelX[2][2];
  totalY += bottomRight * kernelY[2][2];
  
  // returning the square root.
  return sqrt(pow(totalX,2) + pow(totalY, 2));
}

/*
 * iterates through the pixels of input image, performs sobel operation and saves the values into imageVec
 */
void calculateImage(const Image& input_image, vector<vector<double>> &imageVec, double& maxVal){

  // kernel for sobel operator, x and y axis
  vector<vector<int>> kernelX = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  vector<vector<int>> kernelY = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
 
  vector<double> currentValue;
  currentValue.reserve(input_image.num_columns());

  for(int i = 0; i < input_image.num_rows(); ++i){  
    for(int j = 0; j < input_image.num_columns(); ++j){            
      
      double labelVal = calculateSobel(i, j, input_image, kernelX, kernelY);
      maxVal = labelVal > maxVal? labelVal: maxVal;
      currentValue.emplace_back(labelVal);
    }
    imageVec.emplace_back(std::move(currentValue));
  }
}

/*
 *  Function that plots the values if imageVec into input_image and normalizes it with the maximum intensity.
 */
void getFinalImage(Image& input_image, vector<vector<double>> imageVec, const double& maxVal){

  for(int i = 0; i < input_image.num_rows(); ++i){
    for(int j = 0; j < input_image.num_columns(); ++j){            
      input_image.SetPixel(i, j, (imageVec[i][j]/maxVal) * 255);
    }
  }
}

/*
 *  Driver function that reads input from cli, performs input validation and calls helper functions for various operations.
 *  Reads and writes images into file.  
 */
int main(int argc, char** argv){

  if(argc != 3){
    cout << "Usage: %s <grey level image> <output grey-level edge image>\n";
    return 0;
  }
  
  // file names for input and output file.
  const string input_file(argv[1]);
  const string output_file(argv[2]);

  // input validation for input file.
  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
      cout <<"Can't open file " << input_file << endl;
      return 0;
  }
  
  double maxVal = 0;
  vector<vector<double>> imageVec;
  imageVec.reserve(an_image.num_rows() * an_image.num_columns());

  calculateImage(an_image, imageVec, maxVal); // x kernel 
  getFinalImage(an_image, imageVec, maxVal);  //final Image

  // saving the processed result to output file.
  if (!WriteImage(output_file, an_image)){
      cout << "Can't write to file " << output_file << endl;
      return 0;
  }

  cout << "Image Manipulation Completed Successfully!\n";
  cout << "==========================================\n";

  return 0;
}