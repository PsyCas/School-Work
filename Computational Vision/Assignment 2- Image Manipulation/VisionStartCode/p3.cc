#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

// print the values in the database to std output
void printDatabase(const vector<vector<double>> &databaseVec){

    cout << "\nThe values in the database are as follows:" << endl;
    cout << "==========================================" << endl << endl;

    for(auto i: databaseVec){
        if(i[1] == 1) continue;
        cout << fixed << i[0] << " " <<i[2] << " " <<i[3] << " " <<i[8] << " " << i[7] << "\n";
    }
    cout << endl;
}   

int getIndexFromLabel(const vector<vector<double>> &databaseVec, const int &pixel){

    for(int i = 0; i < databaseVec.size(); ++i){
        if(databaseVec[i][0] == pixel) return i; 
    }
    return -1;
}

int createIndexForLabel(vector<vector<double>> &databaseVec, const int &pixel){
    double temp = pixel;
    databaseVec.push_back(vector<double> {temp, 0, 0, 0, 0, 0, 0, 0, 0});
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

        databaseVec[i][7] = atan2(databaseVec[i][5], (databaseVec[i][4] - databaseVec[i][6]))/2;
        databaseVec[i][8] = databaseVec[i][4] * pow(sin(databaseVec[i][7]),2) - databaseVec[i][5] * sin(databaseVec[i][7]) * cos(databaseVec[i][7]) + databaseVec[i][6] * pow(cos(databaseVec[i][7]),2);         
    }                       

    return;
}

void drawLineSegment(Image& inputImage, vector<vector<double>> &databaseVec, const int& radius){
    for(auto i: databaseVec){
        if(i[1] == 1) continue;

        double newX = i[2]+(radius*cos(i[7]));
        double newY = i[3] +(radius*sin(i[7]));
        
        int colorVal = i[0] > 127? 68: 235;
        DrawLine(i[2], i[3], newX, newY, colorVal, &inputImage);
    }
}

void createAndSaveDatabase(Image& inputImage, const string& database){

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
    */
    vector<vector<double>> databaseVec; 
        
    findCenter(inputImage, databaseVec);
    findMoment(inputImage, databaseVec);
    drawLineSegment(inputImage, databaseVec, 35);
    printDatabase(databaseVec);
    
    ofstream fout(database);
    for(auto i: databaseVec){
        if(i[1] == 1) continue;
        fout << fixed << i[0] << " " <<i[2] << " " <<i[3] << " " <<i[8] << " " << i[7] << "\n";
    }
    fout.close();
    return;
}



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
    createAndSaveDatabase(an_image, database_name);

    // saving the processed result to output file.
    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

    cout << "\n\nImage Manipulation Completed Successfully!\n";
    cout << "==========================================\n\n";

    return 0;
}