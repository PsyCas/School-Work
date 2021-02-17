// Name: Parakram Basnet 
// File Name: points2.h
// Edited: 02/05/2019
// Points2 creates a 2 dimensional sequence of objects of the same type and makes use of the big-5 to copy and  move data between instances. 

#ifndef CSCI335_HOMEWORK1_POINTS2_H_
#define CSCI335_HOMEWORK1_POINTS2_H_

// imorting necessary libraries
#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

// Points2 creates a sequence of 2D objects and formats them using overloaded operators.
template<typename Object>
class Points2 {
 
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation.

  // Zero-parameter constructor. 
  // Set size to 0 and sequence to be a nullptr 
  Points2(): sequence_{nullptr}, size_{0}{}

  // Copy-constructor.
  // Take in another instance of Points2 and copies it to the new instance
  Points2(const Points2 &rhs): sequence_{nullptr}, size_{0}{

    size_ = rhs.size_;

    sequence_ = new std::array<Object, 2>[size_]; 
    for(size_t i = 0; i < size_; i++){
      sequence_[i] = rhs.sequence_[i];
    } 
  }

  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  // {
  // Points2 copy = rhs; 
  // std::swap(*this, copy);
  // return *this;
  // }
  // Overloaded operator that copies the elements of the parameter to the object instance that called it.
  Points2& operator=(const Points2 &rhs){

    Points2 copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  // Move-constructor. 
  // Moves the elements of the parameter to the new instance
  Points2(Points2 &&rhs){

    size_ = rhs.size_;
    sequence_ = rhs.sequence_;

    // resetting the values of the parameter
    rhs.size_ = 0;
    rhs.sequence_ = nullptr;
  }

  // Move-assignment
  // Just use std::swap() for all variables.
  Points2& operator=(Points2 &&rhs){

    std::swap(size_, rhs.size_);
    std::swap(sequence_, rhs.sequence_);

    return *this;
  }

  // Destructor that deallocates the memory for sequence and sets it to nullptr
  ~Points2(){

    delete[] sequence_;
    sequence_ = nullptr;
  }

  // End of big-five.

  // One parameter constructor.
  //initializes a sequence with size 1 and adds the parameter passed into the sequence
  Points2(const std::array<Object, 2>& item) {
    
    sequence_ = new std::array<Object, 2>[1];
    sequence_[0] = item;

    size_ = 1; 
  }

  // Read a chain from standard input.
  void ReadPoints2() {
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line); 
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;
    size_ = size_of_sequence;
    // Allocate space for sequence.
    sequence_ = new std::array<Object, 2>[size_of_sequence];
    
    Object token;
    for (int i = 0; input_stream >> token; ++i) {

      sequence_[i][0] = token;
      input_stream >> token;    // collecting the y value of the 2D object 
      sequence_[i][1] = token;
    }
  }

  // function that returns the size of the sequence
  size_t size() const {
    return size_;
  }

  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const { 

    if (location < size_) return sequence_[location];
    abort();  // aborts if the location called is out of range
  }

 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
  friend Points2 operator+(const Points2 &c1, const Points2 &c2) {
   
    Points2<Object> finalPoint;
    size_t smaller = 0;

    // copying the larger of the two sequences into the final sequence
    // smaller stores the value of the sequence with less elements
    if (c1.size_ > c2.size_){
      
      finalPoint = c1; // using the overloaded = operator
      smaller = c2.size_;
    }  
    else{
      finalPoint = c2;
      smaller = c1.size_;
    }

    for (size_t i = 0; i < smaller; i++){

      finalPoint.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0]; 
      finalPoint.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1]; 
    }

    return finalPoint;
 }

 // Overloading the << operator.
 // prints out the sequence as a sequence in the form of (x, y) instead of integers 
 friend std::ostream &operator<<(std::ostream &out, const Points2 &some_points2) {

   for (size_t i = 0; i < some_points2.size_; i++){

     out << "(" << some_points2.sequence_[i][0] << ", " << some_points2.sequence_[i][1] << ") ";
   }
   out << std::endl;
   return out; 
 }
 
 private:
  // Sequence of points. 
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;

};  // end class

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2_H_