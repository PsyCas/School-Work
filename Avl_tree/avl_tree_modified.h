// Edited by: Parakram Basnet
// This file is edited for part 2(c)
// double rotations have been modified to be independent functions that dont call single rotation

/*  Edited functions:

    public:
        void insert( const Comparable & x )
        void insert( Comparable && x )
        int remove( const Comparable & x ) 

    private:
        int remove( const Comparable & x, AvlNode * & t )
        void doubleWithLeftChild( AvlNode * & k3 )
        void doubleWithRightChild( AvlNode * & k1 )

    Additional Functions:
    public:
        Comparable find(const Comparable& x)
        int getNodeNum()
        int getInternalPathLength()
        int findRecursiveCalls(const Comparable &x)

    private:
        int getNodeNum(AvlNode * t)
        float getInternalPathLength(AvlNode * t)
        int findRecursiveCalls(const Comparable &x, AvlNode * t)
        int findRecursiveCalls(const Comparable &x, AvlNode * t)
*/

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted


template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root{ nullptr }
      { }
    
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x) const
    {
        return contains( x, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     * Edited to merge duplicate values 
     */
    void insert( const Comparable & x )
    {
        // if the element is already in the tree, update it
        if(contains(x)){
            Comparable * new_node = find(x, root);
            new_node -> Merge(x);
        }

        else{
            insert( x, root );
        }
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     * * Edited to Merge duplicate values
     */
    void insert( Comparable && x )
    {   
        // if the element is already in the tree, update it
        if(contains(x)){
            Comparable * new_node = find(x, root);
            new_node -> Merge(x);
        }
        else{
            insert( std::move( x ), root );
        }
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     * EDITED to return the total number of recurive calls made by remove
     */
    int remove( const Comparable & x )
    {
        return remove( x, root );        
    }

    /*
     * Finds the Comparable x in the tree and returns the Comparable.
     * Precondition: x exists in the tree
    */
    Comparable find(const Comparable& x){
        
        return *(find(x, root));
    }

    /*
     * Counts the total number of nodes in the tree and returns it 
    */
    int getNodeNum(){
        return getNodeNum(root);
    }

    /*
     * Calculates the internal path length and returns it 
    */
    int getInternalPathLength(){
        return getInternalPathLength(root);
    }

    /*
     * Counts the total number of recursive calls made to find Comparable x and returns it 
    */
    int findRecursiveCalls(const Comparable &x){

        return findRecursiveCalls(x, root);
    }

  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;

    /*
     *  Counts and eturns the total number of nodes in the tree 
    */    int getNodeNum(AvlNode * t){

        if(t == nullptr){
            return 0;
        }
        else{
            return (1+ getNodeNum(t->left) + getNodeNum(t->right)); 
        }
    }

    /*
     *  Calculates and returns the internal path length of the tree  
    */    float getInternalPathLength(AvlNode * t){

        if(t == nullptr){
            return 0;
        }
        else{
            return (getInternalPathLength(t->left) + getInternalPathLength(t -> right) + getNodeNum(t) -1);
        }
    }

    // returns the total number of recursive calls made to find a node.
    int findRecursiveCalls(const Comparable &x, AvlNode * t){

        if( t == nullptr )
            return 0;
        
        else if( x < t->element )
            return (1 + findRecursiveCalls( x, t->left));
        
        else if( t->element < x )
            return (1 + findRecursiveCalls( x, t->right));

        else
            return 1;    // Match
    }

    /*
     *  Pre-condition: Comparable exists in the tree. The public function "find" checks it.
     *  Finds the Comparable x in the tree and returns it as a pointer
    */
    Comparable * find(const Comparable &x, AvlNode * & t){
        
        if( x < t->element )
            return find( x, t->left);
        else if( t->element < x )
            return find( x, t->right);
        else{
            return &(t->element);    // Match
        }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        
        balance( t );
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    int remove( const Comparable & x, AvlNode * & t )
    {
        int num = 0;    // stores the extra number of calls after the node is found

        if( t == nullptr )
            return 0;   // Item not found; do nothing
        
        if( x < t->element )
            return (1 + remove( x, t->left));
        else if( t->element < x )
            return (1 + remove( x, t->right));
        
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin(t->right)->element;  
            num = remove(t->element, t->right) + 1;     // +1 for the current execution call
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
        
        balance(t);
        return num + 1; // +1 is for the function call when node is found
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        } else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
	}
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
    
        return findMin( t->left);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        if( t == nullptr )
            return false;
        
        else if( x < t->element )
            return contains( x, t->left);
        
        else if( t->element < x )
            return contains( x, t->right);
        
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     * 
     * EDITED so that it does not calls the two single rotation functions
     * Subtrees are moved to their correct position and heights are recalculated 
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {

        AvlNode* k1 = k3 -> left;
        AvlNode* k2 = k1 -> right;

        // moving subtree B to be the right child of parent node
        k1 -> right = k2 -> left;
        k2 -> left = k1;

        // moving subtree C to be the left child of the grandparent node
        k3 -> left = k2 -> right;
        k2 -> right = k3;

        // recalculating heights
        k3->height = max( height( k3->left ), height( k3->right ) ) + 1;
        k1->height = max( height( k1->right), height(k1 -> left) ) + 1;
        k2->height = max( height(k1), height(k3) ) + 1;
        
        k3 = k2;
        // rotateWithRightChild( k3->left );
        // rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     * 
     * EDITED so that it does not calls the two single rotation functions
     * Subtrees are moved to their correct position and heights are recalculated
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        AvlNode* k3 = k1 -> right;
        AvlNode* k2 = k3 -> left;

        // moving subtree C to be the left child of parent node
        k3 -> left = k2 -> right;
        k2 -> right = k3;

        // moving subtree B to be the right child of the grandparent node
        k1 -> right = k2 -> left;
        k2 -> left = k1;

        // recalculating heights
        k3->height = max( height( k3->left ), height( k3->right ) ) + 1;
        k1->height = max( height( k1->right), height(k1 -> left) ) + 1;
        k2->height = max( height(k1), height(k3) ) + 1;
        
        k1 = k2;

        // rotateWithLeftChild( k1->right );
        // rotateWithRightChild( k1 );
    }
};

#endif