#ifndef BINARY_IMAGES_H_
#define BINARY_IMAGES_H_

#include <iostream>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

class BinaryImage {

  public:
    BinaryImage(const std::string& input_file);
    bool setImage(const std::string& input_file);    
    Image* getOutputImage();    
    void convertToBinary(const int &threshold);

  private:
    Image input_image;
    Image output_image;
};

#endif