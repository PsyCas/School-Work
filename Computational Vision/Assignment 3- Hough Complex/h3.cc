#include <iostream>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv){

  if(argc != 4){
    cout << "Usage: %s <grey level image> <grey level threshold> <output binary image>\n";
    return 0;
  }

  const string input_file(argv[1]);
  const string output_file(argv[3]);

  return 0;
}