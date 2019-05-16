/*
 * optimal_multiplications.h
 * Name: Parakram Basnet
 * 
 * This file contains functions that will read input from a file, get the optimal order of matrix
 * multiplying two matrices given the input and display the order as well as the matrix
 * 
*/

// including necessary libraries 
#include <iostream>
#include <fstream>
#include <vector>
#include <climits> 

// include matrix class to store values
#include "matrix.h"

using namespace std;

// function that returns the order of optimal multiplication
void getOptimalOrder(int i, int j, int n, matrix<int> *bracket, char &name)
{ 
    if (i == j){
        cout << name;
        name++;
        return;
    }
    
    cout << "(";
    getOptimalOrder(i, (*bracket)[i][j], n,bracket, name);
    getOptimalOrder((*bracket)[i][j] + 1, j,n, bracket, name);
    cout << ")";
}

/**
 * CODE REFERENCED FROM: Data Structures and Algorithms in C++" by Mark Allen Weiss
 * 
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

/*
 * readDimensions reads the dimensions file and stores its contents in a vector passed by reference
*/
void readDimensions(const string &dimensions_file, vector<int>& dimensions){

    ifstream fin(dimensions_file);
    int dimensions_number = 0;

    while(fin >> dimensions_number){
        dimensions.push_back(dimensions_number);
    }
}

/*
 * main function of the file
 * Reads in the name of the input file and makes necessary calls to helper functions
 */
int main(int argc, char** argv){

    // validating input from the CLI 
    if(argc != 2){
        cout << "Usage: " << argv[0] << " <dimensions_filename>" << endl;
        return 0;
    }

    // getting input
    const string dimensions_file(argv[1]);
    cout <<"The input file name is: " << dimensions_file << endl << endl;

    // creating a vector of type int and calling a function to populate it 
    vector<int> dimensions;
    readDimensions(dimensions_file, dimensions);   // reads the dimensions from the input file.

    int n = dimensions.size();

    matrix<long> m(n, n);   // stores the computation of multiplication
    matrix<int> lastChange(n, n);   // stores the last change

    // calling helper function to generate the optimal multiplication 
    optMatrix(dimensions, m, lastChange);

    // initializing necessary variables to find the optimal order.
    char name = 'A';
    matrix<int> * lastChangep = &lastChange;

    cout << "The optimal order is: ";
    getOptimalOrder(1, dimensions.size()-1, dimensions.size(), lastChangep, name);

    return 0;
}