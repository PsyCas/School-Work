#include <iostream>
#include <vector>
#include <fstream>
#include "image.h"

using namespace ComputerVisionProjects;

void getDirectionsFromFile(std::vector<std::vector<double>> &directionsVec, const string& file){

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
  const std::string step(argv[5]);
  const std::string threshold(argv[6]);
  const std::string output_image(argv[7]);

  Image image_obj_1, image_obj_2, image_obj_3, needle_image;

  // read in all three images and the needle 
  if(!ReadImage(image1, &image_obj_1)){
    std::cout << "Cannot open file " << image1 << std::endl;
    return 0;
  }

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

  std::vector<std::vector<double>> directionsVec;
  getDirectionsFromFile(directionsVec, input_directions);
  std::vector<std::vector<double>> inverseVec(directionsVec.size(), std::vector<double>(directionsVec[0].size(), 0));
  

  return 0;
}