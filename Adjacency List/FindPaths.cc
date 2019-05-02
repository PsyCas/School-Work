#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits> 

#include "BinaryHeap.h"

using namespace std;

struct Vertex{
    string nodeName_;
    vector<Vertex> adjacent_;
    bool known_ = false;
    double distance_ = INT_MAX;				
	Vertex *previous_in_path_;
};

void getShortestPaths(vector<Vertex> *graphPtr, Vertex *startingVertex){

    startingVertex -> distance_ = 0;
    BinaryHeap<Vertex> pathfinder;

    for(size_t i = 0; i < graphPtr -> size(); ++i){

        cout << (*graphPtr)[i].nodeName_ << endl;
        cout << (*graphPtr)[i].distance_ << endl;
    }

    pathfinder.insert(*startingVertex);
        
        // while(true){

        //     if(pathfinder.)
        // }


}

void parseAndCreateAdjacencyList(const string &line, Vertex &newVertex){

    stringstream str_in(line);

    char nodeName;
    str_in >> nodeName;
    newVertex.nodeName_ = nodeName;

    char word; double weight;
    while(str_in >> word >> weight){
        Vertex newAdjacent;
        newAdjacent.nodeName_ = word;
        newAdjacent.distance_ = weight; 
        newVertex.adjacent_.push_back(newAdjacent);
    }
}


vector<Vertex> createNewGraph(const string &GRAPH_FILENAME){
    string elementSize; // stroes the total number of element nodes

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

    fin.close();
    return graph;
}

int main(int argc, char **argv){

    if(argc != 3){
        cout << "To implement, type: " << argv[0] << " <GRAPH_FILE> <STARTING_VERTEX>";
        return 0;
    }

    const string GRAPH_FILENAME(argv[1]); 
    const string STARTING_VERTEX(argv[2]);

    cout << "The input graph filename is: " << GRAPH_FILENAME << endl; 
    cout << "The starting vertex is: " << STARTING_VERTEX << endl; 

    vector<Vertex> graph = createNewGraph(GRAPH_FILENAME);
    vector<Vertex> *graphPtr = &graph;
    
    Vertex *startingVertex = new Vertex;

    for(size_t i = 0; i < graphPtr -> size(); ++i){
    
        if ((*graphPtr)[i].nodeName_ == STARTING_VERTEX){
            startingVertex = &(*graphPtr)[i];
            break;
        }; 
    }


    getShortestPaths(graphPtr, startingVertex);

    return 0;
}