#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void read_dimensions(const string &dimensions_file, vector<int>& dimensions){

    ifstream fin(dimensions_file);
    int dimensions_number = 0;

    while(fin >> dimensions_number){
        dimensions.push_back(dimensions_number);
    }
}

int main(int argc, char** argv){

    if(argc != 2){
        cout << "Usage: " << argv[0] << " <dimensions_filename>" << endl;
        return 0;
    }

    const string dimensions_file(argv[1]);
    cout <<"The input file name is: " << dimensions_file << endl << endl;

    vector<int> dimensions;
    read_dimensions(dimensions_file, dimensions);

    for(int newInt: dimensions){
        cout << newInt << " ";
    }
}