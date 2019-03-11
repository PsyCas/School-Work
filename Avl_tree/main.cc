// #include "sequence_map.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main(){

    string first = "AanI";
    string second = "TTA'TAA";
    string comparison = "Bbni";

    vector<string> vec1= {"AanI", "Bbni"};
    vector<string> vec2= {"CcnI", "Dcni"};

    for(string newStr : vec1)
        cout << newStr << endl;
    
    cout << endl;

    for(string newStr : vec2)
        vec1.push_back(newStr);

    for(string newStr : vec1)
        cout << newStr << endl;
   

}