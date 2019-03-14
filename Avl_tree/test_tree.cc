// Parakram Basnet
// Main file for Part2(b) of Homework 2.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream> 
#include <cmath>
using namespace std;

namespace {

  // parses through the recognition sequence of the line from file
  // returns true if a sequence can be extracted and false if not
  // line_val_mod is passed by reference and modified on every function call
  bool getNextRecognitionSequence(string& line_val_mod, string& a_reco_seq){

    string word = "";
    for(size_t i = 0; i < line_val_mod.length(); ++i){
        
        if(line_val_mod.length() == 1){
          return false;
        }

        else if (line_val_mod[i] == '/'){
          a_reco_seq = word;
          line_val_mod = line_val_mod.substr(i+1);
          return true;  
        }

        else word += line_val_mod[i];
    }
    return false;
  }

  // Function that returns the enzyme acronym from the file line
  // line_val_mod is passed by reference and modified on every function call
  string getEnzymeAcronym(string& line_val_mod){

    string final_val = "";
    size_t i = 0;
    
    for(i = 0; i < line_val_mod.length(); ++i){

      if(line_val_mod[i] == '/') break;
      else final_val += line_val_mod[i];
    }    
    line_val_mod = line_val_mod.substr(i+1);
    return final_val;
  }

  template <typename TreeType>
  void readFile(const string& db_filename, TreeType &a_tree){
    
    // opening the file
    ifstream fin(db_filename);
    string line_val = "";
    
    // removing first 10 junk lines from the file
    for(int i = 0; i < 10; ++i){
      getline(fin, line_val);
    }

    // taking input from the file.
    while(fin >> line_val){

      string line_val_mod = line_val;  // value that will be modified by passing its reference
      string an_enz_acronym = getEnzymeAcronym(line_val_mod);
      
      string a_reco_seq;    // stores the recognition sequence from the input line.

      // loop that runs while there is still recognition sequence in the db line.
      while (getNextRecognitionSequence(line_val_mod, a_reco_seq)){
        
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
    int node_num = a_tree.getNodeNum();
    float avg_depth = a_tree.getInternalPathLength()/ float(node_num);

    // log base 2 of n is log base e of n divided by log base e of 2
    float ratio =  avg_depth/(log(node_num)/ log(2));

    // setting up for part 4 and 5 by creating a vector to store the data
    vector<string> db_data;
    fstream fin(seq_filename);
    string db_line;

    while(fin >> db_line){
      db_data.push_back(db_line);
    }
    fin.close();

    // Variables for part 4, checking successful calls and average recursive calls
    int successful_queries = 0, all_queries = 0, number_of_recursive_calls = 0; 
    float avg_number_of_recursive_calls = 0;

    //variables for part 5. removing every other sequence from the tree
    int total_remove_calls = 0, successful_removes = 0,  remove_recursive_calls = 0;
    float avg_remove_recursive_calls = 0;
 
    for (size_t i = 0; i < db_data.size(); ++i){
      
      SequenceMap compare_sequence(db_data[i], "");

      // counting number of successful queries
      if(a_tree.contains(compare_sequence)){
         ++successful_queries;  // 4a
      }

      all_queries++;
      number_of_recursive_calls = a_tree.findRecursiveCalls(compare_sequence);
      avg_number_of_recursive_calls += number_of_recursive_calls; 
    }

    // question 5
    for(size_t i = 0; i< db_data.size(); ++i){

      SequenceMap compare_sequence(db_data[i], "");

      if(i %2 == 0){
          if(a_tree.contains(compare_sequence)) ++successful_removes; // 5a

          remove_recursive_calls = a_tree.remove(compare_sequence); // removing
          avg_remove_recursive_calls += remove_recursive_calls;
          ++total_remove_calls; // total number of calls
      }
    }

    avg_number_of_recursive_calls /= float(all_queries); 
    avg_remove_recursive_calls /= float(total_remove_calls);

    // Part 6
    int node_num_updated = a_tree.getNodeNum();
    float avg_depth_updated = a_tree.getInternalPathLength()/ float(node_num_updated);

    // log base 2 of n is log base e of n divided by log base e of 2
    float ratio_updated =  avg_depth_updated/(log(node_num_updated)/ log(2));

    cout << "2: " << node_num << endl;
    cout << "3a: " << avg_depth << endl;
    cout << "3b: " << ratio << endl;
    cout << "4a: " << successful_queries << endl;
    cout << "4b: " << avg_number_of_recursive_calls << endl;
    cout << "5a: " << successful_removes << endl;
    cout << "5b: " << avg_remove_recursive_calls << endl;
    cout << "6a: " << node_num_updated << endl;
    cout << "6b: " << avg_depth_updated << endl;
    cout << "6c: " << ratio_updated << endl;
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
