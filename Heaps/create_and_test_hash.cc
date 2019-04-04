// Parakram Basnet.

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hash.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename HashTableType>
void readWordAndCreateTable(HashTableType &hash_table, const string &words_filename){

  ifstream fin(words_filename);
  string word = "";
  while(fin >> word){
    hash_table.Insert(word);
  }
}

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();
  //..Insert your own code
  
  readWordAndCreateTable(hash_table, words_filename);
  int itemCount = hash_table.GetItemCount();
  int tableSize = hash_table.GetTableSize();
  int collisions = hash_table.GetCollisions(); 
  double loadFactor = itemCount/ double(tableSize);
  double avgCollisions = collisions/double(itemCount);
  cout << "Collisions: " << collisions <<endl;
  cout << "Number of items: " << itemCount <<endl;
  cout << "Size of hash table: " << tableSize <<endl;
  cout << "Load factor: " << loadFactor << endl;
  cout << "Avg. number of collisions: " << avgCollisions << endl;
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
