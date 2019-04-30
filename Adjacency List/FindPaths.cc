#include <iostream>
#include <fstream>
#include <sstream>

#include "ListElement.h" 
#include "BinaryHeap.h"

using namespace std;

void getShortestPaths(const vector<ListElement<char>> &graph, const BinaryHeap<char> &heapStorage){

    return;
}

void parseAndCreateAdjacencyList(const string &line, ListElement<char> &newElement){

    stringstream str_in(line);

    char nodeName;
    str_in >> nodeName;
    newElement.setName(nodeName);

    char word; double weight;
    while(str_in >> word >> weight){
        newElement.addElement(word, weight);
    }
}


vector<ListElement<char>> createNewGraph(const string &GRAPH_FILENAME){
    string elementSize; // stroes the total number of element nodes

    ifstream fin(GRAPH_FILENAME);
    vector<ListElement<char>> graph;

    if(fin.fail()){
        cerr << "File " << GRAPH_FILENAME << " could not be opened due to an unknown error." << endl;
    }

    else{
        getline(fin, elementSize); // storing the total number of nodes from the first line

        string line;
        while( getline(fin, line)){
            ListElement<char> newElement;
            parseAndCreateAdjacencyList(line, newElement);
            graph.push_back(newElement);
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

    vector<ListElement<char>> graph = createNewGraph(GRAPH_FILENAME);
    
    vector<char> nodeNames;
    for(ListElement<char> nodes: graph){
        nodeNames.push_back(nodes.getElementName());
    }

    BinaryHeap<char> heapStorage(nodeNames);

    getShortestPaths(graph, heapStorage);

    return 0;
}