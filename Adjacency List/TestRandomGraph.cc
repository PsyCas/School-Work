#include <iostream>
#include <vector> 
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <climits>

#include "ListElement.h"
#include "disjoint_sets.h"

using namespace std;

void combineSets(DisjSets &newSet, int &N, const int &first, const int &second){
    N = newSet.unionSets(first-1, second-1, N);
}

bool addEdges(vector<ListElement<int>> &graph, const int &first,const int &second){

    bool isAdded = false;

    if(first != second){

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
    int counter = N;        // copy of N
    int numberOfEdges = 0; 

    while (N != 1) {

        const int first = rand() % counter + 1;    
        const int second = rand() % counter + 1;
        

        bool isAdded = addEdges(graph, first, second);
        if(isAdded){
            combineSets(newSet, N, first, second);
            numberOfEdges++;
        }  
    }

    int smallestOutDegree = INT_MAX, largestOutDegree = INT_MIN;
    double averageOutDegree = 0;
    
    // displays individual relationships in the list
    for(size_t i = 0; i < graph.size(); ++i){
        
        int outDegree = graph[i].getListSize();
        averageOutDegree += outDegree;

        if(outDegree < smallestOutDegree) smallestOutDegree = outDegree;
        if(outDegree > largestOutDegree) largestOutDegree = outDegree;

        // *********** Uncomment this to display all the adjacent relationships ****************
        // graph[i].displayList(); 
    }

    averageOutDegree = averageOutDegree/ graph.size();

    cout << "The total number of edges is: " << numberOfEdges << endl;
    cout << "The smallest out degree is: " << smallestOutDegree << endl;
    cout << "The largest out degree is: " << largestOutDegree << endl;
    cout << "The average out degree is: " << averageOutDegree << endl;

    return 0;
}