#include <iostream>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

void createHoughImage(const string& input_file, const string& output_file, const string& output_array){

  

}



int main(int argc, char **argv){

  if(argc != 4){
    cout << "Usage: %s <input binary image> <grey level hough image> <output Hough voting array>\n";
    return 0;
  }

  const string input_file(argv[1]);
  const string output_file(argv[2]);
  const string output_array(argv[3]);

  cout << input_file << " " << output_file << " " << output_array << endl;

  Image an_image;
  if(!ReadImage(input_file, &an_image)){
    cout << "Can't open file " << input_file << endl;
    return 0;
  }

  createHoughImage(input_file, output_file,output_array);

  // UNCOMMENT THIS LATER

  // if(!WriteImage(output_file, an_image)){
  //   cout << "Can't write to file " << output_file << endl;
  //   return 0;
  // }

  cout << "Image manipulation Completed Successfully!\n";
  cout << "==========================================\n";

  return 0;
}