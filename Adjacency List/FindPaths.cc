#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "ListElement.h" 
#include "BinaryHeap.h"

using namespace std;

struct Vertex{
    string nodeName_;
    vector<Vertex> adjacent_;
    bool known_;
    double distance_;				
	Vertex *previous_in_path_;
};

void getShortestPaths(const vector<ListElement<char>> &graph, const BinaryHeap<char> &heapStorage){

    return;
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
    
    for(Vertex newVert: graph){

        cout << newVert.nodeName_ << " Adjacent: " << endl;
        for(auto i = newVert.adjacent_.begin(); i !=  newVert.adjacent_.end(); ++i){
            cout << i -> nodeName_ << " weight: " << i -> distance_ << endl;
        }
        cout << endl;
    }


    // vector<char> nodeNames;
    // for(ListElement<char> nodes: graph){
    //     nodeNames.push_back(nodes.getElementName());
    // }

    // BinaryHeap<char> heapStorage(nodeNames);

    // getShortestPaths(graph, heapStorage);

    return 0;
}