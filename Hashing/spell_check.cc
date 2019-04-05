// Parakram Basnet
// spell_check.cc reads in text documents and a dictionary and provides suggestions for potential spelling errors.

#include "quadratic_probing.h"  // for prime methods
#include "double_hash.h"        // for double hashing

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// AddCharacter is a helper function of CheckErrors(...)
// Adds every letter in the alphabet to all possible positions in the word, searches them in the dictionary and saves potential corrections
// in the vector correctedWords. 
void AddCharacter(const string &word, vector<string> &correctedWords, HashTableDouble<string> &dictionaryTable){

  vector<string> alphabets = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};

  for(string letter: alphabets){
    for (size_t i = 0; i < word.length()+1; ++i){
      string newWord = "";

      // creating the new word
      if(i == 0) newWord = letter + word;  // edge case for the first letter
      else if (i == word.length()) newWord = word + letter; // edge case for the last letter
      else newWord = word.substr(0,i) + letter + word.substr(i);    
      
      // checking if the word exists in the hash table
      if(dictionaryTable.Find(newWord)) correctedWords.push_back(newWord);
    } 
  }
}

// RemoveCharacter is a helper function of CheckErrors(...)
// Removed every letter one by one in the word, searches them in the dictionary and saves potential corrections
// in the vector correctedWords. 
void RemoveCharacter(const string &word, vector<string> &correctedWords, HashTableDouble<string> &dictionaryTable){

  for(size_t i = 0; i < word.length(); ++i){
    string newWord = word.substr(0,i) + word.substr(i+1);
    if(dictionaryTable.Find(newWord)) correctedWords.push_back(newWord);
  }
}

// SwapAdjacent is a helper function of CheckErrors(...)
// Swaps every adjacent letter in the word, searches them in the dictionary and saves potential corrections
// in the vector correctedWords. 
void SwapAdjacent(const string &word, vector<string> &correctedWords, HashTableDouble<string> &dictionaryTable){
  for(size_t i = 0; word.length() != 0 && i < word.length()-1; ++i){  // short-circuit check for when i == 0
    string newWord = word;
    std::swap(newWord[i], newWord[i+1]);
    if(dictionaryTable.Find(newWord)) correctedWords.push_back(newWord);
  }
}

// CheckErrors is a helper function of SpellChecker
// Checks all possible spelling corrections using three helper functions
// Displays either "No suggestions found" or the potential corrections stores in vector correctedWords 
void CheckErrors(const string &word, HashTableDouble<string> &dictionaryTable){
  vector<string> correctedWords;
  
  AddCharacter(word, correctedWords,dictionaryTable);
  RemoveCharacter(word, correctedWords,dictionaryTable);
  SwapAdjacent(word, correctedWords,dictionaryTable);

  cout << word << " => ";
  if(correctedWords.size() == 0){
    cout << "No suggestions found.";
  }
  else{
    for(string word: correctedWords){
      cout << word << " ";
    }
  }
  cout << endl;
}

// GetFormattedLetter converts all the letters to lowercase and removes punctuations
string GetFromattedLetter(const string& word){
  string finalStr = "";
  for(char letter: word){
    if(isalpha(letter)) finalStr += tolower(letter);
  }
  return finalStr;
}

// SpellChecker read in the dictionary and creates a hash table with all the words from the dictionary
// It reads in the document being checked word by word, tries to find it in the dictionary hash table. If its found, the word is correct
// If not, the word is sent to helper function CheckErrors(...)
void SpellChecker(const string &document_filename, const string &dictionary_filename){

  // creates hash table and inserts all the words from the dictionary
  HashTableDouble<string> dictionaryTable;
  ifstream fin(dictionary_filename);
  string word = "";
  while(fin >> word){
    dictionaryTable.Insert(word);
  }
  fin.close();

  // reads the document line by line and checks for spelling errors
  fin.open(document_filename);
  cout << endl <<"The Corrections are: (duplicate words are skipped)" << endl << endl;
  vector<string> wordList;

  while(fin >> word){
    word = GetFromattedLetter(word);

    // only displays unique words to avoid clutter
    bool isUnique = true;
    if(!dictionaryTable.Find(word)){

      // eliminates duplicate words from the list
      for(string listWord: wordList){
        if (listWord == word){
          isUnique = false;
          break;
        }
      } 

      if(isUnique){ 
        wordList.push_back(word);
        CheckErrors(word, dictionaryTable);
      }
    }
  } 

  fin.close();
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

  
  // Call functions implementing the assignment requirements.
  SpellChecker(document_filename, dictionary_filename);

  return 0;
}
