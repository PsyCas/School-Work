//Parakram Basnet

#include "sequence_map.h"

SequenceMap:: SequenceMap() = default;

SequenceMap:: SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro){

    recognition_sequence = a_rec_seq;
    enzyme_acronyms_.push_back(an_enz_acro);
}

bool SequenceMap:: operator<(const SequenceMap &rhs) const{
    return recognition_sequence < rhs.recognition_sequence;
}

std::ostream &operator<<(std::ostream &out, const SequenceMap &rhs){

    out << rhs.recognition_sequence << "/";
    for (int i = 0; i < rhs.enzyme_acronyms_.size(); ++i){
        out << rhs.enzyme_acronyms_[i] << "/";
    } 

    return out;
}

void SequenceMap:: merge(const SequenceMap &other_sequence){

    std::cout << this;
}