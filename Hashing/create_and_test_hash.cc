// Parakram Basnet
// create_and_test_hash.cc creates hash tables for three different types of probing - linear, quadaratic and double hash
// It then displays different statistitcs like collisions, average collisions, and so on.


#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hash.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// readWordAndCreateTable reads words from words_filename and creates a hash table using it.
template <typename HashTableType>
void readWordAndCreateTable(HashTableType &hash_table, const string &words_filename){

  ifstream fin(words_filename);
  string word = "";
  while(fin >> word){
    hash_table.Insert(word);
  }

  fin.close();
}

//readQueryAndPrint reads words from query_filename and searches for it in the hash table.
// It also displays the number of probes and whether the word was found or not
template <typename HashTableType>
void readQueryAndPrint(HashTableType &hash_table, const string &query_filename){

  ifstream fin(query_filename);
  string word = "";
  cout << endl;

  while(fin >> word){
    if(hash_table.Find(word)){
      cout << word << ": Found in " << hash_table.GetProbes() << " probes" << endl;
    }
    else{
      cout << word << ": Not found in " << hash_table.GetProbes() << " probes" << endl;
    }
  }

  fin.close();
}

// TestFuntionForHashTable tests different hash tables and displays statistics on them
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();

  // ..Insert your own code
  readWordAndCreateTable(hash_table, words_filename);
  int itemCount = hash_table.GetItemCount();
  int tableSize = hash_table.GetTableSize();
  int collisions = hash_table.GetCollisions(); 
  double loadFactor = itemCount/double(tableSize);
  double avgCollisions = collisions/double(itemCount);

  cout << "Collisions: " << collisions << endl;                   // number of collissions during pribing
  cout << "Number of items: " << itemCount << endl;               // total number of items in the table
  cout << "Size of hash table: " << tableSize << endl;            // Size of the hash table
  cout << "Load factor: " << loadFactor << endl;                  // The load factor of the table
  cout << "Avg. number of collisions: " << avgCollisions << endl; // The average number of collisions during probing
  
  // searches for words from query_filename
  readQueryAndPrint(hash_table, query_filename);            
}

// Sample main for program create_and_test_hash
int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
  } 
  
  else if (param_flag == "quadratic") {
    HashTableQuadratic<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    
  } 
  
  else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);    
  }
  
  else {
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
