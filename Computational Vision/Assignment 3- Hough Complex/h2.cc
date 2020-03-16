#include <iostream>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

void createBinaryImage(Image& input_image, int threshold){
  for(int i = 0; i < input_image.num_rows(); ++i){
        for(int j = 0; j < input_image.num_columns(); ++j){            
            input_image.GetPixel(i,j) > threshold? input_image.SetPixel(i, j, 255): input_image.SetPixel(i, j, 0); 
        }
    }
}

int main(int argc, char **argv){

  if(argc != 4){
    cout << "Usage: %s <grey level image> <grey level threshold> <output binary image>\n";
    return 0;
  }

  const string input_file(argv[1]);
  const string output_file(argv[3]);

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

  // input validation for input file.
  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
      cout <<"Can't open file " << input_file << endl;
      return 0;
  }
  
  createBinaryImage(an_image, gray_level_threshold);

  // saving the processed result to output file.
  if(!WriteImage(output_file, an_image)){
      cout << "Can't write to file " << output_file << endl;
      return 0;
  }

  cout << "Image Manipulation Completed Successfully!\n";
  cout << "==========================================\n";

  return 0;
}