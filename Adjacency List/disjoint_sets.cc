/*
 * disjoint_sets.cc
 * Modified by: Parakram Basnet
 * Modification:
 *              1) In function unionSets, added third parameter N that counts the number of sets in vector "s"
*/


#include "disjoint_sets.h"

/**
 * Construct the disjoint sets object.
 * numElements is the initial number of disjoint sets.
 */
DisjSets::DisjSets( int numElements ) : s( numElements, -1 )
{
}

/**
 * Union two disjoint sets.
 * For simplicity, we assume root1 and root2 are distinct
 * and represent set names.
 * root1 is the root of set 1.
 * root2 is the root of set 2.
 */
int DisjSets::unionSets( int root1, int root2, int N )
{
    if( s[ root2 ] < s[ root1 ] ){  // root2 is deeper
        if(s[root1] < 0) N-=1;
        s[ root1 ] = root2;
        return N;      
    }  // Make root2 new root
    else
    {
        if( s[ root1 ] == s[ root2 ] ){
            if(s[root1] == 0) N += 1;
            --s[ root1 ];          // Update height if same
        }
        if(s[root2] < 0) N -= 1;
        s[ root2 ] = root1;        // Make root1 new root
        return N;
    }
}


/**
 * Perform a find.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSets::find( int x ) const
{
    if( s[ x ] < 0 )
        return x;
    else
        return find( s[ x ] );
}


/**
 * Perform a find with path compression.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSets::find( int x )
{   
    if( s[ x ] < 0 )
        return x;
    else
        return s[ x ] = find( s[ x ] );
}

