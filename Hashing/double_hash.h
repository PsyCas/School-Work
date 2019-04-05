// Parakram Basnet
// double_hash creates a hash table using double hash as its probing method

// Extra methods added:  
// size_t GetItemCount(); <- returns the item count
// int GetCollisions();  <- returns the number collissions
// int GetTableSize();   <- returns the table size
// int GetProbes();     <- returns the number of probes
// bool Find(const HashedObj &x);  <- Looks for the object x in the hash table and returns True if found, else false

// Extra data members:
// int collisionCounter_; <- counter for the total number of collisions
// int valueR_ = 0;       <- counter for the R value
// int probeCounter_ = 1; <- counter for the number of probes

#ifndef DOUBLE_HASH_H
#define DOUBLE_HASH_H

#include <vector>
#include <algorithm>
#include <functional>

#include <iostream>

// Quadratic probing implementation.
template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size)), collisionCounter_(0)
    {
        MakeEmpty();
        GetPrimeLessThanTableSize();
    }
  
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
    std::hash<HashedObj> hf;
    size_t hashedObj = hf(x);  
    size_t offset = valueR_ - (hashedObj % valueR_);
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
      current_pos += offset;  // Compute ith probe.
      collisionCounter_++;
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
  int collisionCounter_;
  int valueR_ = 0;
  int probeCounter_ = 1;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) {
    probeCounter_ = 0;
    std::hash<HashedObj> hf;
    size_t hashedObj = hf(x);  
    // std::cout << "Value of R is: " << valueR_ << " for table: " << array_.size() << std::endl; 
    size_t offset = valueR_ - (hashedObj % valueR_);
    size_t current_pos = InternalHash(x);

    // std::cout << "Value of offset is: " << offset << " for current pos: " << current_pos << std::endl; 
      
    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
      current_pos += offset;  // Compute ith probe.
      collisionCounter_++;
      probeCounter_++;
      if (current_pos >= array_.size()){
	      current_pos -= array_.size();
      }
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    GetPrimeLessThanTableSize(); // get new value of R

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

    // Value of R
  void GetPrimeLessThanTableSize(){
      
      size_t tableSizeTemp = array_.size() -1;
      if (tableSizeTemp % 2 == 0) --tableSizeTemp;
      while(tableSizeTemp > 0){
        if(IsPrime(tableSizeTemp)){
            valueR_ = tableSizeTemp;
            return;
        }
        else tableSizeTemp = tableSizeTemp-2;
      }
  }
};




#endif