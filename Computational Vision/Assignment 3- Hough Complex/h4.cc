#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "image.h"
#include "labelImages.cc"
#include "createEdgeImage.cc"

using namespace std;
using namespace ComputerVisionProjects;

const double PI = 3.14159265358979323846;


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
    databaseVec.push_back(vector<double> {temp, 0, 0, 0, 0, 0, 0, 0, 0});
    return databaseVec.size()-1;
}


// helper function that finds the center of the givem image. 
void findCenter(const Image& inputImage, const Image& originalImage, vector<vector<double>> &databaseVec){
  for(int i = 0; i < inputImage.num_rows(); ++i){
    for(int j = 0; j < inputImage.num_columns(); ++j){

      int pixel = inputImage.GetPixel(i, j);
      if(pixel != 0){
        int originalValue = originalImage.GetPixel(i, j);  
        int index = getIndexFromLabel(databaseVec, pixel);
        index = index == -1? createIndexForLabel(databaseVec, pixel): index;

        databaseVec[index][1] += 1 * originalValue; // area
        databaseVec[index][2] += i * originalValue; // row
        databaseVec[index][3] += j * originalValue; // column
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

Image* drawImage(const vector<vector<double>> &accumulator, const int& threshold){

  Image *output_image = new Image();
  output_image -> AllocateSpaceAndSetSize(accumulator.size(), accumulator[0].size());
  output_image -> SetNumberGrayLevels(255);

  for(int i = 0; i < accumulator.size(); ++i){
    for(int j= 0; j < accumulator[i].size(); ++j){
      output_image -> SetPixel(i, j, (int)( accumulator[i][j]> threshold? accumulator[i][j]: 0));
    }
  }
  return output_image;
}

void importAccumulator(const string& file, vector<vector<double>>& accumulator){

  ifstream fin(file);
  if(fin.fail()){
    cout << "Failed to open file: " << file <<  endl;
    return;
  }

  string rhoLabel, thetaLabel, voteLabel;
  double rhoVal, thetaVal, voteVal, previousVal = -1;

  while(fin >> rhoLabel >> rhoVal >> thetaLabel >> thetaVal >> voteLabel >> voteVal){
    if(previousVal < rhoVal){
      previousVal = rhoVal;
      accumulator.push_back(vector<double> {});
    }
    accumulator[rhoVal].push_back(voteVal);
  }

  fin.close();
}


int main(int argc, char **argv){

  if(argc != 5){
    cout << "Usage: %s <input original image> <input hough voting array> <input Hough threshold value> <output line image>\n";
    return 0;
  }

  const string input_original_image(argv[1]);
  const string input_hough_array(argv[2]);
  const string input_hough_threshold(argv[3]);
  const string output_line_image(argv[4]);

  //input validation for threshold
  int thresholdVal; 
  try{
    thresholdVal = stoi(input_hough_threshold);
  }
  catch(int err){ 
    cout << "Invalid Threshold Value";
    return 0;
  }

  // create image objects
  Image input_image, copy_image;  

  // read images from input file
  if(!ReadImage(input_original_image, &input_image) || !ReadImage(input_original_image, &copy_image)){
    cout << "Can't open the input image " << input_original_image << endl;
    return 0;
  }

  vector<vector<double>> accumulator;
  importAccumulator(input_hough_array, accumulator);
  Image *inputHough = drawImage(accumulator, thresholdVal);
  Image *inputHoughCopy = drawImage(accumulator, thresholdVal);

  for(int i =0; i < inputHough->num_rows(); ++i){
		for(int j =0; j < inputHough->num_columns(); ++j){
			if(inputHough->GetPixel(i, j) != 0){
				std::cout << inputHough->GetPixel(i, j) << " ";
			}
		}
		std::cout << std::endl;
	}


  sequentialLabeling(*inputHoughCopy);  

  // vector<vector<double>> databaseVec;
  // findCenter(*inputHoughCopy, *inputHough, databaseVec);

  // double maxVal = 0;
  // vector<vector<double>> imageVec;
  // imageVec.reserve(copy_image.num_rows() * copy_image.num_columns());
  // calculateImage(copy_image, imageVec, maxVal); // x kernel 
  // getFinalImage(copy_image, imageVec, maxVal);  //final Image



  // if(!WriteImage(output_line_image, copy_image)){
  //   cout << "Can't write to file " << output_line_image << endl;
  //   return 0;
  // }

  cout << "Image manipulation Completed Successfully!\n";
  cout << "==========================================\n";

  return 0;
}