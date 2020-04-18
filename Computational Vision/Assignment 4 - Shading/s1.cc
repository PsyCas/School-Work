#include <iostream>
#include "binaryImages.h"
#include "image.h"

using namespace std;


int main(int argc, char** argv){

  if (argc!=4) {
        cout << "Usage: %s <input image> <grey threshold value> <output parameters file>\n" << argv[0] << endl;
        return 0;
    }

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

    // file names for input and output file.
    const string input_file(argv[1]);
    const string output_file(argv[3]);

    Image *binary_image;  //pointer to binary image object
    BinaryImage anImage(input_file);
    anImage.convertToBinary(gray_level_threshold);
    binary_image = anImage.getOutputImage();

    // saving the processed result to output file.
    if (!WriteImage(output_file, *binary_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

    cout << "Image Manipulation Completed Successfully!\n";
    cout << "==========================================\n";

}
