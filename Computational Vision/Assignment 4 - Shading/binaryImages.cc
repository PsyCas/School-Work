/*
 * Parakram Basnet
 * Funtion implementation of the BinaryImages class.
 */

#include "binaryImages.h"
#include <iostream>
#include <string>

/*
 * parameterized constructor that reads image provided in the parameter and stores it into
 * the instance variable 
 */
BinaryImage::BinaryImage(const std::string& input_file){
  if(!ReadImage(input_file, &input_image)){
    std::cout << "Can't open file " << input_file << std::endl;
    abort();
  }
  else{
    ReadImage(input_file, &output_image);
  }
}

/*
 * Function that reads the image that is provided in the parameter
 */
bool BinaryImage::setImage(const std::string& input_file){
  if(!ReadImage(input_file, &input_image)){
    return false;
  }
  else{
    ReadImage(input_file, &output_image);
    return true;
  }
}
    
/*
 * Function that returns a pointer to the image stored in the instance variable
 */
Image* BinaryImage::getOutputImage(){
  Image *output_pointer = &output_image;
  return output_pointer;
}
    
/*
 * Function that converts the image into a binary image with the provided threshold 
 */
void BinaryImage::convertToBinary(const int &threshold){
  for(int i = 0; i < input_image.num_rows(); ++i){
    for(int j = 0; j < input_image.num_columns(); ++j){            
        input_image.GetPixel(i,j) > threshold? output_image.SetPixel(i, j, 255): output_image.SetPixel(i, j, 0); 
    }
  }
}
