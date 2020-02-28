#include <iostream>
#include <vector>
#include <math.h>
#include "image.h"

# define M_PI           3.14159265358979323846  /* pi */

using namespace std;
using namespace ComputerVisionProjects;

// print the values in the database to std output
void printDatabase(const vector<vector<double>> &databaseVec){

    cout << "The values in the database are as follows:" << endl;
    // cout << "Label\t\t" << 
    //         "Area\t\t" << 
    //         "Row\t\t" << 
    //         "Col\t\t" << 
    //         "a\t\t\t" << 
    //         "b\t\t\t" << 
    //         "c\t\t       "<< 
    //         "Theta\t\t" << 
    //         "Moment\t\t" << 
    //         "Orient\t\t" << endl;

    for(auto i: databaseVec){
        cout << std::fixed;
        cout << "a --> " << i[4] << endl;
        cout << "b --> " << i[5] << endl;
        cout << "c --> " << i[6] << endl;
        cout << "theta --> " << i[7] << endl;
        cout << "moment --> " << i[8] << endl;


        // for(auto j: i){
            // cout << j << "\t\t";
        // }
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
    databaseVec.push_back(vector<double> {temp, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    return databaseVec.size()-1;
}

void findCenter(const Image& inputImage, vector<vector<double>> &databaseVec){

    for(int i = 0; i < inputImage.num_rows(); ++i){
        for(int j = 0; j < inputImage.num_columns(); ++j){
    
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

    // computing the centers by dividing with area
    for(int i = 0; i < databaseVec.size(); ++i){
        databaseVec[i][2] = databaseVec[i][2]/ databaseVec[i][1];
        databaseVec[i][3] = databaseVec[i][3]/ databaseVec[i][1];
    }

    return;
}

void findMoment(Image& inputImage, vector<vector<double>> &databaseVec){

    for(int i = 0; i < inputImage.num_rows(); ++i){
        for(int j = 0; j < inputImage.num_columns(); ++j){
            
            int pixel = inputImage.GetPixel(i, j);
            if(pixel != 0){

                // index cannot be -1 now since it is already initialized
                int index = getIndexFromLabel(databaseVec, pixel);
                if(index == -1) {
                    cout << "Something went wrong. Try again.";
                    abort();
                }

                databaseVec[index][4] += pow(i - databaseVec[index][2],2); // x (pixel x) - x' (center x)   
                databaseVec[index][5] += (i - databaseVec[index][2])*(j - databaseVec[index][3]); // (x-x')*(y-y')   
                databaseVec[index][6] += pow(j - databaseVec[index][3],2); // y (pixel y) - y' (center x)   
            }
        }
    }
    // computing the theta and finalizing value of b
    for(int i = 0; i < databaseVec.size(); ++i){
        databaseVec[i][5] *= 2; // 2 * sum. Check formula for reference

        int temp = (databaseVec[i][5])/(databaseVec[i][4] - databaseVec[i][6]);
        databaseVec[i][7] = atan(temp)/2 * (180/M_PI);

        databaseVec[i][8] = databaseVec[i][4] * pow(sin(databaseVec[i][7]),2) - databaseVec[i][5] * sin(databaseVec[i][7]) * cos(databaseVec[i][7]) + databaseVec[i][6] * pow(cos(databaseVec[i][7]),2);         
    }                       

    return;
}

void createAndSaveDatabase(Image& inputImage){

    /* Indices:
        0: Label
        1: Area
        2: Center x (row)
        3: Center y (col)
        4: a
        5: b
        6: c
        7: Theta
        8: Minimum Moment of Inertia
        9: Orientation (angle in degrees) 
    */
    vector<vector<double>> databaseVec; 
        
    findCenter(inputImage, databaseVec);
    findMoment(inputImage, databaseVec);
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
    // if (!WriteImage(output_file, an_image)){
    //     cout << "Can't write to file " << output_file << endl;
    //     return 0;
    // }

    cout << "\n\nImage Manipulation Completed Successfully!\n";
    cout << "==========================================\n\n";

    return 0;
}