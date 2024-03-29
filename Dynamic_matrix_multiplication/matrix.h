/*
 * matrix.h
 * Modified by: Parakram Basnet 
 * Code referenced from: "Data Structures and Algorithms in C++" by Mark Allen Weiss 
 * 
 * This file contains the matrix class that contains functions and methods to simulate a matrix
 * 
 * Modification: Added an extra function 
 *      void displayMatrix() 
 * that displays the matrix.
 */


#ifndef MATRIX_H2
#define MATRIX_H34

#include <vector>

using namespace std;

template <typename Object>
class matrix{
    
    public:
        
        matrix( int rows, int cols ) : array( rows )
        {
            for( auto & thisRow : array )
                thisRow.resize( cols );
        }
        
        matrix( vector<vector<Object>>v ) : array{ v }
        {}
        
        matrix( vector<vector<Object>> &&v):array{ std::move( v ) }
        {}
        
        const vector<Object> & operator[]( int row ) const
        { return array[ row ]; }
        
        vector<Object> & operator[]( int row )
        
        { return array[ row ]; }
        
        int numrows( ) const
        { return array.size( ); }
        
        int numcols( ) const
        { return numrows( ) ? array[ 0 ].size( ) : 0; }

        void displayMatrix() const {

            for(auto i: array){
                for(auto j: i){

                    cout << j  << " ";
                }
                cout << endl;
            }
        }
        
    private:
        
        vector<vector<Object>> array;
};
    
#endif