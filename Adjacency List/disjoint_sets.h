// disjoint_sets.h
// Modified by: Parakram Basnet
// Modification: Added include statement for disjoint_sets.cc as
// my compiler was having issues importing it through the header file.

/******* In case of a compile time error, remove #include "disjoint_sets.cc" and try again *******/ 


#ifndef DISJ_SETS_H
#define DISJ_SETS_H

// DisjSets class
//
// CONSTRUCTION: with int representing initial number of sets
//
// ******************PUBLIC OPERATIONS*********************
// void union( root1, root2 ) --> Merge two sets
// int find( x )              --> Return set containing x
// ******************ERRORS********************************
// No error checking is performed

#include <vector>
using namespace std;

/**
 * Disjoint set class.
 * Use union by rank and path compression.
 * Elements in the set are numbered starting at 0.
 */
class DisjSets
{
  public:
    explicit DisjSets( int numElements );

    int find( int x ) const;
    int find( int x );
    int unionSets( int root1, int root2, int N );

  private:
    vector<int> s;
};

#include "disjoint_sets.cc"   // added this line 
#endif
