// Parakram Basnet
// Main file for Part2(a) of Homework 2.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace {

  // parses through the recognition sequence of the line from file
  // returns true if a sequence can be extracted and false if not
  // lineValMod is passed by reference and modified on every function call
  bool getNextRecognitionSequence(string& lineValMod, string& a_reco_seq){

    string word = "";
    for(size_t i = 0; i < lineValMod.length(); ++i){
        
        if(lineValMod.length() == 1){
          return false;
        }

        else if (lineValMod[i] == '/'){
          a_reco_seq = word;
          lineValMod = lineValMod.substr(i+1);
          return true;  
        }

        else word += lineValMod[i];
    }
    return false;
  }

  // Function that returns the enzyme acronym from the file line
  // lineValMod is passed by reference and modified on every function call
  string getEnzymeAcronym(string& lineValMod){

    string finalVal = "";
    size_t i = 0;
    
    for(i = 0; i < lineValMod.length(); ++i){

      if(lineValMod[i] == '/') break;
      else finalVal += lineValMod[i];
    }    
    lineValMod = lineValMod.substr(i+1);
    return finalVal;
  }


  // @db_filename: an input filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be
  //  empty.
  template <typename TreeType>
  void QueryTree(const string &db_filename, TreeType &a_tree) {

    // opening the file
    ifstream fin(db_filename);
    string lineVal = "";
    
    // removing first 10 junk lines from the file
    for(int i = 0; i < 10; ++i){
      getline(fin, lineVal);
    }

    // taking input from the file.
    while(fin >> lineVal){

      string lineValMod = lineVal;
      string an_enz_acronym = getEnzymeAcronym(lineValMod);
      
      string a_reco_seq;    // stores the recognition sequence from the input line.

      // loop that runs while there is still recognition sequence in the db line.
      while (getNextRecognitionSequence(lineValMod, a_reco_seq)){
        
        SequenceMap new_sequence_map(a_reco_seq, an_enz_acronym);
        a_tree.insert(new_sequence_map);
      }
    }

    fin.close();  // closing the file stream
  }

}  // end namespace

//argc is the number of arguments passed in the terminal
//argv is the value of the argument in the form of an array
int main(int argc, char **argv) {
  
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  
  const string db_filename(argv[1]);
  
  cout << "Input filename is " << db_filename << endl;
 
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);
  return 0;
}
