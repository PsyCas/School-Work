#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits> 
#include <stack>
#include <iomanip>
#include <cctype>

#include "BinaryHeap.h"

using namespace std;

struct Vertex{
    string nodeName_;
    vector<Vertex> adjacent_;
    bool known_ = false;
    double distance_ = INT_MAX;				
	string previous_in_path_;
};

Vertex* getNode(vector<Vertex> *graphPtr, const string &nodeName){

    for(size_t i = 0; i < graphPtr -> size(); ++i){
        if((*graphPtr)[i].nodeName_ == nodeName) return &(*graphPtr)[i];
    }
}

void printPaths(vector<Vertex> *graphPtr, const string &startingPoint){

    for(size_t i = 0; i < graphPtr -> size(); ++i){

        string finalOp = (*graphPtr)[i].nodeName_ + ":";
        stack<string> pathStack;

        string path = (*graphPtr)[i].previous_in_path_;
        
        if(path == ""){
            path = startingPoint;
            pathStack.push(path);
        } 
        else{
            pathStack.push((*graphPtr)[i].nodeName_);
            pathStack.push(path);
        }

        while(path != startingPoint){

            Vertex *n = getNode(graphPtr, path);
            path = n -> previous_in_path_;
            pathStack.push(path);
        }

        while(!pathStack.empty()){
            finalOp += pathStack.top() + ", ";
            pathStack.pop();
        }

        if((*graphPtr)[i].distance_ == INT_MAX){
            cout << finalOp << "Cost: " << (*graphPtr)[i].distance_ << setprecision(1) << fixed << ". NO PATH" << endl;            
        }
        else{
            cout << finalOp << "Cost: " << (*graphPtr)[i].distance_ << setprecision(1) << fixed << "." << endl;
        }
    }

}

void getShortestPaths(vector<Vertex> *graphPtr, Vertex *startingVertex){

    startingVertex -> distance_ = 0;
    BinaryHeap<Vertex> pathfinder;

    pathfinder.insert(*startingVertex);
        
    while(true){

        if(pathfinder.isEmpty()) break;

        Vertex vNode = pathfinder.findMin();
        pathfinder.deleteMin();
        Vertex *v = getNode(graphPtr, vNode.nodeName_);

        if(!v -> known_){
            for(size_t i = 0; i < v ->adjacent_.size(); ++i){
                if(!v-> adjacent_[i].known_){
                    Vertex *w = getNode(graphPtr, v -> adjacent_[i].nodeName_);

                    if(v -> distance_ + v -> adjacent_[i].distance_ < w -> distance_){
                        w -> distance_ = v -> distance_ + v -> adjacent_[i].distance_;
                        pathfinder.insert(*w);
                        w -> previous_in_path_ = v -> nodeName_;
                        v -> adjacent_[i].known_ = true;
                    }
                }
            }
        }
        v -> known_ = true;
    }

    printPaths(graphPtr, startingVertex -> nodeName_);

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