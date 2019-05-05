/*
 * FindPaths.cc
 * Written by: Parakram Basnet
 * 
 * This file implements Dijkstra's greedy algorithm to find the shortest paths. 
 * FindPaths.cc creates a graph from an input file and then returns the shortest path from an input node 
 * to every node in the graph and then displays the paths.   
 */

// including necessary files
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>  // for "INFINITY" weights
#include <stack>    // for final path output
#include <iomanip>  // to display weights with precision

// Uses binary heap to find the minimum paths
#include "BinaryHeap.h"

using namespace std;

// Vertex struct that stores the names and adjacent items for every node
struct Vertex{
    string nodeName_;
    vector<Vertex> adjacent_;
    bool known_ = false;
    double distance_ = INT_MAX;				
	string previous_in_path_;
};

/*
 * Helper function that takes the adjacency list "graphPtr" and returns a pointer pointing to the node for string "nodeName" 
 */
Vertex* getNode(vector<Vertex> *graphPtr, const string &nodeName){

    for(size_t i = 0; i < graphPtr -> size(); ++i){
        if((*graphPtr)[i].nodeName_ == nodeName) return &(*graphPtr)[i];
    }
}

/*
 * Helper function for getShortestPaths that prints the final paths found using Dijkstra
 * This function visits every adjacent nodes and follows their paths using pervious_in_path and stores them 
 * in a stack. When printing, the stack is parsed normally which gives the path in the correct form.
 */
void printPaths(vector<Vertex> *graphPtr, const string &startingPoint){

    // for every node in graph
    for(size_t i = 0; i < graphPtr -> size(); ++i){

        string finalOp = (*graphPtr)[i].nodeName_ + ":";    // accumulates the final output
        stack<string> pathStack;                            // stack that stores the path

        string path = (*graphPtr)[i].previous_in_path_;     // gets the path
        
        // when there is no path, the path is the starting point 
        if(path == ""){
            path = startingPoint;
            pathStack.push(path);
        } 
        else{
            pathStack.push((*graphPtr)[i].nodeName_);
            pathStack.push(path);
        }

        // loops until they find a path to the starting point.
        while(path != startingPoint){

            Vertex *n = getNode(graphPtr, path);  
            path = n -> previous_in_path_;
            pathStack.push(path);
        }

        // moving through each element in the stack and accumulating them in the final output
        while(!pathStack.empty()){
            finalOp += pathStack.top() + ", ";
            pathStack.pop();
        }

        // if there is no path from the starting point, it print the INT_MAX value and mentions that there is no path
        if((*graphPtr)[i].distance_ == INT_MAX){
            cout << finalOp << "Cost: " << (*graphPtr)[i].distance_ << setprecision(1) << fixed << ". NO PATH" << endl;            
        }
        // else it gives the path and its total cost
        else{
            cout << finalOp << "Cost: " << (*graphPtr)[i].distance_ << setprecision(1) << fixed << "." << endl;
        }
    }

}


/*
 * Function that implements dijkstra's algorithm to find the shortest paths.
 * Creates a binary heap and inserts all the adjacent variables in order of their weights
 * Then the heap is emptied using deleteMin() and updated based on the adjacent vertices of the vertex
 * that is visited. The loop continues until the heap is finally empty. 
 */
void getShortestPaths(vector<Vertex> *graphPtr, Vertex *startingVertex){

    startingVertex -> distance_ = 0;    // setting the distance of starting vertex to be 0
    BinaryHeap<Vertex> pathfinder;      // Creating binary heap object of type Vertex

    pathfinder.insert(*startingVertex); // inserting the first element to the heap
        
    while(true){

        if(pathfinder.isEmpty()) break; // break case -  only satisfied when the heap is completely empty.

        Vertex vNode = pathfinder.findMin();    // finds the min of the heap and stores it
        pathfinder.deleteMin();                 // deletes the min from the heap
        Vertex *v = getNode(graphPtr, vNode.nodeName_); // fetches pointer to node from graph using a helper funtion

        if(!v -> known_){
            for(size_t i = 0; i < v ->adjacent_.size(); ++i){      // loops through all the adjacent nodes for v
                if(!v-> adjacent_[i].known_){
                    Vertex *w = getNode(graphPtr, v -> adjacent_[i].nodeName_);

                    if(v -> distance_ + v -> adjacent_[i].distance_ < w -> distance_){
                        w -> distance_ = v -> distance_ + v -> adjacent_[i].distance_;
                        pathfinder.insert(*w);                      // inserting vertices according to their weight
                        w -> previous_in_path_ = v -> nodeName_;
                        v -> adjacent_[i].known_ = true;
                    }
                }
            }
        }
        v -> known_ = true;
    }

    // helper function that prints all the paths 
    printPaths(graphPtr, startingVertex -> nodeName_);

}

/* 
    * Function that takes in a string "line", parses it and adds values to the element    
    * Vertex that is passed by reference. 
 */
void parseAndCreateAdjacencyList(const string &line, Vertex &newVertex){

     // creating a new string stream
    stringstream str_in(line);

    char nodeName;
    str_in >> nodeName;
    newVertex.nodeName_ = nodeName;     // setting the name of the element

    // adding name and weight to the adjacency vector of "nodeName"
    char word; double weight;
    while(str_in >> word >> weight){
        Vertex newAdjacent;
        newAdjacent.nodeName_ = word;
        newAdjacent.distance_ = weight; 
        newVertex.adjacent_.push_back(newAdjacent);
    }
}

/*
    * Function that creates a new graph by parsing a file called GRAPH_FILENAME
    * The function returns a vector "graph" which is an adjacency list
    * that contains all the vertcies and their adjacency vectors. 
 */
vector<Vertex> createNewGraph(const string &GRAPH_FILENAME){
    string elementSize; // stroes the total number of element nodes

    // creating a file stream
    ifstream fin(GRAPH_FILENAME);
    vector<Vertex> graph;

    if(fin.fail()){
        cerr << "File " << GRAPH_FILENAME << " could not be opened due to an unknown error." << endl;
    }

    else{
        getline(fin, elementSize); // storing the total number of nodes from the first line

        string line;
        while( getline(fin, line)){
            Vertex newVertex;
            parseAndCreateAdjacencyList(line, newVertex);
            graph.push_back(newVertex);
        }
    }

    fin.close();    // closing file stream
    return graph;   // returning adjacency list
}

/*
 * Main function that takes in inputs from the CLI and stores it in variables.
 * It then creates a graph using helper functions, creates a new vertex using Struct, finds the starting vertex in
 * the adjacency graph and supplies it to another helper function that finds the shortest paths. 
 */
int main(int argc, char **argv){

    if(argc != 3){
        cout << "To implement, type: " << argv[0] << " <GRAPH_FILE> <STARTING_VERTEX>";
        return 0;
    }

    const string GRAPH_FILENAME(argv[1]); 
    const string STARTING_VERTEX(argv[2]);

    cout << "The input graph filename is: " << GRAPH_FILENAME << endl; 
    cout << "The starting vertex is: " << STARTING_VERTEX << endl; 

    vector<Vertex> graph = createNewGraph(GRAPH_FILENAME);  // creates a new graph and stores it in "graph"
    vector<Vertex> *graphPtr = &graph;  // creating a pointer for graph as it will be manipulated in other functions
    
    // starting vertex stores the reference to the vertex in "graph" that is the starting point supplied by the user 
    Vertex *startingVertex = new Vertex;

    // loop sets the starting vertex
    for(size_t i = 0; i < graphPtr -> size(); ++i){
    
        if ((*graphPtr)[i].nodeName_ == STARTING_VERTEX){
            startingVertex = &(*graphPtr)[i];
            break;
        }; 
    }

    // function that implements dijkstra and gets the shortest paths 
    getShortestPaths(graphPtr, startingVertex);

    return 0;
}