#include <iostream>

using namespace std;

int main(int argc, char** argv){

    if(argc != 2){
        cout << "Usage: " << argv[0] << " <dimensions_filename>" << endl;
        return 0;
    }

    const string text_filename(argv[1]);
    cout <<"The input file name is: " << text_filename << endl;

}