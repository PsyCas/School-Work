#include <iostream>
#include <fstream>
#include <vector>
#include <climits> 

#include "matrix.h"

using namespace std;

/**
 * Compute optimal ordering of matrix multiplication. 
 * c contains the number of columns for each of the n matrices. 
 * c[0] is the number of rows in the matrix 1.
 * The minimum number of multiplications is left in m[1][n].
 * Actual ordering is computed via another procedure using lastChange.
 * m and lastChange are indexed starting at 1, instead of 0.
 * Note: Entries below main diagonals of m and lastChange
 * are meaningless and uninitialized
 */
void optMatrix( const vector<int> &c, matrix<long> &m, matrix<int> &lastChange ){

    int n = c.size() -1;

    for( int left = 1; left <= n; left++){
        m[left][left] = 0;
    }

    for( int k = 1; k < n; k++ ){ // k is right - left
           
        for( int left = 1; left <= n - k; left++ ){
            
            //For each position
            int right = left + k;
            m[left][right] = LONG_MAX;
            for( int i = left; i < right; i++ ){

                long thisCost = m[left][i] + m[i + 1][right] + c[left - 1] * c[i] * c[right];                
                if(thisCost < m[left][right] ){  //Update min
                    m[left][right] = thisCost;
                    lastChange[left][right] = i;
                }
            }
        }
    }
    cout << "Optimal matrix multiplication is: " << m[1][c.size()-1] << endl;
}

void readDimensions(const string &dimensions_file, vector<int>& dimensions){

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
    readDimensions(dimensions_file, dimensions);   // reads the dimensions from the input file.

    // for(int newInt: dimensions){
    //     cout << newInt << " ";
    // }

    int n = dimensions.size();

    matrix<long> m(n, n);
    matrix<int> lastChange(n, n);

    optMatrix(dimensions, m, lastChange);
    
}