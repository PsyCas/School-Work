#include <iostream>
#include <vector> 
#include <set> 
#include <algorithm>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

int findEquivalentLabel(const vector<vector<int>> table, const int &pixel){

    int index = pixel - 1;
    int newPixel = pixel; 

    for(int i = index-1; i >= 0; --i){
        auto iter = find(table[i].begin(), table[i].end(), newPixel);
        if(iter != table[i].end()){
            newPixel = table[i][0];
        } 
    }

    // //Alternate algorithm 
    // bool flag = true;
    // while(flag == true){
    //     for(int i = 0; i < newPixel; i++){
    //         auto iter = find(table[i].begin()+1, table[i].end(), newPixel);
    //         if(iter != table[i].end()){
    //             newPixel = table[i][0];
    //             break;
    //         }
    //         else if(i == newPixel-1){
    //             flag = false;
    //         }
    //     }
    // }


    return newPixel;
}

void printTable(const vector<vector<int>> table){

    cout << "here";

    for(int i = 0; i < table.size(); ++i){
        for(int num: table[i]){
            cout << num << ",";
        }
        cout << endl;
    }
}

void sequentialLabeling(Image &inputImage){

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
            if( pixel != 255){
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
    equivalencyTable.pop_back();

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