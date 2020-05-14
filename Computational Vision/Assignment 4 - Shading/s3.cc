/*
Assignment 4 - Program 3

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 
 
Program that computes the surface normals and creates a needle map image.
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
 *
 */
void createNeedleImage(const std::vector<std::vector<double>>& inverseVec, const Image& sphere1, const Image& sphere2, const Image& sphere3, Image& needle_image, const int&threshold, const int& step){

  // vector that stores the intensity for the three images
  std::vector<double> intensity = {-1, -1, -1};

  for(int i = 0; i < sphere1.num_rows(); i += step){
    for(int j = 0; j < sphere1.num_columns(); j += step){
      
      int sphere1_intensity = sphere1.GetPixel(i, j);
      int sphere2_intensity = sphere2.GetPixel(i, j);
      int sphere3_intensity = sphere3.GetPixel(i, j);

      // only process logic if all the intensities are greater than the threshold 
      if(sphere1_intensity >= threshold && sphere2_intensity >= threshold && sphere3_intensity >= threshold){
        intensity[0] = sphere1_intensity;
        intensity[1] = sphere2_intensity;
        intensity[2] = sphere3_intensity;

        // vector that stores the normal
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
        
        // calculating orientation 
        for(int k = 0; k < normal.size(); ++k){
          normal[k] /= normScalar;
        }

        // creating the circle 
				needle_image.SetPixel(i - 1, j, 255);
				needle_image.SetPixel(i, j - 1, 255);
				needle_image.SetPixel(i + 1, j, 255);
				needle_image.SetPixel(i, j + 1, 255);

        // drawing the line with respect to the normal
        DrawLine(i, j, i + normal[1] *10, j + normal[0] * 10, 255, &needle_image);
        needle_image.SetPixel(i, j, 0);
      }
    }
  }

}


/*
 *  Read file input and save the directions into directionsVec
 */
void getDirectionsFromFile(std::vector<std::vector<double>> &directionsVec, const std::string& file){

  // read file with ifstream object
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
 * Driver function
 * Reads in input from the CLI and does input validation
 * Read in and writes image and file output
 * Makes calls to helper function to perform the assigned tasks. 
 */
int main(int argc, char** argv){

  if(argc != 8){
    std::cout << "Usage: %s <input directions> <image 1> <image 2> <image 3> <step> <threshold> <output>\n" << argv[0] << std::endl;
    return 0;
  }

  //gathering input from the user
  const std::string input_directions(argv[1]);
  const std::string image1(argv[2]);
  const std::string image2(argv[3]);
  const std::string image3(argv[4]);
  const std::string step_str(argv[5]);
  const std::string threshold_str(argv[6]);
  const std::string output_image(argv[7]);

  // input validation for the step and threshold 
  int step, threshold;
  try{
    step = std::stoi(step_str);
    threshold = std::stoi(threshold_str);
  }
  catch(int e){
    std::cout << "Invalid input for threshold or step";
    return 0;
  }

  // creating Image object
  Image image_obj_1, image_obj_2, image_obj_3, needle_image;

  // read in all three images and the needle 
  if(!ReadImage(image1, &image_obj_1)){
    std::cout << "Cannot open file " << image1 << std::endl;
    return 0;
  }

  // duplicate to create needle image on
  if(!ReadImage(image1, &needle_image)){
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

  //vector that stores directions from the file
  std::vector<std::vector<double>> directionsVec;
  getDirectionsFromFile(directionsVec, input_directions);
  
  // vector that stores the inverse matrix of the directions.
  std::vector<std::vector<double>> inverseVec(directionsVec.size(), std::vector<double>(directionsVec[0].size(), 0));
  inverse(directionsVec, inverseVec, directionsVec.size());
  inverseVec[1][0] *= -1;  
  inverseVec[1][1] *= -1;  
  inverseVec[1][2] *= -1;  
  
  // creating the needle image
  createNeedleImage(inverseVec, image_obj_1, image_obj_2, image_obj_3, needle_image, threshold, step);

  // writing the image to file
  if(!WriteImage(output_image, needle_image)){  
    std::cout << "Cannout write to output file." << endl;
    return 0;
  }

  std::cout << "Image manipulation completed successfully" << endl;
  std::cout << "=========================================" << endl;

  return 0;
}