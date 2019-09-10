#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <map>

using namespace std;

void findEuclideanDistance(vector<vector<float>> &data, int kVal){

    map<float, vector<float>> distances;
    vector<float> newInstance = data[data.size() - 1];

    for(size_t i = 0; i < data.size() - 1; i++){
        float distVal = pow((data[i][0] - newInstance[0]),2) + pow((data[i][1] - newInstance[1]),2) + pow((data[i][2] - newInstance[2]),2) + pow((data[i][3] - newInstance[3]),2); 
        // cout << "distance: " << distVal << endl;
        // cout << "data: " << data[i][4] << endl;
        distances.insert(pair<float, vector<float>> (distVal, data[i]));
    }

    int counter = 0;
    int aCount = 0, bCount = 0, cCount = 0;

    cout << "EUCLIDEAN DISTANCE: " << endl;
    cout << "==========================================" << endl << endl;

    cout << "The k closest distances to the new example are: " << endl << endl;
    for(auto distance: distances){

        if(counter == kVal) break;

        cout<< "Distance: " << distance.first << "\tInstance: " << "[ ";

        
        for(float values: distance.second){
            if(values > 60) cout << char(values) << " ";
            else cout << values << ", ";
        }

        cout << "]" << endl;


        if(distance.second[4] == 'A') aCount++;
        else if(distance.second[4] == 'B') bCount++;
        else cCount++;

        counter++;
    }
    cout << endl;
    cout << "A: " <<aCount << " " << "B: "<< bCount << " " << "C: " << cCount << endl << endl;    

    if(aCount >= bCount && aCount >= cCount) data[data.size() -1][4] = 'A';
    if(bCount >= aCount && bCount >= cCount) data[data.size() -1][4] = 'B';
    if(cCount >= aCount && cCount >= bCount) data[data.size() -1][4] = 'C';

    cout << "The class generated by EUCLIDEAN distance for k = " << kVal << " is " << char(data[data.size() -1][4]) << endl;
    
}

void findManhattanDistance(vector<vector<float>> &data, int kVal){

    map<float, vector<float>> distances;
    vector<float> newInstance = data[data.size() - 1];

    for(size_t i = 0; i < data.size() - 1; i++){
        float distVal = abs(data[i][0] - newInstance[0]) + abs(data[i][1] - newInstance[1]) + abs(data[i][2] - newInstance[2]) + abs(data[i][3] - newInstance[3]); 
        // cout << "distance: " << distVal << endl;
        // cout << "data: " << data[i][4] << endl;
        distances.insert(pair<float, vector<float>> (distVal, data[i]));
    }

    int counter = 0;
    int aCount = 0, bCount = 0, cCount = 0;

    cout << "MANHATTAN DISTANCE: " << endl;
    cout << "==========================================" << endl << endl;

    cout << "The k closest distances to the new example are: " << endl << endl;
    for(auto distance: distances){

        if(counter == kVal) break;

        cout<< "Distance: " << distance.first << "\tInstance: " << "[ ";

        
        for(float values: distance.second){
            if(values > 60) cout << char(values) << " ";
            else cout << values << ", ";
        }

        cout << "]" << endl;


        if(distance.second[4] == 'A') aCount++;
        else if(distance.second[4] == 'B') bCount++;
        else cCount++;

        counter++;
    }
    cout << endl;
    cout << "A: " <<aCount << " " << "B: "<< bCount << " " << "C: " << cCount << endl << endl;    

    if(aCount >= bCount && aCount >= cCount) data[data.size() -1][4] = 'A';
    if(bCount >= aCount && bCount >= cCount) data[data.size() -1][4] = 'B';
    if(cCount >= aCount && cCount >= bCount) data[data.size() -1][4] = 'C';

    cout << "The class generated by MANHATTAN distance for k = " << kVal << " is " << char(data[data.size() -1][4]) << endl;
    
}

vector<pair<float,float>> findMinAndMax(vector <vector<float>> &data){

    vector<pair<float,float>> minMax;
    
    minMax.push_back(pair<float,float> (INT_MIN, INT_MAX));
    minMax.push_back(pair<float,float> (INT_MIN, INT_MAX));
    minMax.push_back(pair<float,float> (INT_MIN, INT_MAX));
    minMax.push_back(pair<float,float> (INT_MIN, INT_MAX));

    for(size_t i = 0; i < data.size(); i++){
        // cout << row.first << " " << row.second << endl; 
        for(size_t j = 0; j < data[i].size() -1; j++){

            if(data[i][j] > minMax[j].first){
                minMax[j].first = data[i][j];
            }
            if(data[i][j] < minMax[j].second){
                minMax[j].second = data[i][j];
            }
        }
    }

    // for(auto row: minMax){
    //     cout << row.first << " " << row.second << endl; 
    // }

    return minMax; 
}


void normalizeFeatures(vector<vector<float>> &data){

    cout <<endl << "******************** APPLYING NORMALIZATION *********************" << endl << endl;

    auto minMaxVal = findMinAndMax(data);

    for(size_t i = 0; i < data.size(); i++){
        for(size_t j = 0; j < data[i].size() -1; j++){

            float numerator = data[i][j] - minMaxVal[j].second;            
            float denominator =  minMaxVal[j].first - minMaxVal[j].second;

            data[i][j] = numerator/denominator; 
        }
    }
}

/*
 * function that prints the dataset,
 * Last feature is the latest addition to the dataset and is kept there because it doesn't affect the min/max value
*/
void printDataValues(const vector<vector<float>> &data){
    
    cout << endl << "THE INPUT DATASET IS" << endl;
    cout << "==========================================" << endl << endl;

    for(auto line: data){
        string value = "";
        if(char(line[4]) != 'X'){
            for(float lineData: line){
                if(lineData > 60){
                    value = value + char(lineData);
                }
                else{
                    value = value + to_string(lineData) + ", ";
                }
            }
            cout << value << endl;
        }
        
    }

    cout <<endl << "==========================================" << endl;    
}

int main(){
    
    vector<vector <float>> data;

    data.push_back(vector<float> {5.1,3.5,1.3,0.2,'A'});
    data.push_back(vector<float> {5.7,3.4,1.3,0.2,'C'});
    data.push_back(vector<float> {4.7,3.1,1.6,0.2,'A'});
    data.push_back(vector<float> {5.0,4.6,1.4,0.1,'B'});
    data.push_back(vector<float> {5.9,3.3,4.0,1.3,'C'});
    data.push_back(vector<float> {6.5,2.7,4.6,1.5,'A'});
    data.push_back(vector<float> {5.7,2.8,4.4,1.3,'B'});
    data.push_back(vector<float> {6.3,3.3,4.7,1.4,'C'});
    data.push_back(vector<float> {4.7,2.4,3.2,1.0,'A'});
    data.push_back(vector<float> {7.7,3.6,6.7,2.2,'B'});
    data.push_back(vector<float> {7.7,2.6,6.5,2.3,'C'});
    data.push_back(vector<float> {6.0,2.2,5.0,1.4,'A'});
    data.push_back(vector<float> {6.9,3.2,5.7,9.3,'B'});
    data.push_back(vector<float> {5.6,2.2,4.6,2.0,'C'});
    data.push_back(vector<float> {5.0,2.8,4.6,0.7,'X'});    // new instance that has an unknown class and will be predicted by kNN

    
    printDataValues(data);

    int kVal = 0;
    cout << "IMPLEMENTING kNN" << endl;
    cout << "==========================================" << endl << endl;    
    cout << "Enter the k value: ";
    cin  >> kVal;
    cout << endl;


    normalizeFeatures(data);
    
    findEuclideanDistance(data, kVal);
    findManhattanDistance(data, kVal);


    return 0;
}