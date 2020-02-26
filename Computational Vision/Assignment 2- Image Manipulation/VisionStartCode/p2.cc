#include <iostream>
#include <vector> 
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

int findLabel(const vector<vector<int>> &equivalencyTable){
    return -1
}

Image sequentialLabeling(Image &inputImage){

    int labelCounter = 1;
    Image generatedImage;

    // equivalency table where index [0] is the index label and [ 1-n ] are equivalent labels
    vector<vector<int>> equivalencyTable;

    // init table with first label
    equivalencyTable.push_back(vector<int> {labelCounter});

    for(int i = 0; i < inputImage.num_rows(); ++i){
        for(int j = 0; j < inputImage.num_columns(); ++j){

            int pixel = inputImage.GetPixel(i, j), 
                upperPixel = i != 0? inputImage.GetPixel(i-1, j): 0,    // error checking for seg fault
                leftPixel =  j != 0? inputImage.GetPixel(i, j-1): 0;

            // object exists
            if( pixel == 255){
                
                // pixel above is labeled
                if(upperPixel != 0 && upperPixel != 255){   
                    inputImage.SetPixel(i, j, labelCounter);

                    // both above and left pixel are labeled 
                    if(leftPixel != 0 && leftPixel != 255 && leftPixel != upperPixel){  
                        int labelIndex = findLabel(equivalencyTable);
                        equivalencyTable[labelIndex].push_back(leftPixel);
                    }
                    //unwritten else if condition means both left and up pixel have same lables.
                }
                // left pixel is labeled
                else if (leftPixel != 0 && leftPixel != 255){
                    inputImage.SetPixel(i, j, labelCounter);
                }
                // neither top nor left pixel are labeled
                else{
                    labelCounter++;
                    inputImage.SetPixel(i, j, labelCounter);
                    equivalencyTable.push_back(vector<int> {labelCounter});
                }
            }
        }
    }
    return generatedImage;
}


int main(int argc, char **argv){

    if (argc!=3) {
        cout << "Usage: %s <input image> <output binary image>\n" << argv[0] << endl;
        return 0;
    }

    // file names for input and output file.
    const string input_file(argv[1]);
    const string output_file(argv[2]);

    // input validation for input file.
    Image an_image;
    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }

    // saving the processed result to output file.
    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

    cout << "Image Manipulation Completed Successfully!\n";
    cout << "==========================================\n";
}