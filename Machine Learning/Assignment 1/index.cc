#include <iostream>
#include <vector>

using namespace std;


void normalizeFeatures(vector<vector<float>> &data){

    for(auto line: data){
        for(float lineData: line){
            if(lineData < 60){
                // value = value + to_string(lineData) + ", ";
            }
        }
        // cout << value << endl;
    }

}


void printDataValues(const vector<vector<float>> &data){

    for(auto line: data){
        string value = "";
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

    normalizeFeatures(data);
    printDataValues(data);

    return 0;
}