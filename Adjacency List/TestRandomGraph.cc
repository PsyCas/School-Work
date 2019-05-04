#include <iostream>
#include <vector> 
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "ListElement.h"
#include "disjoint_sets.h"

using namespace std;

void combineSets(DisjSets &newSet, int &N, const int &first, const int &second){

    cout << "First Index: "<<  first -1  << endl;
    cout << "Second Index: "<< second -1  << endl;


    // // cout << "First: " << newSet.find(first) << endl; 
    // // cout << "Second: " << newSet.find(second) << endl;
    vector<int> printVec = newSet.getVec();
    for(int num: printVec){
        cout << num << " ";
    }
    cout << endl;

    // // cout << "0: " << newSet.find(0) << endl; 
    // // cout << "1: " << newSet.find(1) << endl; 
    // // cout << "2: " << newSet.find(2) << endl; 
    // // cout << "3: " << newSet.find(3) << endl; 
    // // cout << "4: " << newSet.find(4) << endl; 
    // // cout << "5: " << newSet.find(5) << endl; 

    N = newSet.unionSets(first-1, second-1, N);

    printVec = newSet.getVec();
    for(int num: printVec){
        cout << num << " ";
    }
    cout << endl<< endl;

    cout << "The value of N is: " << N << endl;

    // N = newSet.getEdgeNum();

}

bool addEdges(vector<ListElement<int>> &graph, const int &first,const int &second){

    // cout << "First: " << graph[first -1].getElementName() << "  ";
    // cout << "First: " << first << endl;

    // cout << "Second: " << graph[second -1].getElementName() << "  ";
    // cout << "Second: " << second <<  endl << endl;

    bool isAdded = false;

    if(first != second){

        // index for the number being added is -1 the numbers generated
        if(!graph[first-1].checkConnection(second)){
            graph[first-1].addElement(second, 1);
            isAdded = true;
        }
        
        if(!graph[second-1].checkConnection(first)){
            graph[second-1].addElement(first, 1);
            isAdded = true;            
        }
    }

    return isAdded;
} 


int main(int argc, char **argv){
    // error handling for when the command is incomplete
    if(argc != 2){
        cout << "To implement, type: " << argv[0] << " <Maximum_number_of_nodes>";
        return 0;
    }
    
    // getting the maximum number of nodes from CLI input
    const string MAX_NODES(argv[1]);
    cout << "The maximum number of nodes is: " << MAX_NODES << endl;

    // converting input string to integer using string stream
    stringstream sstr(MAX_NODES);
    int N;
    sstr >> N;

    DisjSets newSet(N); // create a new set
    vector<ListElement<int>> graph; // creates a graph
    
    for(int i = 1; i <= N; i++){

        ListElement<int> newElement(i); // creating individual adjacent lists
        graph.push_back(newElement);
    }


    srand(time(0));
    int counter = N;    // limiter 

    while (N != 1) {           // while (N != 1)

        // cout << N << " ";
        const int first = rand() % counter + 1;    
        const int second = rand() % counter + 1;
        

        bool isAdded = addEdges(graph, first, second);
        if(isAdded) combineSets(newSet, N, first, second); 
    }

    // displays individual relationships in the list
    for(size_t i = 0; i < graph.size(); ++i){
        graph[i].displayList();
    }


    return 0;
}