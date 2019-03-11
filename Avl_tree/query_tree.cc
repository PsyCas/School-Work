// Parakram Basnet
// Main file for Part2(a) of Homework 2.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace {

  bool getNextRecognitionSequence(string& lineValMod, string& a_reco_seq){

    string word = "";

    for(size_t i = 0; i < lineValMod.length(); ++i){
        
        if (lineValMod[i] == '/' && lineValMod[i+1] != '/'){          
          a_reco_seq = word;
          lineValMod = lineValMod.substr(i);
          return true;  
        }

        else if(lineValMod[i] == '/' && lineValMod[i+1] != '/'){
          return false;
        }
        else word += lineValMod[i];
    }

    return false;
  }

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

      string a_reco_seq;

      while (getNextRecognitionSequence(lineValMod, a_reco_seq)){
        
        cout << a_reco_seq << endl;
        SequenceMap new_sequence_map(a_reco_seq, an_enz_acronym);
        a_tree.insert(new_sequence_map);
      }

    }

    fin.close();
  }

}  // namespace

//argc is the number of arguments passed in the terminal
//argv is the value of the argument in the form of an array
int main(int argc, char **argv) {
  
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  
  const string db_filename(argv[1]);
  
  cout << "Input filename is " << db_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
 
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);
  return 0;
}
