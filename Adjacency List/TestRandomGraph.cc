/* TestRandomGraph.cc
 * Written by: Parakram Basnet
 *
 * This program generates a graph of N random vertices and keeps adding edges to it until there is only one set remaining
 * To keep track of the number of sets, this program uses "disjoint_sets.h" and to make vertices, it uses "ListElement.h"    
*/

// importing necessary libraries
#include <iostream>
#include <vector> 
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <climits>

// importing necessary files
#include "ListElement.h"
#include "disjoint_sets.h"

using namespace std;

/*
 * Function that does a union of sets first-1 and second-1
 * This was created as a function because first and second are constants outside of it
 */
void combineSets(DisjSets &newSet, int &N, const int &first, const int &second){
    N = newSet.unionSets(first-1, second-1, N);
}

/*
 * This function adds edges between "first" and "second" to the "graph" that is passed as a parameter.
 * @param:  graph: the adjacency list
 *          first: a random number s.t. 1 <= first <= N    
 *          second: a random number s.t. 1 <= second <= N
 * @return: bool: True if successful, False if not    
 */
bool addEdges(vector<ListElement<int>> &graph, const int &first,const int &second){

    bool isAdded = false;

    // makes sure there is no connection between the same number
    if(first != second){

        if(!graph[first-1].checkConnection(second)){    // checks for unique connection
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

/*
 * Main function that takes in the max nodes N from the CLI.
 * Then, it creates object for disjoint sets and an adjacency list.
 * It then generates two random numbers s.t. 1 <= random num <= N and calls helper function addEdge to 
 * add edges to the graph until there is only one set remaining in the disjoint set.
 * After completion, it displays the fillowing:
 *              1. total number of edges
 *              2. smallest outdegree 
 *              3. largest outdegree 
 *              4. average outdegree 
 */
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

    // displaying the results
    cout << "The total number of edges are: " << numberOfEdges << endl;
    cout << "The smallest out degree is: " << smallestOutDegree << endl;
    cout << "The largest out degree is: " << largestOutDegree << endl;
    cout << "The average out degree is: " << averageOutDegree << endl;

    return 0;
}