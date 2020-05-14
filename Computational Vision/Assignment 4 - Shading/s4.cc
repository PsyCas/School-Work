/*
Assignment 4 - Program 4

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 

Program that computes the surface albedo 
====================================================================================================================
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "image.h"
#include "matrixOperations.cc"

using namespace ComputerVisionProjects;


/*
 *  Function that reads in directions from a file and saves it in directionsVec.
 */
void getDirectionsFromFile(std::vector<std::vector<double>> &directionsVec, const std::string& file){

  std::ifstream fin(file);
  if(fin.fail()){
    std::cout << "Could not open file: " << file; 
  } 
  double x, y, z;

  while(fin >> x >> y >> z){
    directionsVec.push_back({x, y, z});
  }
  return;
}


/*
 *  Function that finds the surface albedo. Uses the inverse matrix from directions and the threshold value to calculate the surface albedo
 *  and save it into a vector. The values in the vector are converted to the image pixel values. 
 */
void findAlbedo(const std::vector<std::vector<double>>& inverseVec, const Image& sphere1, const Image& sphere2, const Image& sphere3, Image& output_image, const int&threshold){

  // vector thats stores intensity of three images
  std::vector<double> intensity = {0, 0, 0};

  // vector that stores the final values for the surface albedo
  std::vector<std::vector<double>> outputVec(output_image.num_rows(), (std::vector<double>(output_image.num_columns(), 0)));
  double maxVal = -1;

  for(int i = 0; i < sphere1.num_rows(); ++i){
    for(int j = 0; j < sphere1.num_columns(); ++j){
      
      int sphere1_intensity = sphere1.GetPixel(i, j);
      int sphere2_intensity = sphere2.GetPixel(i, j);
      int sphere3_intensity = sphere3.GetPixel(i, j);

      // process logic if the value is greater than the threshold
      if(sphere1_intensity >= threshold && sphere2_intensity >= threshold && sphere3_intensity >= threshold){
        intensity[0] = sphere1_intensity;
        intensity[1] = sphere2_intensity;
        intensity[2] = sphere3_intensity;

        vector<double> normal = {0, 0 , 0};
        double normScalar = 0;

        // matrix multiplication
        for(int k = 0; k < inverseVec.size(); ++k){
          normal[0] += inverseVec[0][k] * intensity[k]; 
          normal[1] += inverseVec[1][k] * intensity[k]; 
          normal[2] += inverseVec[2][k] * intensity[k]; 
        }

        // calculating magnitude
        for(int k = 0; k < normal.size(); ++k){
          normScalar += pow(normal[k], 2);
        }
        normScalar = sqrt(normScalar);
        outputVec[i][j] = normScalar;
        maxVal = maxVal > normScalar? maxVal: normScalar;
      }
    }
  }

  // plotting the values in the vector to an image
  for(int i = 0; i < sphere1.num_rows(); ++i){
    for(int j = 0; j < sphere1.num_columns(); ++j){
      output_image.SetPixel(i, j, (outputVec[i][j] * 255)/ maxVal);
    }
  }

}

/*
 * Driver function
 * Reads in input from the CLI and does input validation
 * Read in and writes image and file output
 * Makes calls to helper function to perform the assigned tasks. 
 */
int main(int argc, char** argv){

  if(argc != 7){
    std::cout << "Usage: %s <input directions> <image 1> <image 2> <image 3> <step> <threshold> <output>\n" << argv[0] << std::endl;
    return 0;
  }

  //gathering input from the user
  const std::string input_directions(argv[1]);
  const std::string image1(argv[2]);
  const std::string image2(argv[3]);
  const std::string image3(argv[4]);
  const std::string threshold_str(argv[5]);
  const std::string output_image_str(argv[6]);

  int step, threshold;
  try{
    threshold = std::stoi(threshold_str);
  }
  catch(int e){
    std::cout << "Invalid input for threshold or step";
    return 0;
  }

  Image image_obj_1, image_obj_2, image_obj_3, output_image;

  // read in all three images and the needle 
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

  if(!ReadImage(image1, &output_image)){
    std::cout << "Cannot open file " << image1 << std::endl;
    return 0;
  }

  // get directions from input file
  std::vector<std::vector<double>> directionsVec;
  getDirectionsFromFile(directionsVec, input_directions);

  //find inverse
  std::vector<std::vector<double>> inverseVec(directionsVec.size(), std::vector<double>(directionsVec[0].size(), 0));
  inverse(directionsVec, inverseVec, directionsVec.size());
  inverseVec[1][0] *= -1;  
  inverseVec[1][1] *= -1;  
  inverseVec[1][2] *= -1;  

  // main function call to find the surface albedo that is stored in output_image
  findAlbedo(inverseVec, image_obj_1, image_obj_2, image_obj_3, output_image, threshold);

  if(!WriteImage(output_image_str, output_image)){  
    std::cout << "Cannout write to output file." << endl;
    return 0;
  }

  std::cout << "Image manipulation completed successfully" << endl;
  std::cout << "=========================================" << endl;

  return 0;
}