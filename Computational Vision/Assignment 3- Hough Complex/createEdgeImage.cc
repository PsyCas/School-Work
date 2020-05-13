#include <iostream>
#include <vector>
#include <math.h>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

void createBinaryImage(Image& input_image, int threshold){
  for(int i = 0; i < input_image.num_rows(); ++i){
        for(int j = 0; j < input_image.num_columns(); ++j){            
            input_image.GetPixel(i,j) > threshold? input_image.SetPixel(i, j, 255): input_image.SetPixel(i, j, 0); 
        }
    }
}

double calculateSobel(const int &row, const int &col, const Image& input_image, const vector<vector<int>> kernelX, const vector<vector<int>> kernelY){

  double totalX = 0, totalY = 0;

  // getting the value of pixels from the image
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
  
  return sqrt(pow(totalX,2) + pow(totalY, 2));
}

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

void getFinalImage(Image& input_image, vector<vector<double>> imageVec, const double& maxVal){

  for(int i = 0; i < input_image.num_rows(); ++i){
    for(int j = 0; j < input_image.num_columns(); ++j){            
      input_image.SetPixel(i, j, (imageVec[i][j]/maxVal) * 255);
    }
  }
}