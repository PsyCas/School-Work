#include <iostream>
#include <vector> 
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "ListElement.h"
#include "disjoint_sets.h"

using namespace std;


void addEdges(vector<ListElement<int>> &graph, int first, int second){

    cout << "First: " << graph[first -1].getElementName() << "  ";
    cout << first << endl;

    cout << "Second: " << graph[second -1].getElementName() << "  ";
    cout << second << endl << endl;

    if(first != second){
        
        // index for the number being added is -1 the numbers generated
        if(!graph[first-1].checkConnection(second)) graph[first-1].addElement(second, 1);
        if(!graph[second-1].checkConnection(first))graph[second-1].addElement(first, 1);
    }
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
    int counter = 0;    // limiter 

    while (counter < N) {
        const int first = rand() % N + 1;
        // cout << first << endl;
    
        const int second = rand() % N + 1;
        // cout << second << endl;
        // cout << endl;
        
        addEdges(graph, first, second);


        counter++;
    }

    // displays individual relationships in the list
    for(size_t i = 0; i < graph.size(); ++i){
        graph[i].displayList();
    }


    return 0;
}