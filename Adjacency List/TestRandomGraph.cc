#include <iostream>
#include <vector> 
#include <cstdlib>
#include <ctime>

using namespace std;


int main(int argc, char **argv){

    // error handling for when the command is incomplete
    if(argc != 2){
        cout << "To implement, type: " << argv[0] << " <Maximum_number_of_nodes>";
        return 0;
    }
    
    // getting the maximum number of nodes from CLI input
    const N(argc[1]);

    cout << "The maximum number of nodes is: " << N << endl;



    return 0;
}