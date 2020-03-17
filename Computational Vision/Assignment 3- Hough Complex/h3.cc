#include <iostream>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;





int main(int argc, char **argv){

  if(argc != 4){
    cout << "Usage: %s <input binary image> <grey level hough image> <output Hough voting array>\n";
    return 0;
  }

  const string input_file(argv[1]);
  const string output_file(argv[2]);
  const string output_array(argv[3]);

  cout << input_file << " " << output_file << " " << output_array << endl;

  return 0;
}