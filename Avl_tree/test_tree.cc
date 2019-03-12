// Parakram Basnet
// Main file for Part2(b) of Homework 2.

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

  template <typename TreeType>
  void readFile(const string& db_filename, TreeType &a_tree){
    
    // opening the file
    ifstream fin(db_filename);
    string lineVal = "";
    
    // removing first 10 junk lines from the file
    for(int i = 0; i < 10; ++i){
      getline(fin, lineVal);
    }

    // taking input from the file.
    while(fin >> lineVal){

      string lineValMod = lineVal;  // value that will be modified by passing its reference
      string an_enz_acronym = getEnzymeAcronym(lineValMod);
      
      string a_reco_seq;    // stores the recognition sequence from the input line.

      // loop that runs while there is still recognition sequence in the db line.
      while (getNextRecognitionSequence(lineValMod, a_reco_seq)){
        
        SequenceMap new_sequence_map(a_reco_seq, an_enz_acronym);
        a_tree.insert(new_sequence_map);
      }
    }

    fin.close();  // closes the file stream
  }

  // @db_filename: an input database filename.
  // @seq_filename: an input sequences filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be
  //  empty.
  template <typename TreeType>
  void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {

    readFile(db_filename, a_tree);
    cout << "2: " << a_tree.getNodeNum() << endl;

  }

}  // namespace


int main(int argc, char **argv) {
  
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);

  return 0;
}
