/* CreateGraphAndTest.cc
 * Written by: Parakram Basnet
 * This program first reads in a file containing nodes, their adjacent vertices and weight of the edges 
 * Then, creates a graph of "List Elements" and stores them an adjacency list as a vector of List Elements. 
 * It then checks and displays the connections between element that are being passed as queries from an input file. 
*/

// including required libraries
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

// including classfile that stores node names and adjacent vertices
#include "ListElement.h"

using namespace std;

/* 
    * Function that takes in a string "line", parses it and adds elements to the vector    
    * newElement that is passed by reference. 
 */
void parseAndCreateAdjacencyList(const string &line, ListElement<char> &newElement){

    // creating a new string stream
    stringstream str_in(line);

    char nodeName;
    str_in >> nodeName;
    newElement.setName(nodeName);   // setting the name of the element

    // adding name and weight to the adjacency vector of "nodeName"
    char word; double weight;
    while(str_in >> word >> weight){
        newElement.addElement(word, weight);
    }
}

/*
    * Function that creates a new graph by parsing a file called GRAPH_FILENAME
    * The function returns a vector "graph" which is an adjacency list
    * that contains all the vertcies and their adjacency vectors. 
 */
vector<ListElement<char>> createNewGraph(const string &GRAPH_FILENAME){
    string elementSize; // stroes the total number of element nodes

    // creating a file stream
    ifstream fin(GRAPH_FILENAME);
    vector<ListElement<char>> graph;

    if(fin.fail()){
        cerr << "File " << GRAPH_FILENAME << " could not be opened due to an unknown error." << endl;
    }

    else{
        getline(fin, elementSize); // storing the total number of nodes from the first line

        string line;
        while( getline(fin, line)){
            ListElement<char> newElement;                   // creates a new List element for every line in the graph file
            parseAndCreateAdjacencyList(line, newElement);  // calls helper function to create adjacent vectors
            graph.push_back(newElement);                    // adds the element to adjacency list
        }
    }

    fin.close();    // closing file stream
    return graph;   // returning adjacency list
}

/*
    * This function creates a query from the provided file, checks the connection between all the query nodes
    * and displays whether the nodes are connected or not. If connected, it also gives their cost.
 */
void createQueryAndCheckConnection(const string &ADJACENCY_LIST_FILENAME, const vector<ListElement<char>> &graph){

    ifstream fin(ADJACENCY_LIST_FILENAME);

    if(fin.fail()){
        cerr << "File " << ADJACENCY_LIST_FILENAME << " could not be opened due to an unknown error." << endl;
        return;
    }

    char first, second;
    while(fin >> first >> second){
        
        // looping through each element in the adjacency list
        for(ListElement<char> elementNode: graph){
            if(elementNode.getElementName() == first){  
                if(elementNode.checkConnection(second)){    // checkConnection() checks the connection between two nodes
                    cout << first << " " << second << ": " << "Connected, weight of edge is " << "weight " << elementNode.getWeight(second) << endl;
                }
                else{
                    cout << first << " " << second << ": " << "Not connected" << endl;
                }
                break;
            }
        }
    }

    fin.close();    //closing file stream

}

/*
    * Main function that takes in two arguments from the cli, does error handling and calls helper function.
 */
int main(int argc, char **argv){

    if(argc != 3){
        cout << "To implement, type: " << argv[0] << " <DirectedGraphFile> <AdjacencyQueriesFile>" << endl;
        return 0;
    }

    const string GRAPH_FILENAME(argv[1]);
    const string ADJACENCY_LIST_FILENAME(argv[2]);

    cout << "The input graph filename is: " << GRAPH_FILENAME << endl;
    cout << "The input adjacency list filename is: " << ADJACENCY_LIST_FILENAME << endl << endl;

    // graph stores the graph containing the adjacency list
    vector<ListElement<char>> graph = createNewGraph(GRAPH_FILENAME);
    createQueryAndCheckConnection(ADJACENCY_LIST_FILENAME, graph);

    return 0;
}