/*
Assignment 2 - Program 2

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 

Convert Binary Image to Labeled Image
====================================================================================================================
*/

#include <iostream>
#include <vector> 
#include <set> 
#include <algorithm>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

// function that takes a label as input and searches in the equivalence table for the smallest possible label equivalent to it.
int findEquivalentLabel(const vector<vector<int>> table, const int &pixel){

    int index = pixel - 1;
    int newPixel = pixel;; 

    for(int i = index-1; i >= 0; --i){
        auto iter = find(table[i].begin(), table[i].end(), newPixel);
        if(iter != table[i].end()){
            newPixel = table[i][0];
        } 
    }

    //Alternate algorithm 
    /*bool flag = true;
    while(flag == true){
        for(int i = 0; i < newPixel; i++){
            auto iter = find(table[i].begin()+1, table[i].end(), newPixel);
            if(iter != table[i].end()){
                newPixel = table[i][0];
                break;
            }
            else if(i == newPixel-1){
                flag = false;
            }
        }
    }*/

    return newPixel;
}

// prints the equivalence table
void printTable(const vector<vector<int>> table){

    for(int i = 0; i < table.size(); ++i){
        for(int num: table[i]){
            cout << num << ",";
        }
        cout << endl;
    }
}

// function that sequentially labels an image.
// it visits every pixel, checks for labels in upper and left pixel. Then chooses the smallest as label and inserts the other into an equivalence table. 
void sequentialLabeling(Image &inputImage){

    // individual label counter
    int labelCounter = 1;

    // equivalency table where index [0] is the index label and [ 1-n ] are equivalent labels
    vector<vector<int>> equivalencyTable;

    // init table with first label
    equivalencyTable.push_back(vector<int> {labelCounter});

    // first pass
    for(int i = 0; i < inputImage.num_rows(); ++i){
        for(int j = 0; j < inputImage.num_columns(); ++j){
            
            int pixel = inputImage.GetPixel(i, j), 
                upperPixel = i != 0? inputImage.GetPixel(i-1, j): -1,    // error checking for seg fault
                leftPixel =  j != 0? inputImage.GetPixel(i, j-1): -1;

            // object exists
            if( pixel == 255){
                // pixel above is labeled
                if(upperPixel != 0 && upperPixel != 255){
                    inputImage.SetPixel(i, j, upperPixel);

                    // both above and left pixel are labeled different
                    if(leftPixel != 0 && leftPixel != 255 && leftPixel > upperPixel){  
                        int labelIndex = upperPixel-1;        //if label is 1, index is 0 and so on...
                        
                        auto iter = find(equivalencyTable[labelIndex].begin()+1, equivalencyTable[labelIndex].end(), leftPixel); 
                        if(iter == equivalencyTable[labelIndex].end()){
                            equivalencyTable[labelIndex].push_back(leftPixel);
                        } 
                    }
                    else if(leftPixel != 0 && leftPixel != 255 && leftPixel < upperPixel){
                        inputImage.SetPixel(i, j, leftPixel);
                        int labelIndex = leftPixel-1;        //if label is 1, index is 0 and so on...
                        
                        auto iter = find(equivalencyTable[labelIndex].begin()+1, equivalencyTable[labelIndex].end(), upperPixel); 
                        if(iter == equivalencyTable[labelIndex].end()){
                            equivalencyTable[labelIndex].push_back(upperPixel);
                        } 
                    }

                    //unwritten else if condition means both left and up pixel have same lables.
                }
                // left pixel is labeled
                else if (leftPixel != 0 && leftPixel != 255){
                    inputImage.SetPixel(i, j, leftPixel);
                }
                // neither top nor left pixel are labeled
                else{
                    inputImage.SetPixel(i, j, labelCounter);
                    labelCounter++;
                    equivalencyTable.push_back(vector<int> {labelCounter});
                }
            }
        }
    }
    equivalencyTable.pop_back(); // last element is excess

    // to store and display final labels
    std::set<int> labelDups;

    //second pass
    for(int i = 0; i < inputImage.num_rows(); ++i){
        for(int j = 0; j < inputImage.num_columns(); ++j){
        
            int pixel = inputImage.GetPixel(i, j);
            // precondition - no white (255) pixels
            if(pixel != 0){
                int label = findEquivalentLabel(equivalencyTable, pixel);
                inputImage.SetPixel(i, j, label + 25);
                labelDups.insert(label);
            }
        }
    }
    cout << "\n\nThe labels in the end are: " << endl;
    int setCounter = 0;
    for (auto it=labelDups.begin(); it != labelDups.end(); ++it){
        setCounter != labelDups.size()-1? cout << *it << ", ": cout << *it;
        setCounter++;
    }
    cout<< endl;
}


// main function that reads names from stdinput, makes calls to helper functions and reads and writes images. 
int main(int argc, char **argv){

    if (argc!=3) {
        cout << "Usage: %s <input binary image> <output labeled image>\n" << argv[0] << endl;
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

    sequentialLabeling(an_image);

    // saving the processed result to output file.
    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

    cout << "\n\nImage Manipulation Completed Successfully!\n";
    cout << "==========================================\n\n";
}