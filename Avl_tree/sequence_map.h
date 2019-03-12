//Parakram Basnet
#include <iostream>
#include <vector>

using namespace std;

class SequenceMap{

    public:  
        SequenceMap() = default;

        SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
            recognition_sequence_ = a_rec_seq;
            enzyme_acronyms_.push_back(an_enz_acro);
        }

        bool operator < (const SequenceMap &rhs) const{
            return recognition_sequence_ < rhs.recognition_sequence_;
        }

         // displays the sequence map
        friend ostream& operator<<(ostream &out, const SequenceMap &rhs){
            out << rhs.recognition_sequence_ << "/";
            for (size_t i = 0; i < rhs.enzyme_acronyms_.size(); ++i){
                out << rhs.enzyme_acronyms_[i] << "/";
            } 

            return out;
        } 
        
        // precondition: recognition_sequence_ ==  other_sequence_.recognition_sequence_
        void Merge(const SequenceMap &other_sequence_){

            // flag that checks if there are duplicates or not
            bool canMerge = true;

            //looping through every element in other_sequence
            for(string enzo_acro : other_sequence_.enzyme_acronyms_){
                
                // looping through every iteration in enzyme_acronyms_
                for(string individual_enzyme : enzyme_acronyms_){
                    
                    // avoiding duplicates by setting flag to false
                    if(individual_enzyme == enzo_acro){
                        canMerge = false;
                    }
                }

                // only merges if the flag is set to true
                if(canMerge) enzyme_acronyms_.push_back(enzo_acro);
            }
        }

        // function thats prints all the enzyme acronyms
        void PrintEnzymeAcronyms(){

            for(string word: enzyme_acronyms_){
                cout << word << " ";
            } 
        }

    private:

        string recognition_sequence_;
        vector<string> enzyme_acronyms_;
};