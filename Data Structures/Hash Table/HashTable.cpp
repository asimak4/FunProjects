//
// File: HashTable.cpp
// Author: Alex Simak
// Date Due: December 11, 2018
// Class: CMSC 341
// Project 5
//

#include "HashTable.h"
#include "iostream"

#include <cstring>
#include <stdexcept>

using namespace std;

const int MAXSIZE = 199999;
const int MINSIZE = 101;



// hashCode function given to us
unsigned int HashTable::hashCode(const char *str) {
  unsigned int val = 0 ;
  const unsigned int thirtyThree = 33 ;  // magic number from textbook
  
  int i = 0 ;
  while (str[i] != '\0') {
    val = val * thirtyThree + str[i];
    i++;
  }
  return val ;
}

char * const HashTable::DELETED  = (char *) &DELETED;

HashTable::HashTable(int n) {
  hashTableCapacity = n;
  isRehashTrue = false;
  giveUp = false;
  hashSize = 0;
  checkForInsertIntoSecond = false;
  loadFactor = hashSize/hashTableCapacity;
  
  if(n > MAXSIZE){
    throw out_of_range("Size too big");
  }
  else if(n < MINSIZE){
    hashTableCapacity = 101;
  }
  hashTableCapacity = roundUpPrime(hashTableCapacity);
  
  oldHash = new char*[hashTableCapacity];
  for(int i = 0; i < hashTableCapacity; i++){
    oldHash[i] = nullptr;
  }
  
  newCapacity = roundUpPrime(hashTableCapacity+1);
  newHash = new char*[newCapacity];
  
  newSize = 0;
  newLoadFactor = newSize/newCapacity;
  for(int j = 0; j < (newCapacity); j++){
    newHash[j] = nullptr;
  }
  
}

HashTable::HashTable(HashTable &other) {
  // copying elements over
  hashTableCapacity = other.hashTableCapacity;
  hashSize = other.hashSize;
  loadFactor = other.loadFactor;

  newCapacity = other.newCapacity;
  newSize = other.newSize;

  isRehashTrue = other.isRehashTrue;
  giveUp = other.giveUp;
  checkForInsertIntoSecond = other.checkForInsertIntoSecond;
  // constructing new arrays
  oldHash = new char*[hashTableCapacity];
  newHash = new char*[newCapacity];

  // setting all the elements to NULL after initializing two new HashTables
    for (int j = 0; j < hashTableCapacity; j++) {
        oldHash[j] = nullptr;
    }
    for (int k = 0; k < newCapacity; k++) {
        newHash[k] = nullptr;
    }
    // if rehashing is not true, just move all the elements over
  if(!(other.isRehashTrue)){
      for(int i = 0; i < other.hashTableCapacity;i++){
          oldHash[i] = strdup(other.oldHash[i]);
      }
      for(int i = 0; i < other.newCapacity;i++){
          newHash[i] = strdup(other.newHash[i]);
      }
  }
  else{
      // force rehashing then simply copy over the elements from both hashTables
      other.moveAllToThird();
      for(int i = 0; i < other.hashTableCapacity;i++){
          if(other.oldHash[i] != nullptr && other.oldHash[i] != DELETED)
              oldHash[i] = strdup(other.oldHash[i]);
      }
      for(int i = 0; i < other.newCapacity;i++){
          if(other.newHash[i] != nullptr && other.newHash[i] != DELETED)
              newHash[i] = strdup(other.newHash[i]);
	  
      }
  }  
}


const HashTable &HashTable::operator=(HashTable &rhs) {
    if(this == &rhs){
        return *this;
    }

    hashTableCapacity = rhs.hashTableCapacity;
    hashSize = rhs.hashSize;
    loadFactor = rhs.loadFactor;

    newCapacity = rhs.newCapacity;
    newSize = rhs.newSize;

    isRehashTrue = rhs.isRehashTrue;
    giveUp = rhs.giveUp;
    checkForInsertIntoSecond = rhs.checkForInsertIntoSecond;

    delete [] oldHash;
    delete [] newHash;
    
    oldHash = new char*[rhs.hashTableCapacity];
    newHash = new char*[rhs.newCapacity];

    for(int i = 0; i < hashTableCapacity; i++){
      oldHash[i] = nullptr;
    }

    for(int i = 0; i < newCapacity; i++){
      newHash[i] = nullptr;
    }

    
    if(!(rhs.isRehashTrue)){
      for(int i = 0; i < rhs.hashTableCapacity;i++){
	if(rhs.oldHash[i] != nullptr && rhs.oldHash[i] != DELETED)
	  oldHash[i] = strdup(rhs.oldHash[i]);
      }
      for(int i = 0; i < rhs.newCapacity;i++){
	if(rhs.newHash[i] != nullptr && rhs.newHash[i] != DELETED)
	  newHash[i] = strdup(rhs.newHash[i]);
        }
    }
    else{
      rhs.moveAllToThird();
      for(int i = 0; i < rhs.hashTableCapacity;i++){
	  if(rhs.oldHash[i] != nullptr && rhs.oldHash[i] != DELETED)
            oldHash[i] = strdup(rhs.oldHash[i]);
        }
      for(int i = 0; i < rhs.newCapacity;i++){
	if(rhs.newHash[i] != nullptr && rhs.newHash[i] != DELETED)
	  newHash[i] = strdup(rhs.newHash[i]);
      }
      
    }
    return *this;
}


HashTable::~HashTable(){

  for(int i = 0; i < hashTableCapacity; i++){
    if(oldHash[i] != DELETED)
      free(oldHash[i]);
    oldHash[i] = nullptr;
  }
  
  for(int j = 0; j < (newCapacity); j++){
    if(newHash[j] != DELETED)
      free(newHash[j]);
    newHash[j] = nullptr;
    
  }
  delete [] newHash;
  delete [] oldHash;

}

void HashTable::insert(const char *str) {
  // checking load factor for incremental hashing
  
  if(hashSize != 0){
    loadFactor = (float(hashSize) / hashTableCapacity);
  }
  
  if (loadFactor > .5){
    isRehashTrue = true;
  }
  if (isRehashTrue && loadFactor <= .03){
    moveRemainingItems();
  }
  
  bool isCluster = false;
  bool isDup = false;
  
  // setting the string to its specific hashCode
  unsigned int hashedString = hashCode(str);
  int hashedValue = hashedString % hashTableCapacity;
  if(!isRehashTrue) {
    if(findInTables(str)){
      isDup = true;
    }
    
    // example of linear probing, if the hashIndex is taken,
    // needs to keep going until finds an empty spot and copy value in there
    else if ((oldHash[hashedValue] != nullptr && !isDup)) {
      int clusterCounter = 0;
      // while not null and its not DELETED, aka its a filled Hash spot 
      while (oldHash[hashedValue] != nullptr && oldHash[hashedValue] !=  DELETED){
	// checking if the string is a duplicate value in case 
	if (strcmp(oldHash[hashedValue], str) == 0) {
	  isDup = true;
	}
	// adding to cluster counter, making sure there is not 10 values in a row
	clusterCounter++;
	hashedValue++;
	// resetting the hash value in case it loops around to the front 
	if (hashedValue == hashTableCapacity) {
	  hashedValue = 0;
	}
	// activates rehashing 
	if(clusterCounter >= 9){
	  isCluster = true;
	  isRehashTrue = true;
	}
      }
      // if the value is "DELETED"
      if (!isDup) {
	oldHash[hashedValue] = strdup(str);
	hashSize++;
      }
      
    }
    // if it lands on a simple empty slot
    if (oldHash[hashedValue] == nullptr && !isDup) {
      oldHash[hashedValue] = strdup(str);
      hashSize++;
    }
  }
  
  // rehashing sequences
  if(isRehashTrue && isCluster){
    // loops through the cluster until reaches NULL
    // rehashing is true, so it takes values from old to new 
    while(oldHash[hashedValue] != nullptr && oldHash[hashedValue] != DELETED){
      insertIntoSecondTable(oldHash[hashedValue]);
      hashSize--;
      free(oldHash[hashedValue]);
      oldHash[hashedValue] = nullptr;
      hashedValue--;
      if(hashedValue == 0){
	hashedValue = hashTableCapacity;
      }
    }
  }
  // if the loadFactor is greater than .5
  else if(isRehashTrue){

      insertIntoSecondTable(str);

      if(oldHash[hashedValue] != nullptr && !checkForInsertIntoSecond){
          moveCluster(hashedValue);
      }


  }

  // when the loadFactor is less than .03
  // making sure not the first values inserted into the array
  if(isRehashTrue && hashSize == 0 && newSize > 0){
    moveRemainingItems();
  }

  
}

void HashTable::insertIntoSecondTable(const char *str) {
  // get a hashCode for each str passed in
  if(str != nullptr && str != DELETED) {
      unsigned int hashedString = hashCode(str);
      int hashedValue = hashedString % newCapacity;


      if ((newHash[hashedValue] != nullptr && newHash[hashedValue] != DELETED)){
          int slotCounter = 0;
          // looking for the next open spot to insert, aka a null or DELETED value
          while (newHash[hashedValue] != nullptr && newHash[hashedValue] != DELETED) {
           /*   if (strcmp(newHash[hashedValue], str) == 0) {
                  isDup = true;
              }*/
              slotCounter++;
              hashedValue++;
              if (hashedValue == newCapacity) {
                  hashedValue = 0;
              }
              // if the new Hash Table has a cluster of 10 we give up rehashing and make
              // one large third array
              if (slotCounter >= 9) {
                  giveUp = true;
              }
          }
      }
      // if we are hashed to an empty spot
      if (newHash[hashedValue] == nullptr || newHash[hashedValue] == DELETED){
          newHash[hashedValue] = strdup(str);
          newSize++;
      }
      // if giveUp is true, we move all the values to the third HashTable
      if (giveUp) {
          checkForInsertIntoSecond = true;
          moveAllToThird();
      }
  }
}

bool HashTable::find(const char *str) {
    
    bool found = false;
    
    // checking load factor for incremental hashing
    if(hashSize != 0){
        loadFactor = (float(hashSize) / hashTableCapacity);
    }

    if (loadFactor > .5){
        isRehashTrue = true;
    }
    if (isRehashTrue && loadFactor <= .03){
        moveRemainingItems();
    }

    // getting a bool value for str passed into findInTables
    // this function is made only to loop through and check if the
    // str exists
    found = findInTables(str);

    // getting a hashCode value for str
    unsigned int hashedValue2 = hashCode(str);
    int hashIndex2 = hashedValue2 % hashTableCapacity;

    // if currently rehash, and not null, move the cluster to the new Hash Table
    if(isRehashTrue && oldHash[hashIndex2] != nullptr && oldHash[hashIndex2] != DELETED && !checkForInsertIntoSecond) {
       moveCluster(hashIndex2);
       checkForInsertIntoSecond = false;

    }
    // we need to look through the hashtable until the next non-null value to move to the new Hash Table
    else if(isRehashTrue && !found && oldHash[hashIndex2] == nullptr){
        unsigned int hashedValue = hashCode(str);
        int hashIndex = hashedValue % hashTableCapacity;

        // until non null value keep looking through the table
        while(oldHash[hashIndex] == nullptr){
            hashIndex++;
            if(hashIndex == hashTableCapacity){
                hashIndex = 0;
            }
        }
        // when we reach the non-null value, move the cluster to the new Hash Table
        while(oldHash[hashIndex] != nullptr && oldHash[hashIndex] != DELETED){
            insertIntoSecondTable(oldHash[hashIndex]);
            hashSize--;
            free(oldHash[hashIndex]);
            oldHash[hashIndex] = nullptr;
            hashIndex++;
            if (hashIndex == hashTableCapacity) {
                hashIndex = 0;
            }
        }
    }
    // if the remaining .03 loadfactor is left, it will move the remaining items
    if(isRehashTrue && hashSize == 0 && newSize > 0){
        moveRemainingItems();
    }
    return found;
}

// purpose of this function is just to return if the str is found in either hash table
bool HashTable::findInTables(const char *str) {
    // checking load factor for incremental hashing
    bool found = false;

    unsigned int hashedValue = hashCode(str);
    int hashIndex = hashedValue % hashTableCapacity;
    // looking through the old Hash table for str
    while(oldHash[hashIndex] != nullptr){
        if (strcmp(oldHash[hashIndex], str) == 0) {
            found = true;
        }
        hashIndex++;
        if(hashIndex == hashTableCapacity){
            hashIndex = 0;
        }
    }
    // looking through the new Hash table for the str
    int newHashIndex = hashedValue % newCapacity;
    while(newHash[newHashIndex] != nullptr){
        if (strcmp(newHash[newHashIndex], str) == 0) {
            found = true;
        }
        newHashIndex++;
        if(newHashIndex == newCapacity){
            newHashIndex = 0;
        }
    }
    // if the str is found in either hash table, will return true
    // else will return false
    return found;
}


char *HashTable::remove(const char *str) {
  // checking load factor for incremental hashing
  if(hashSize != 0){
    loadFactor = (float(hashSize) / hashTableCapacity);
  }
  
    if (loadFactor > .5){
      isRehashTrue = true;
    }
    if (isRehashTrue && loadFactor <= .03){
      moveRemainingItems();
    }
    
    for(int i = 0; i < hashTableCapacity; i++) {
      if (oldHash[i] != nullptr) {
	if (strcmp(oldHash[i], str) == 0) {
	  char *tempString;
	  // set the temp variable to the word to delete to return
	  tempString = oldHash[i];
	  // set value to deleted and decrease size
	  oldHash[i] = DELETED;
	  hashSize--;
	  
	  if(isRehashTrue && hashSize == 0 && newSize > 0){
	    moveRemainingItems();
	  }
	  return tempString;
	}
	
      }
    }
    // look for the str only if the new Hash has a size greater than 0
    if(newSize > 0){
      for(int j = 0; j < newCapacity; j++) {
        if (newHash[j] != nullptr) {
	  if (strcmp(newHash[j], str) == 0) {
	    char *tempString;
	    tempString = newHash[j];
	    
	    newHash[j] = DELETED;
	    newSize--;
	    
	    if(isRehashTrue && hashSize == 0 && newSize > 0){
	      moveRemainingItems();
	    }
	    return tempString;
	  }
        }
      }
    }
    if(isRehashTrue && hashSize == 0 && newSize > 0){
      moveRemainingItems();
    }
    
    return NULL;
    
}



void HashTable::dump() {
  
  cout << "HashTable #1: size = " << hashSize <<", tableSize = " << hashTableCapacity << endl;
  int hashIndex = 0;
  for (int i = 0; i < hashTableCapacity; i++) {
    cout << "H1[  " << i << "] = ";
    if(oldHash[i] == nullptr) {
      printf(oldHash[i]);
      cout << " " << endl;
    }else if(oldHash[i] != nullptr && oldHash[i] == DELETED){
      cout << "DELETED" << endl;
    }
    else{
      printf(oldHash[i]);
      unsigned int hashNumber = hashCode(oldHash[i]);
      hashIndex = hashNumber % hashTableCapacity;
      cout << " ("<< hashIndex << ")"<< endl;
    }
  }
  
  if(newSize > 0){
    cout << endl << endl;
    cout << "HashTable #2: size = " << newSize <<", tableSize = " << newCapacity << endl;
    for (int i = 0; i < newCapacity; i++) {
      cout << "H2[  " << i << "] = ";
      
      if(newHash[i] == nullptr){
	printf(newHash[i]);
	cout << " " << endl;
      }
      else if(newHash[i] != nullptr && strcmp(newHash[i], DELETED) == 0){
	cout << "DELETED" << endl;
      }else{
	printf(newHash[i]);
	unsigned int hashNumber = hashCode(newHash[i]);
	hashIndex = hashNumber % newCapacity;
	cout << " ("<< hashIndex << ")"<< endl;
      }
    }
  }
  
}
// use this function when the items in the oldHash become .03 load factor
void HashTable::moveRemainingItems() {
  
  if(hashSize > 0) {
    for (int i = 0; i < hashTableCapacity; i++) {
      if (oldHash[i] != nullptr && strcmp(oldHash[i],DELETED) != 0)
	insertIntoSecondTable(oldHash[i]);
    }
  }
  // moving items over and getting rid of second Table and making it the first one
  hashTableCapacity = newCapacity;
  hashSize = newSize;
  delete [] oldHash;
  oldHash = new char*[hashTableCapacity];
  
  for(int i = 0; i < hashTableCapacity; i++){
    oldHash[i] = nullptr;
  }
  
  for (int k = 0; k < newCapacity; k++) {
    if(newHash[k] != nullptr){
      oldHash[k] = strdup(newHash[k]);
      free(newHash[k]);
      newHash[k] = nullptr;
    }
  }
  
  newSize = 0;
  isRehashTrue = false;
  
  delete [] newHash;
  newSize = 0;
  
  newCapacity = roundUpPrime(hashTableCapacity + 1);
  newHash = new char*[newCapacity];
  
  for(int i = 0; i < newCapacity; i++){
    newHash[i] = nullptr;
  }
}

// when all is given up, moving to the thirdArray
void HashTable::moveAllToThird() {
  checkForInsertIntoSecond = true;
  giveUp = false;
  
  // store a temp Hash table for all the elements
  // four times the items and then rounded to prime
  int totalNumberOfItems = hashSize + newSize;
  int thirdCapacity = roundUpPrime(4 * totalNumberOfItems);
  char **tempHashTable = new char*[thirdCapacity];
  for(int i = 0; i < thirdCapacity; i++){
    tempHashTable[i] = nullptr;
  }
  
  
  // take all the items from the new
  for(int j = 0; j < newCapacity; j++){
    if(newHash[j] != nullptr && strcmp(newHash[j],DELETED) != 0){
      unsigned int hashedString = hashCode(newHash[j]);
      int hashedValue = hashedString % thirdCapacity;
      
      // if the index is empty, place the hashed value there
      if(tempHashTable[hashedValue] == nullptr) {
	tempHashTable[hashedValue] = strdup(newHash[j]);
      }else{
	// using linear probing, until next null spot
	while(tempHashTable[hashedValue] != nullptr){
	  hashedValue++;
	  if(hashedValue == thirdCapacity){
	    hashedValue = 0;
	  }
	}
	tempHashTable[hashedValue] = strdup(newHash[j]);
      }
      free(newHash[j]);  
    }
    //free(newHash[j]);
    newHash[j] = nullptr;
  }
  newSize = 0;
  
  // take all the elements from the old
  for (int k = 0; k < hashTableCapacity; k++) {
    if(oldHash[k] != nullptr && oldHash[k] != DELETED){
      unsigned int hashedString = hashCode(oldHash[k]);
      int hashedValue = hashedString % thirdCapacity;
      
      // if the index is empty, place the hashed value there
      if(tempHashTable[hashedValue] == nullptr) {
	tempHashTable[hashedValue] = strdup(oldHash[k]);
      }else{
	// using linear probing, until next null spot
	while(tempHashTable[hashedValue] != nullptr){
	  hashedValue++;
	  if(hashedValue == thirdCapacity){
	    hashedValue = 0;
	  }
	}
	tempHashTable[hashedValue] = strdup(oldHash[k]);
      }
      free(oldHash[k]);
    }
    
    oldHash[k] = nullptr;
    
  }
  
  
  // make the largest(Third Temp Hash table set to the old one)
  hashTableCapacity = thirdCapacity;
  hashSize = totalNumberOfItems;
  
  delete [] oldHash;
  
  oldHash = new char*[thirdCapacity];
  for(int i = 0; i < thirdCapacity; i++){
    oldHash[i] = nullptr;
  }
  
  for (int k = 0; k < hashTableCapacity; k++) {
    
    if(tempHashTable[k] != nullptr){
      
      oldHash[k] = strdup(tempHashTable[k]);
      
      free(tempHashTable[k]);
      tempHashTable[k] = nullptr;
    }
  }
  delete [] tempHashTable;
  
}

bool HashTable::isRehashing() {
  return isRehashTrue;
}

int HashTable::tableSize(int table) {
  if(table == 0){
    return hashTableCapacity;
  }
  else{
    return newCapacity;
  }
}

int HashTable::size(int table) {
  if(table == 0){
    return hashSize;
  }
  else{
    return newSize;
  }
}

const char *HashTable::at(int index, int table) {
  if (table == 0 && oldHash[index] != DELETED) {
    return oldHash[index];
  }
  else if (table == 1 && newHash[index] != DELETED) {
    return newHash[index];
  }
  else
    return NULL;
}




void HashTable::moveCluster(int index){
  
  // we go to the beginning of the cluster 
    while(oldHash[index] != nullptr){
      index--;
      if(index < 0){
	index = hashTableCapacity - 1;
      }
    }
    
    index++;
    
    // goes through the cluster and adds the elements to the
    // second array
    while(oldHash[index] != nullptr && oldHash[index] != DELETED){
      if(oldHash[index] != DELETED && oldHash[index] != nullptr){

	insertIntoSecondTable(oldHash[index]);
	free(oldHash[index]);
	oldHash[index] = nullptr;
	index++;
	index %= hashTableCapacity;
	hashSize--;
	
      }
    }
}






