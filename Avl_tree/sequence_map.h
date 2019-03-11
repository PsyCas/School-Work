//Parakram Basnet
#include <iostream>
#include <vector>

using namespace std;

class SequenceMap{

    public:  
        SequenceMap() = default;

        SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
            recognition_sequence = a_rec_seq;
            enzyme_acronyms_.push_back(an_enz_acro);
        }

        bool operator < (const SequenceMap &rhs) const{
            return recognition_sequence < rhs.recognition_sequence;
        }

         // displays the sequence map
        friend ostream& operator<<(ostream &out, const SequenceMap &rhs){
            out << rhs.recognition_sequence << "/";
            for (int i = 0; i < rhs.enzyme_acronyms_.size(); ++i){
                out << rhs.enzyme_acronyms_[i] << "/";
            } 

            return out;
        } 
        
        
        void merge(const SequenceMap &other_sequence){
            
            for(string enz_acro : other_sequence.enzyme_acronyms_)
                enzyme_acronyms_.push_back(enzo_acro);
        }

    private:

        string recognition_sequence;
        vector<string> enzyme_acronyms_;
};