#include <iostream>

using namespace std;

int main(int argc, char** argv){

  if(argc != 6){
    cout << "Usage: %s <input parameters file> <image 1> <image 2> <image 3> <output directions file>\n" << argv[0] << endl;
    return 0;
  }

  //gathering input from the user
  const string input_param_file(argv[1]);
  const string image1(argv[2]);
  const string image2(argv[3]);
  const string image3(argv[4]);
  const string output_file(argv[5]);

  cout << input_param_file << endl;
  cout << image1 << endl;
  cout << image2 << endl;
  cout << image3 << endl;
  cout << output_file << endl;

  return 0;
}