#include <iostream>
#include <vector> 
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

    //second algorithm 
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
            if( pixel == 255){
                // cout << "(" << i << ", " << j << ") " << endl;
                // cout << "(" << i << ", " << j << ") " << pixel << " " << upperPixel << " " << leftPixel << endl;

                // pixel above is labeled
                if(upperPixel != 0 && upperPixel != 255){
                    // cout << "cond1" << endl;   
                    inputImage.SetPixel(i, j, upperPixel);

                    // both above and left pixel are labeled different
                    if(leftPixel != 0 && leftPixel != 255 && leftPixel != upperPixel){  
                        // cout << "cond1 if" << endl;
                        int labelIndex = upperPixel-1;        //if label is 1, index is 0 and so on...
                        
                        auto iter = find(equivalencyTable[labelIndex].begin(), equivalencyTable[labelIndex].end(), leftPixel); 
                        if(iter == equivalencyTable[labelIndex].end()){
                            equivalencyTable[labelIndex].push_back(leftPixel);
                        } 
                        // printTable(equivalencyTable);
                    }
                    //unwritten else if condition means both left and up pixel have same lables.
                }
                // left pixel is labeled
                else if (leftPixel != 0 && leftPixel != 255){
                    // cout << "cond2 elif" << " leftpx- " << leftPixel << endl;
                    inputImage.SetPixel(i, j, leftPixel);
                }
                // neither top nor left pixel are labeled
                else{
                    // cout << "(" << i << ", " << j << ") " << pixel << " " << upperPixel << " " << leftPixel << endl;
                    // cout << "else"<< endl;
                    inputImage.SetPixel(i, j, labelCounter);
                    labelCounter++;
                    equivalencyTable.push_back(vector<int> {labelCounter});
                }
            }
        }
    }
    // cout << endl;
    equivalencyTable.pop_back();
    printTable(equivalencyTable);

    //second pass
    for(int i = 0; i < inputImage.num_rows(); ++i){
        for(int j = 0; j < inputImage.num_columns(); ++j){
        
            int pixel = inputImage.GetPixel(i, j);
            // precondition - no white (255) pixels
            if(pixel != 0){
                // cout << "in label: " << pixel << endl; 
                int label = findEquivalentLabel(equivalencyTable, pixel);
                inputImage.SetPixel(i, j, label+10);
                // cout << "out label: " << label << endl << endl; 

            }
        }
    }
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

    sequentialLabeling(an_image);

    // saving the processed result to output file.
    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

    cout << "\n\nImage Manipulation Completed Successfully!\n";
    cout << "==========================================\n\n";
}