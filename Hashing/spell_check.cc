// Parakram Basnet
#include "quadratic_probing.h"  // for prime methods
#include "double_hash.h"        // for double hashing 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void AddCharacter(const string &word, vector<string> &correctedWord, HashTableDouble<string> &dictionaryTable){

  vector<string> alphabets = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};

  for(string letter: alphabets){
    for (size_t i = 0; i < word.length()+1; ++i){
      string newWord = "";      
      // creating the word
      if(i == 0) newWord = letter + word;  
      else if (i == word.length()) newWord = word + letter;
      else newWord = word.substr(0,i) + letter + word.substr(i);  
      
      // checking if the word exists in the hash table
      if(dictionaryTable.Find(newWord)) correctedWord.push_back(newWord);
    } 
  }
}

void RemoveCharacter(const string &word, vector<string> &correctedWord, HashTableDouble<string> &dictionaryTable){

  for(size_t i = 0; i < word.length(); ++i){
    string newWord = word.substr(0,i) + word.substr(i+1);
    if(dictionaryTable.Find(newWord)) correctedWord.push_back(newWord);
  }
}

void SwapAdjacent(const string &word, vector<string> &correctedWord, HashTableDouble<string> &dictionaryTable){

  for(size_t i = 0; i < word.length()-1; ++i){
    string newWord = word;
    std::swap(newWord[i], newWord[i+1]);
    cout << newWord << endl;
  }
}

void CheckErrors(const string &word, HashTableDouble<string> &dictionaryTable){
  vector<string> correctedWords;
  AddCharacter(word, correctedWords,dictionaryTable);
  RemoveCharacter(word, correctedWords,dictionaryTable);
  SwapAdjacent(word, correctedWords,dictionaryTable);
  
  for(string word: correctedWords){
    cout << word << ", ";
  }
  cout << endl;
}

// converts all the letters to lowercase and removes punctuations
string GetFromattedLetter(const string& word){
  string finalStr = "";
  for(char letter: word){
    if(isalpha(letter)) finalStr += tolower(letter);
  }
  return finalStr;
}

void SpellChecker(const string &document_filename, const string &dictionary_filename){

  HashTableDouble<string> dictionaryTable;
  ifstream fin(dictionary_filename);
  string word = "";
  while(fin >> word){
    dictionaryTable.Insert(word);
  }
  fin.close();

  fin.open(document_filename);
  cout << "The Corrections are: " << endl << endl;

  while(fin >> word){
    word = GetFromattedLetter(word);
    
    if(!dictionaryTable.Find(word)){ 
      cout << word << " => ";
      CheckErrors(word, dictionaryTable);
    }
  } 
}



// Sample main for program spell_check
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }
  
  const string document_filename(argv[1]);
  const string dictionary_filename(argv[2]);
  
  cout << "Input document filename is " << document_filename << endl;
  cout << "Input dictionary filename is " << dictionary_filename << endl;

  SpellChecker(document_filename, dictionary_filename);

  // Call functions implementing the assignment requirements.

  return 0;
}
