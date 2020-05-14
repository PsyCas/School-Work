/*
Assignment 4 - Program 2

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 

Computing the directions and intenstities of light sources.
====================================================================================================================
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include"image.h"

using namespace ComputerVisionProjects;

/*
 * Function that finds the normals and saves it in the vector normalDatabase
 */
void findNormal(std::vector<std::vector<double>> &normalDatabase, const std::vector<std::vector<int>> &bpDatabase, const std::string& input_param_file){

  // get center and radius from file
  int centerX, centerY, radius;
  std::ifstream fin(input_param_file);
  fin >> centerX >> centerY >> radius;
  fin.close();

  std::cout << centerX << " " << centerY << " " << radius << std::endl;

  for(int i = 0; i < 3; ++i){

    normalDatabase.push_back(std::vector<double> {0, 0, 0});

    // this was written out by hand and coded in
    double nx = (bpDatabase[i][0] - centerX)/sqrt(-1 * pow(bpDatabase[i][0] - centerX, 2) - pow(bpDatabase[i][1] - centerY, 2) + pow(radius, 2));
    double ny = -(bpDatabase[i][1] - centerY)/sqrt(-1 * pow(bpDatabase[i][0] - centerX, 2) - pow(bpDatabase[i][1] - centerY, 2) + pow(radius, 2));
    double nz = sqrt(pow(nx, 2) + pow(ny, 2) + 1); 

    normalDatabase[i] = {(nx/nz)*bpDatabase[i][2], (ny/nz)*bpDatabase[i][2], (1/nz)*bpDatabase[i][2]};  
  }  
}

/*
 *  Functon that finds the brigtest point in an image and saves it in the bpDatabase wrt to ID 
 */
void findBrightestPoint(std::vector<std::vector<int>> &bpDatabase, const Image& image, const int& imageId){  

  bpDatabase.push_back(std::vector<int> {0, 0, 0});
  int maxBrightness = -1;

  // going through every pixel in the image
  for(int i = 0; i < image.num_rows(); ++i){
    for(int j = 0; j < image.num_columns(); ++j){            
      
      int pixelValue = image.GetPixel(i, j);
      if( pixelValue != 0 && pixelValue > maxBrightness){
        
        maxBrightness = pixelValue;
        bpDatabase[imageId][0] = j; 
        bpDatabase[imageId][1] = i; 
      }
    }
  }
  bpDatabase[imageId][2] = maxBrightness;
}


/*
 * Driver function
 * Reads in input from the CLI and does input validation
 * Read in and writes image and file output
 * Makes calls to helper function to perform the assigned tasks. 
 */
int main(int argc, char** argv){

  if(argc != 6){
    std::cout << "Usage: %s <input parameters file> <image 1> <image 2> <image 3> <output directions file>\n" << argv[0] << std::endl;
    return 0;
  }

  //gathering input from the user
  const std::string input_param_file(argv[1]);
  const std::string image1(argv[2]);
  const std::string image2(argv[3]);
  const std::string image3(argv[4]);
  const std::string output_file(argv[5]);

  // vector that stores the brightests points for all three images
  std::vector<std::vector<int>> bpDatabase;

  // creating image objects
  Image image_obj_1, image_obj_2, image_obj_3;

  // read in all three images
  if(!ReadImage(image1, &image_obj_1)){
    std::cout << "Cannot open file " << image1 << std::endl;
    return 0;
  }

  if(!ReadImage(image2, &image_obj_2)){
    std::cout << "Cannot open file " << image2 << std::endl;
    return 0;
  }

  if(!ReadImage(image3, &image_obj_3)){
    std::cout << "Cannot open file " << image3 << std::endl;
    return 0;
  }

  //find brightest point for all three images
  findBrightestPoint(bpDatabase, image_obj_1, 0);
  findBrightestPoint(bpDatabase, image_obj_2, 1);
  findBrightestPoint(bpDatabase, image_obj_3, 2);

  //find the normal for all three images
  std::vector<std::vector<double>> normalDatabase;
  
  //finding the normals
  findNormal(normalDatabase, bpDatabase, input_param_file); 
  
  // opening file for writing the value of normals
  std::ofstream fout(output_file);
  if(fout.fail()){
    std::cout << "Cannot open file " << output_file << std::endl;
    return 0;
  }

  //writing to file.
  for(int i = 0; i < 3; ++i){
    fout << normalDatabase[i][0] << " " << normalDatabase[i][1] << " " << normalDatabase[i][2] << "\n";
  }
  fout.close(); 
 
  return 0;
}