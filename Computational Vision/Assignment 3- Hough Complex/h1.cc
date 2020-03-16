#include <iostream>
#include <vector>
#include <math.h>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

void calculateImage(const Image& input_image, const vector<vector<int>> kernel, Image& return_img){

  for(int i = 0; i < input_image.num_rows(); ++i){
    for(int j = 0; j < input_image.num_columns(); ++j){            
      
      // getting the value of pixels from the image
      int topLeft = (i != 0 && j != 0)? input_image.GetPixel(i-1, j-1): 0;
      int top = i != 0? input_image.GetPixel(i-1, j): 0;
      int topRight = (i != 0 && j != input_image.num_columns()-1)? input_image.GetPixel(i-1, j+1): 0;
      
      int left = j != 0? input_image.GetPixel(i, j-1): 0;
      int center = input_image.GetPixel(i, j);
      int right = j != input_image.num_columns()-1? input_image.GetPixel(i, j+1): 0;
      
      int bottomLeft = (i != input_image.num_rows()-1 && j != 0)? input_image.GetPixel(i+1, j-1): 0;
      int bottom = i != input_image.num_rows()-1? input_image.GetPixel(i+1, j): 0;
      int bottomRight = (i != input_image.num_rows()-1 && j != input_image.num_columns()-1)? input_image.GetPixel(i+1, j+1): 0;

      // multiplying the value of pixels to the kernel
      topLeft = topLeft * kernel[0][0];
      top = top * kernel[0][1]; 
      topRight = topRight * kernel[0][2];

      left = left * kernel[1][0];
      center = center * kernel[1][1];
      right = right * kernel[1][2];

      bottomLeft = bottomLeft * kernel[2][0];
      bottom = bottom * kernel[2][1];
      bottomRight = bottomRight * kernel[2][2];

      int sum = (topLeft + top + topRight + left + center + right + bottomLeft + bottom + bottomRight)/9;
      return_img.SetPixel(i, j, sum);
    }
  }
}

void getFinalImage(Image& input_image, const Image& xImg, const Image& yImg){

    for(int i = 0; i < input_image.num_rows(); ++i){
      for(int j = 0; j < input_image.num_columns(); ++j){            
        int value = round(sqrt(pow(xImg.GetPixel(i,j),2) + pow(yImg.GetPixel(i,j),2))); // newPixel = sqrt(xPxl^2 + ypxl^2)
        input_image.SetPixel(i, j, value);
      }
    }
}


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
  
  
  // kernel for sobel operator, x and y axis
  // vector<vector<int>> kernelX = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  // vector<vector<int>> kernelY = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
  vector<vector<int>> kernelX = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

  Image xImg, yImg;
  if (!ReadImage(input_file, &xImg)) {
      cout <<"Can't open file " << input_file << endl;
      return 0;
  }
  if (!ReadImage(input_file, &yImg)) {
      cout <<"Can't open file " << input_file << endl;
      return 0;
  }

  calculateImage(an_image, kernelX, xImg); // x kernel 
  // calculateImage(an_image, kernelY, yImg); // y kernel
  
  // getFinalImage(an_image, xImg, yImg);  //final Image

  /*
  // saving the processed result to output file.
  if (!WriteImage("Ximg.pgm", xImg)){
      cout << "Can't write to file " << output_file << endl;
      return 0;
  }

  // saving the processed result to output file.
  if (!WriteImage("Yimg.pgm", yImg)){
      cout << "Can't write to file " << output_file << endl;
      return 0;
  }*/

  // saving the processed result to output file.
  if (!WriteImage(output_file, xImg)){
      cout << "Can't write to file " << output_file << endl;
      return 0;
  }

  cout << "Image Manipulation Completed Successfully!\n";
  cout << "==========================================\n";


  return 0;
}