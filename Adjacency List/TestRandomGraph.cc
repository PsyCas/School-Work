#include <iostream>
#include <vector> 
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "disjoint_sets.h"

using namespace std;

int main(int argc, char **argv){
    // error handling for when the command is incomplete
    if(argc != 2){
        cout << "To implement, type: " << argv[0] << " <Maximum_number_of_nodes>";
        return 0;
    }
    
    // getting the maximum number of nodes from CLI input
    const string MAX_NODES(argv[1]);
    cout << "The maximum number of nodes is: " << MAX_NODES << endl;

    stringstream sstr(MAX_NODES);
    int N;
    sstr >> N;

    DisjSets newSet(N); // create a new set
    
    srand(time(0));
    int counter = 0;
    // while (true) {
    //     const int random_variable = rand() % maximum_value + 1;
    //     cout << random_variable << endl;
    // }


    return 0;
}