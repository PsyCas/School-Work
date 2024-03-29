/*
Assignment 4 - Program 1

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 

Program that locates a spheres location and computes its center and radius
====================================================================================================================
*/

#include <iostream>
#include <vector>
#include <fstream>
#include "binaryImages.h"
#include "image.h"

using namespace std;

/*
 * Function that calculates the center of an image and stores it in the center vector
 */
void findCenter(const Image &an_image, vector<int> &center){
  int area = 0;

  for(int i = 0; i < an_image.num_rows(); ++i){
    for(int j = 0; j < an_image.num_columns(); ++j){

      if(an_image.GetPixel(i, j) != 0){
        area++;
        center[0] += i;
        center[1] += j;
      }

    } // j
  } //i
  
  center[0] = center[0]/area;
  center[1] = center[1]/area;
}

/*
 *  Function that calculates the radius of an image using its center.
 *  @return radius value
 */
int findRadius(const Image &an_image, vector<int> center){

  int radius = 0, avgRow = 0, avgCol = 0;

  // get the average value for the row
  for(int i = 0; i < an_image.num_rows(); ++i){
    if(an_image.GetPixel(i, center[1]) != 0){
      avgRow++;
    }
  }

  // get the average value for the column
  for(int i = 0; i < an_image.num_columns(); ++i){
    if(an_image.GetPixel(center[0], i) != 0){
      avgCol++;
    }
  }

  // div by 2 for average, div by 2 again to convert diameter to radius
  radius = (avgRow+avgCol)/4; 

  return radius;
}


/*
 * Driver function
 * Reads in input from the CLI and does input validation
 * Read in and writes image and file output
 * Makes calls to helper function to perform the assigned tasks. 
 */
int main(int argc, char** argv){

  if (argc!=4) {
        cout << "Usage: %s <input image> <grey threshold value> <output parameters file>\n" << argv[0] << endl;
        return 0;
    }

    // input validation for threshold.
    int gray_level_threshold; 
    
    try{
       gray_level_threshold = std::stoi(argv[2]);
    }
    catch (std::invalid_argument const &e){
        cerr << "Invalid value for threshold." << endl;
        return 0;
    }
    catch (std::out_of_range const &e){
        cerr << "Value for threshold out of range" << endl;
        return 0;
    }
    if(gray_level_threshold < 0 || gray_level_threshold > 255){
        cout << "Invalid threshold. The values should range between 0-255 inclusive." << endl;
        return 0;
    }

    // file names for input and output file.
    const string input_file(argv[1]);
    const string output_file(argv[3]);

    Image *binary_image;  //pointer to binary image object
    BinaryImage anImage(input_file);
    anImage.convertToBinary(gray_level_threshold);
    binary_image = anImage.getOutputImage();

    vector<int> center{0, 0};
    findCenter(*binary_image, center);

    int radius = findRadius(*binary_image, center);

    cout  << "X: " << center[1] << " " 
          << "Y: " << center[0] << " " 
          << "\nRadius: " << radius << endl << endl;

    //writing to file    
    ofstream out(output_file);
    out << center[1] << " " << center[0] << " " << radius << endl;
    out.close();
    
    cout << "File Successfully Written!\n";
    cout << "==========================================\n";
}