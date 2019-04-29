#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "ListElement.h"

using namespace std;

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

void createQueryAndCheckConnection(const string &ADJACENCY_LIST_FILENAME, const vector<ListElement<char>> &graph){

    ifstream fin(ADJACENCY_LIST_FILENAME);

    if(fin.fail()){
        cerr << "File " << ADJACENCY_LIST_FILENAME << " could not be opened due to an unknown error." << endl;
        return;
    }

    char first, second;
    while(fin >> first >> second){
        
        for(ListElement<char> elementNode: graph){
            if(elementNode.getElementName() == first){  
                if(elementNode.checkConnection(second)){
                    cout << first << " " << second << ": " << "Connected, weight of edge is " << "weight " << elementNode.getWeight(second) << endl;
                }
                else{
                    cout << first << " " << second << ": " << "Not connected" << endl;
                }
                break;
            }
        }
    }

}

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

    // for(ListElement<char> list: graph){
    //     list.displayList();
    //     cout << endl;
    // }

    return 0;
}