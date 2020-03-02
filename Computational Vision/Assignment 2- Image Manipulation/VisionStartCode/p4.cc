/*
Assignment 2 - Program 4

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 

Recognize Images From Input Database
====================================================================================================================
*/

#include <iostream>
#include <vector>
#include <math.h>
#include <sstream>
#include <fstream>
#include "image.h"

#define M_PI 3.14159265358979323846

using namespace std;
using namespace ComputerVisionProjects;

// print the values in the database to std output
void printDatabase(const vector<vector<double>> &databaseVec){

    cout << "\nThe values in the database are as follows:" << endl;
    cout << "==========================================" << endl << endl;

    for(auto i: databaseVec){
        if(i[1] == 1) continue;
        cout << fixed << i[0] << " " <<i[2] << " " <<i[3] << " " <<i[8] << " " << i[7]*180/M_PI << " " << i[9] << "\n";
    }
    cout << endl;
} 

// if index exists for label in the dataset, return index
// else return -1
int getIndexFromLabel(const vector<vector<double>> &databaseVec, const int &pixel){

    for(int i = 0; i < databaseVec.size(); ++i){
        if(databaseVec[i][0] == pixel) return i; 
    }
    return -1;
}

// called if label does not exist in dataset. Creates label and returns its index.
int createIndexForLabel(vector<vector<double>> &databaseVec, const int &pixel){
    double temp = pixel;
    databaseVec.push_back(vector<double> {temp, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    return databaseVec.size()-1;
}

// function that recolors an object based on whether it was recognized or not.
//  valid moment and orientation -> 255
//  valid moment but different orientation --> 127
//  not found --> 25 
void recolorImage(Image& inputImage, vector<vector<double>> &databaseVec){

    // visiting every pixel
    for(int i = 0; i < inputImage.num_rows(); ++i){
        for(int j = 0; j < inputImage.num_columns(); ++j){
    
            int pixel = inputImage.GetPixel(i, j);
            if(pixel != 0){
                int index = getIndexFromLabel(databaseVec, pixel);
                if(databaseVec[index][9] == 1){
                    inputImage.SetPixel(i, j, 255);
                }
                else if(databaseVec[index][9] == 2){
                    inputImage.SetPixel(i, j, 127);
                }
                else if(databaseVec[index][9] == 3){
                    inputImage.SetPixel(i, j, 25);
                }
            }
        }
    }
}

// Function that draws a line representing the orientation of the object. 
void drawLineSegment(Image& inputImage, vector<vector<double>> &databaseVec, const int& radius){

    for(auto i: databaseVec){
        if(i[1] == 1) continue;
        
        if(i[9] == 1 || i[9] == 2){
            double newX = i[2]+(radius*cos(i[7]));
            double newY = i[3] +(radius*sin(i[7]));
            
            int colorVal = i[0] > 127? 68: 235;
            DrawLine(i[2], i[3], newX, newY, colorVal, &inputImage);
        }
    }
}

// helper function that finds the center of the givem image.  
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

// function that finds the minimum moment of inertia
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

        databaseVec[i][7] = atan2(databaseVec[i][5], (databaseVec[i][4] - databaseVec[i][6]))/2;
        databaseVec[i][8] = databaseVec[i][4] * pow(sin(databaseVec[i][7]),2) - databaseVec[i][5] * sin(databaseVec[i][7]) * cos(databaseVec[i][7]) + databaseVec[i][6] * pow(cos(databaseVec[i][7]),2);         
    }                       

    return;
}

// function that will extract data from the text document and compare it with the data extracted from the image.
// after that, it sets conditions for similarity and checks it.
void compareValues(Image& inputImage, vector<vector<double>> &databaseVec, const string& compareDatabase){
    
    vector<vector<double>> compareDatabaseVec;
    ifstream fin(compareDatabase);
    string line;
    while(getline(fin, line)){
        compareDatabaseVec.push_back(vector<double> {});
        stringstream ss(line);
        string value;
        while(ss >> value){
            /*
                0: Label
                1: Center x
                2: Ceter y
                3: Moment of Inertia
                4: Orientation (theta)
            */
            compareDatabaseVec[compareDatabaseVec.size()-1].push_back(stod(value));
        }
    }

    // comparison
    // since different images, cannot compare labels and centers.
    // take 0.88 <= ratio of moment < 1.12 and difference of degrees <= 10 will be considered similar --> color 255
    // else if 0.88 <= ratio of moment < 1.12  but difference of degrees > 10, similar but different orientation --> color 127
    // else not similar --> color -> 25
    for(auto comparisonDatabase: compareDatabaseVec){
        for(int i = 0; i < databaseVec.size(); ++i){
            if(databaseVec[i][1] == 1) continue;

            double momentRatio = databaseVec[i][8]/comparisonDatabase[3];  
            double degreeDifference =  comparisonDatabase[4] - databaseVec[i][7]*180/M_PI;

            if(momentRatio >= 0.88 && momentRatio < 1.12 && degreeDifference <= 10 && degreeDifference > 0){
                databaseVec[i][9] = 1;     // same
            }
            else if(momentRatio >= 0.88 && momentRatio < 1.12 && (degreeDifference > 10 || degreeDifference < 0)){
                if(databaseVec[i][9] == 0 || databaseVec[i][9] == 3){
                    databaseVec[i][9] = 2;
                }
            }
            else{
                if(databaseVec[i][9] == 0){
                    databaseVec[i][9] = 3;
                }
            }
        }
    }
}

// main function that makes calls to helper functions to:
//  find center
//  find moment
//  compare values
//  recolor image
//  draw line
//  print dataset
void compareImageAndDatabase(Image& inputImage, const string& database){

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
        9: similarity integer (enum {1,2,3})
    */
    vector<vector<double>> databaseVec; 
        
    findCenter(inputImage, databaseVec);
    findMoment(inputImage, databaseVec);
    compareValues(inputImage, databaseVec, database);
    recolorImage(inputImage, databaseVec);
    drawLineSegment(inputImage, databaseVec, 35);
    printDatabase(databaseVec);
}


// main function that reads names from stdinput, makes calls to helper functions and reads and writes images. 
int main(int argc, char **argv){

    if (argc!=4) {
        cout << "Usage: %s <input labeled image> <database filename> <output image name>\n" << argv[0] << endl;
        return 0;
    }

    // file names for input and output file.
    const string input_file(argv[1]);
    const string database_name(argv[2]);
    const string output_file(argv[3]);

    // input validation for input file.
    Image an_image;
    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }

    //make function call
    compareImageAndDatabase(an_image, database_name);

    // saving the processed result to output file.
    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

    cout << "\n\nImage Manipulation Completed Successfully!\n";
    cout << "==========================================\n\n";

    return 0;
}