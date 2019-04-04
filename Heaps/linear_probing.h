#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

#include <iostream>
#include "quadratic_probing.h"

// Quadratic probing implementation.
template <typename HashedObj>
class HashTableLinear: public HashTableQuadratic<HashedObj> {
    public:
        enum EntryType {ACTIVE, EMPTY, DELETED};    // enum cannot be inherited
        explicit HashTableLinear(size_t size = 101): HashTableQuadratic(){
            std::cout << GetTableSize() << std::endl;
            MakeEmpty();
        }

     private:        
        
        struct HashEntry {
            HashedObj element_;
            EntryType info_;
            
            HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
            :element_{e}, info_{i} { }
            
            HashEntry(HashedObj && e, EntryType i = EMPTY)
            :element_{std::move(e)}, info_{ i } {}
        };
            

        std::vector<HashEntry> array_;
        size_t current_size_;

        bool IsActive(size_t current_pos) const
        { return array_[current_pos].info_ == ACTIVE; }

        size_t FindPos(const HashedObj &x, int &collisions) const {
            
            size_t offset = 1;
            size_t current_pos = InternalHash(x);
            
            while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
            current_pos += offset;  // Compute ith probe.
            offset += 2;
            collisions++;
            if (current_pos >= array_.size()){
                current_pos -= array_.size();
            }
            }
            return current_pos;
        }

        void Rehash(int &collisions) {
            std::vector<HashEntry> old_array = array_;

            // Create new double-sized, empty table.
            array_.resize(NextPrime(2 * old_array.size()));
            for (auto & entry : array_)
                entry.info_ = EMPTY;
            
            // Copy table over.
            current_size_ = 0;
            for (auto & entry :old_array)
                if (entry.info_ == ACTIVE)
                    Insert(std::move(entry.element_), collisions);
        }
        
        // std::hash has overloaded operator () that calculates the hash
        size_t InternalHash(const HashedObj & x) const {
            std::cout << "In derived InternalHash" << std::endl;
            static std::hash<HashedObj> hf;
            return hf(x) % array_.size();  // returns the position of the hashed value
        }
 
};

#endif  // LINEAR_PROBING_H