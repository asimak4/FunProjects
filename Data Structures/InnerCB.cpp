// File: InnerCB.cpp
// Name: Alex Simak
// UMBC CMSC 341 Fall 2018 Project 1
//
// CPP for Inner Circular Buffer.
// See project description for details.
//

#include "InnerCB.h"
#include <stdexcept>
#include <iostream>

using namespace std;

// Constructor, default size is 10.
InnerCB::InnerCB(int n){
  // initializes a new buffer of size 10 
  m_buffer = new int[n];
  m_size = 0;
  m_capacity = n;
  m_start = -1;
  m_end = -1;
  
}

// Copy constructor
InnerCB::InnerCB(const InnerCB& other){
  // initialize a new buffer with the elements
  // copied from the other InnerCB
  m_buffer = new int [other.m_capacity];

  m_capacity = other.m_capacity;
  m_size = other.m_size;
  m_start = other.m_start;
  m_end = other.m_end;
  // loops through the original array and copies the elements 
  for(int i = 0; i < other.m_capacity; i++){
    m_buffer[i] = other.m_buffer[i];
  }
}

// Destructor
InnerCB::~InnerCB(){
  // deletes the buffer and sets to NULL 
  delete [] m_buffer;
  m_buffer = NULL;
 
}


// Add item to circular buffer
void InnerCB::enqueue(int data){
  // If the back is Full 
  if (isFull()){
    throw overflow_error("FULL");
  }
  // Adding the data to the queue starting from zero 
    if(m_start == -1 && m_end == -1){
      m_start = 0;
    }
    // if the end is at the capacity
    if(m_end == m_capacity - 1){
      // end goes back to the beginning and adds the data 
      // incriments size of the CB
      m_end = 0;
      m_buffer[m_end] = data;
      m_size++;
    }
    // if the end stil has space to add data
    else{
      // adds data and updates size and the end 
      m_buffer[m_end+1] = data;
      m_end++;
      m_size++; 
    }
  
}

// Remove item from circular buffer
int InnerCB::dequeue(){
  if (isEmpty()) 
    throw underflow_error("EMPTY");
  // sets the variable to the element at the start
  int deleteVar = m_buffer[m_start];
  // if the element is at the capacity the start goes back to the beginning 
  if(m_start == m_capacity-1)
    m_start = -1;
  // update start and size
  m_start = m_start+1;
  m_size--;
  return deleteVar;
}



// True if no space left in buffer
bool InnerCB::isFull(){
  // if the total number of elements equals the capacity
  if (m_size == m_capacity)
    return 1;
  else
    return 0;
}

// True if buffer holds no items
bool InnerCB::isEmpty(){
  // if there are no elements left 
  if (m_size == 0)
    return 1;
  return 0;
}

// return maximum number of items this buffer can hold
int InnerCB::capacity(){
  return m_capacity;
}

// return number of items currently held in the buffer
int InnerCB::size(){
  return m_size;
}

// overloaded assignment operator
const InnerCB &InnerCB::operator=(const InnerCB& rhs){
  // checks for self assigment 
  if(this == &rhs)
    return *this;
  
  m_capacity = rhs.m_capacity;
  m_size = rhs.m_size;
  // deletes the previous information of the allocated buffer
  delete [] m_buffer;
  // allocates new buffer with the rhs capacity 
  m_buffer = new int[rhs.m_capacity];
  // loops through the size of the buffer and sets them equal to each other 
  for (int i =0; i < rhs.m_capacity;i++){
    m_buffer[i] = rhs.m_buffer[i];
  }
  
  m_start = rhs.m_start;
  m_end = rhs.m_end;
  
  return *this;
}

// debugging function. Prints out contents.
void InnerCB::dump(){
  cout << "InnerCB dump(): m_size = " << m_size << endl;
  // if the newest is before the oldest
  // loops from the oldest to the capacity
  // then loops from zero to the newest and dumps the InnerCB elements
  if(m_end < m_start){
    for (int i = m_start; i < m_capacity; i++){
      cout << "[" << i << "] " << m_buffer[i] << ", ";
    }
    for (int i = 0; i <= m_end; i++){
      cout << "[" << i << "] " << m_buffer[i] << ", ";
    }
  }
  else{
    for (int i = m_start; i <= m_end; i++){
      cout << "[" << i << "] " << m_buffer[i] << ", ";
    }
  }
  cout << endl;
}
