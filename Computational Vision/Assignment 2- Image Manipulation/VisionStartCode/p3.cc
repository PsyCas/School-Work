#include <iostream>
#include <vector>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

void printDatabase(const vector<vector<double>> &databaseVec){

    for(auto i: databaseVec){
        for(auto j: i){
            cout << j << " ";
        }
        cout << endl;
    }
}

int getIndexFromLabel(const vector<vector<double>> &databaseVec, const int &pixel){

    for(int i = 0; i < databaseVec.size(); ++i){
        if(databaseVec[i][0] == pixel) return i; 
    }
    return -1;
}

int createIndexForLabel(vector<vector<double>> &databaseVec, const int &pixel){
    double temp = pixel;
    databaseVec.push_back(vector<double> {temp, 0, 0, 0, 0, 0, 0});
    return databaseVec.size()-1;
}

void findCenter(Image& inputImage, vector<vector<double>> &databaseVec){

    for(int i = 0; i < inputImage.num_rows(); ++i){
        for(int j = 0; j < inputImage.num_columns(); ++j){
                
            double  area = 0,
                    row = 0,
                    column = 0;
            
            int pixel = inputImage.GetPixel(i, j);
            if(pixel != 0){
                
                int index = getIndexFromLabel(databaseVec, pixel);
                index = index == -1? createIndexForLabel(databaseVec, pixel): index;

                databaseVec[index][1] += 1; // area
                databaseVec[index][2] += i; // row
                databaseVec[index][3] += j; // column
            }                     
        }
    }

    // computing the centers
    for(int i = 0; i < databaseVec.size(); ++i){
        
        // cout << "Before: " << databaseVec[i][0] << " " << databaseVec[i][1] << " " << databaseVec[i][2] << " " << databaseVec[i][3] << endl;
        
        databaseVec[i][2] = databaseVec[i][2]/ databaseVec[i][1];
        databaseVec[i][3] = databaseVec[i][3]/ databaseVec[i][1];

        inputImage.SetPixel(databaseVec[i][2], databaseVec[i][3], 255);
        // cout << "After: " << databaseVec[i][0] << " " << databaseVec[i][1] << " " << databaseVec[i][2] << " " << databaseVec[i][3] << endl;

    }

    return;
}

void createAndSaveDatabase(Image& inputImage){

    /* Indices:
        0: Label
        1: Area
        2: Center x (row)
        3: Center y (col)
        4: min moment of inertia
        5: orientation
    */
    vector<vector<double>> databaseVec; 
        
    findCenter(inputImage, databaseVec);
    printDatabase(databaseVec);

    return;
}



int main(int argc, char **argv){

    if (argc!=3) {
        cout << "Usage: %s <input labeled image> <output image name>\n" << argv[0] << endl;
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

    //make function call
    createAndSaveDatabase(an_image);

    // saving the processed result to output file.
    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

    cout << "\n\nImage Manipulation Completed Successfully!\n";
    cout << "==========================================\n\n";

    return 0;
}