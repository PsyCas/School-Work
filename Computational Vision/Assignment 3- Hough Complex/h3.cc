#include <iostream>
#include <vector>
#include <math.h>
#include "image.h"

#define PI 3.14159265
const double DEG_TO_RAD = 180/PI;

using namespace std;
using namespace ComputerVisionProjects;

void drawImageWithThreshold(Image& output_image,  vector<vector<int>> accumulator, const int& threshold){

  for(int i = 0; i < accumulator.size(); ++i){
    for(int j= 0; j < accumulator[i].size(); ++j){
      if(accumulator[i][j] >= threshold && i < output_image.num_rows() && j < output_image.num_columns()){
        output_image.SetPixel(i, j, accumulator[i][j]>255? 255: accumulator[i][j]);
        // cout << "here" << " " << accumulator[i][j] << endl;
      }
    }
  }
}

void createHoughImage(Image& input_image, Image& output_image){

  int h = input_image.num_rows(), w = input_image.num_columns();
  int acc_thetaVal = 180;
  int acc_rhoVal = sqrt(2.0) * (h>w? h : w);

  //remove later
  cout << acc_rhoVal << endl;

  int center_row = h/2, center_col = w/2;

  // creating accumulator dataset
  vector<vector<int>> accumulator(acc_rhoVal, vector<int> (acc_thetaVal, 0));

  for(int i = 0; i < h; ++i){
    for(int j = 0; j < w; ++j){
      int pixel = input_image.GetPixel(i, j);
      
      // prepare the output image to turn it into a hough greyscale image
      output_image.SetPixel(i, j, 0);

      //hough transform logic
      if(pixel == 255){
        
        for(int k = 0; k < 180; ++k){         
          int r = round(((i - center_row) * sin(k * DEG_TO_RAD)) + ((j - center_col) * cos(k * DEG_TO_RAD)));

          // cout << 905/2 + r << endl;
          // r = abs(r);
          r = r + acc_rhoVal/2;
          if(r <= acc_rhoVal){
            accumulator[r][k] = accumulator[r][k]+ 1;
          }
        }
      }
    }
  }

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

  createHoughImage(an_image, hough_image);

  if(!WriteImage(output_file, hough_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }

  cout << "Image manipulation Completed Successfully!\n";
  cout << "==========================================\n";

  return 0;
}