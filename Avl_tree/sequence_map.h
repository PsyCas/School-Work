//Parakram Basnet

#include <vector>
#include <iostream>

class SequenceMap{

    public:  
        SequenceMap();

        SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro);
        bool operator < (const SequenceMap &rhs) const;
        friend std::ostream& operator<<(std::ostream &out, const SequenceMap &rhs); // displays the sequence map 
        void merge(const SequenceMap &other_sequence);

    private:

        std::string recognition_sequence;
        std::vector<std::string> enzyme_acronyms_;
};