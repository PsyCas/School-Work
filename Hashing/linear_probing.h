// Parakram Basnet
// linear_probing creates a hash table using linear probing as its probing method.

// Extra methods added:  
// size_t GetItemCount(); <- returns the item count
// int GetCollisions();  <- returns the number collissions
// int GetTableSize();   <- returns the table size
// int GetProbes();     <- returns the number of probes
// bool Find(const HashedObj &x);  <- Looks for the object x in the hash table and returns True if found, else false

// Extra data members:
// int collisionCounter_; <- counter for the total number of collisions
// int probeCounter_ = 1; <- counter for the number of probes


#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

#include <iostream>

// Quadratic probing implementation.
template <typename HashedObj>
class HashTableLinear {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableLinear(size_t size = 101) : array_(NextPrime(size)), collisionCounter_(0)
    {MakeEmpty();}
  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj &x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2){
      Rehash();    
    }
    return true;
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2){
      Rehash();
    }

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  bool Find(const HashedObj &x){
    probeCounter_ = 1;
    size_t offset = 1;
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x){
      current_pos += offset;  // Compute ith probe.
      probeCounter_++;
      if (current_pos >= array_.size()){
        current_pos -= array_.size();
      }
    } 
    if(array_[current_pos].info_ == EMPTY) return false;
    else if (array_[current_pos].element_ == x) return true;
    return false;
  }

  size_t GetItemCount(){
    return current_size_;
  }

  int GetTableSize(){
    return array_.size();
  }
  
  int GetCollisions(){
    return collisionCounter_; 
  }

  int GetProbes(){
    return probeCounter_;
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
  mutable int collisionCounter_;
  mutable int probeCounter_ = 1;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) {
    size_t offset = 1;
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
      current_pos += offset;  // Compute ith probe.
      collisionCounter_++;
      if (current_pos >= array_.size()){
	      current_pos -= array_.size();
      }
    }
    return current_pos;
  }

  void Rehash() {
    // std::cout << "Rehashing... " << std::endl;
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE){
        Insert(std::move(entry.element_));
      }
  }
  
  // std::hash has overloaded operator () that calculates the hash
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );  // returns the position of the hashed value
  }
};

#endif  // LINEAR_PROBING_H