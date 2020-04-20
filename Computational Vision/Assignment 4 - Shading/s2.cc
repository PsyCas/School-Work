#include <iostream>
#include <fstream>
#include <vector>
#include"image.h"

using namespace ComputerVisionProjects;

void findBrightestPoint(std::vector<std::pair<int, int>> &bpDatabase, const Image& image, const int& imageId){  

  bpDatabase.push_back(std::pair<int, int> {0, 0});
  int maxBrightness = -1;

  for(int i = 0; i < image.num_rows(); ++i){
    for(int j = 0; j < image.num_columns(); ++j){            
      
      int pixelValue = image.GetPixel(i, j);
      if( pixelValue != 0 && pixelValue > maxBrightness){
        
        maxBrightness = pixelValue;
        bpDatabase[imageId].first = j; 
        bpDatabase[imageId].second = i; 
      }
    }
  }

  std::cout << "X: " << bpDatabase[imageId].first << " Y: " << bpDatabase[imageId].second << " Brightness: " << maxBrightness << std::endl;
}

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

  std::vector<std::pair<int, int>> bpDatabase;

  Image image_obj_1, image_obj_2, image_obj_3;

  if(!ReadImage(image1, &image_obj_1)){
    std::cout << "Cannot open file " << image1 << std::endl;
    return 0;
  }

  if(!ReadImage(image2, &image_obj_2)){
    std::cout << "Cannot open file " << image2 << std::endl;
    return 0;
  }

  if(!ReadImage(image3, &image_obj_3)){
    std::cout << "Cannot open file " << image1 << std::endl;
    return 0;
  }

  findBrightestPoint(bpDatabase, image_obj_1, 0);
  findBrightestPoint(bpDatabase, image_obj_2, 1);
  findBrightestPoint(bpDatabase, image_obj_3, 2);

  return 0;
}