#include "binaryImages.h"
#include <iostream>
#include <string>

BinaryImage::BinaryImage(const std::string& input_file){
  if(!ReadImage(input_file, &input_image)){
    std::cout << "Can't open file " << input_file << std::endl;
    abort();
  }
  else{
    ReadImage(input_file, &output_image);
  }
}

bool BinaryImage::setImage(const std::string& input_file){
  if(!ReadImage(input_file, &input_image)){
    return false;
  }
  else{
    ReadImage(input_file, &output_image);
    return true;
  }
}
    
Image* BinaryImage::getOutputImage(){
  Image *output_pointer = &output_image;
  return output_pointer;
}
    
void BinaryImage::convertToBinary(const int &threshold){
  for(int i = 0; i < input_image.num_rows(); ++i){
    for(int j = 0; j < input_image.num_columns(); ++j){            
        input_image.GetPixel(i,j) > threshold? output_image.SetPixel(i, j, 255): output_image.SetPixel(i, j, 0); 
    }
  }
}
