#include <vector>
#include <iostream>

using namespace std;

class SequenceMap{

    public:
        
        SequenceMap();

        SequenceMap(const string &a_rec_seq, const string &an_enz_acro);
        bool operator < (const SequenceMap &rhs) const;
        // overload << operator
        void merge(const SequenceMap &other_sequence)

    private:

        string recognition_sequence;
        vector<string> enzyme_acronyms_;
};