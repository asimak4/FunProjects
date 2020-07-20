// File: CBofCB.cpp
// Name: Alex Simak
// Student ID: OW81171
// UMBC CMSC 341 Fall 2018 Project 1
//
// CPP for Circular Buffer of Circular Buffer.
// 

#include "CBofCB.h"
#include <list>
#include <iostream>

using namespace std;

// default constructor
CBofCB::CBofCB(){
  // setting all the starting values
  // the outerCB starts with one InnerCB 
  m_obSize = 1;
  m_oldest = 0;
  m_newest = 0;
  
  for(int i = 1; i < m_obCapacity;i++){
    m_buffers[i]=NULL;
  }
  // Initialize the first InnerCB 
  m_buffers[0]= new InnerCB();
}

// copy constructor
CBofCB::CBofCB(const CBofCB& other){
  // Setting all the elements
  m_obSize = other.m_obSize;
  m_oldest = other.m_oldest;
  m_newest = other.m_newest;
    
  // loops through the CBofCB and makes a copy of
  // including all of the InnerCB's
  for (int i = 0; i < other.m_obCapacity;i++){
    if(other.m_buffers[i] != NULL)
      m_buffers[i] = new InnerCB(*other.m_buffers[i]);    
  }
  
}
// destructor
CBofCB::~CBofCB(){
  // loops through the whole CB without missing elements
  // if the newest is less than the oldest it needs to
  // go from oldest to the capacity and then from
  // zero to the newest element 
  if(m_newest < m_oldest){
    for (int i = m_oldest; i < m_obCapacity; i++)
      delete m_buffers[i];
    
    for (int i = 0; i <= m_newest; i++)
      delete m_buffers[i];
  }
  else{
    for (int i = m_oldest;i <= m_newest; i++){
      if(m_buffers[i] != NULL)
	delete m_buffers[i];
      
    }
  }
}

// add item to this data structure
void CBofCB::enqueue(int data){
  // needs to check if the CBofCB is full  
  if(isFull())
    throw overflow_error ("Full");

  // if the InnerCB is full
  if(m_buffers[m_newest]->isFull())
    {
      // if the m_newest is not at the end of CBofCB
      // adds a new InnerCB double the capacity
      if(m_newest != m_obCapacity -1){
	m_buffers[m_newest+1] = new InnerCB (m_buffers[m_newest]->capacity()*2);
      }
      // if the m_newest is at the end of CBofCB
      else{
	// m_newest goes back to the beginning 
	m_newest = -1;
	m_buffers[m_newest+1] = new InnerCB (m_buffers[m_obCapacity-1]->capacity()*2);
      }
      // add the data to the newest InnerCB and increase the size of the CBofCB size 
      m_newest++;
      m_buffers[m_newest]->enqueue(data);
      m_obSize++;
      
    }
  // if theres space in the InnerCB the data is added
  else
    m_buffers[m_newest]->enqueue(data);
}

// remove item from this data structure

int CBofCB::dequeue(){
  // checks to see if the CBofCB is empty 
  if(isEmpty())
    throw underflow_error ("EMPTY");
  // get the element that should be deleted from InnerCB
  int deletedVar = 0;
  deletedVar = m_buffers[m_oldest]->dequeue();
  // checks to see if the InnerCB is empty
  if(m_buffers[m_oldest]->isEmpty())
    {
      // deletes the empty InnerCB and sets to NULL 
      delete m_buffers[m_oldest];
      m_buffers[m_oldest] = NULL;
      // checks if the InnerCB being deleted, if it was at the end of CBofCB
      if(m_oldest == m_obCapacity -1)
	m_oldest = 0;
      else
	m_oldest++;
      
      m_obSize--;
    }
  return deletedVar;
}

// returns true if cannot add more items
bool CBofCB::isFull(){
  // loops through the array and checks each InnerCB to see if they are full 
  for (int i = 0; i < m_obCapacity; i++){
    if(m_buffers[i] != NULL){
      if(!m_buffers[i]->isFull()){
	return 0;
      }
    }
    else
      return 0;
  }
  
  return 1;
}

// returns true if no items stored in data structure
bool CBofCB::isEmpty(){
  // if the size is equal to zero its empty
  if(m_obSize == 0){
    return 1;
  }
  return 0;
}

// number of items in the data structure as a whole.
// Note: not the number of InnerCB's
int CBofCB::size(){
  int wholeSize = 0;
  // uses a variable and adds to it
  // checks the size of all the InnerCB's in the CBofCB 
  for (int i = 0; i < m_obCapacity; i++){
    if(m_buffers[i]!= NULL){
      wholeSize += m_buffers[i]->size();
    }
  }
  return wholeSize;  
}

// overloaded assignment operator
const CBofCB& CBofCB::operator=(const CBofCB& rhs){
  // checks for self assigment 
  if(this == &rhs){
    return *this;
  }
  // sets all the variables equal to each other 
  m_obSize = rhs.m_obSize;
  m_oldest = rhs.m_oldest;
  m_newest = rhs.m_newest;

  
  for (int i = 0; i < m_obCapacity;i++){
  // need to delete the previous information and sets to NULL  
    if(m_buffers[i] != NULL){
      delete m_buffers[i];
      m_buffers[i] = NULL;
    }
    // allocates a new InnerCB for each rhs InnerCB(makes copies)
    if(rhs.m_buffers[i] != NULL){
      m_buffers[i] = new InnerCB(*rhs.m_buffers[i]);
    }

  }
  
  
  return *this;
}

// debugging function, prints out contents of data structure
void CBofCB::dump(){
  for (int i = 0; i < 43; i++){
    cout << "-";
  }
  cout << endl;
  cout << "Outer Circular buffer dump(): m_obSize = " << m_obSize << ": "<< endl;
  // if the newest is before the oldest
  // loops from the oldest to the capacity
  // then loops from zero to the newest and dumps the InnerCB elements 
  if(m_newest < m_oldest){
    for (int i = m_oldest; i < m_obCapacity; i++){
      cout << "[ " << i << "] ";
      m_buffers[i]->dump();
    }
    for (int i = 0; i <= m_newest; i++){
      cout << "[" << i << "] ";
      m_buffers[i]->dump();
    }
  }
  else{
    for (int i = m_oldest;i <= m_newest; i++){
      cout << "[" << i << "] ";
      m_buffers[i]->dump();
    }
  }
  
  for (int i = 0; i < 43; i++){
    cout << "-";
  }

  cout << endl;
  
}


