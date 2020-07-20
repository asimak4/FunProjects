//
// File: HashTable.cpp
// Author: Alex Simak
// Date Due: December 11, 2018
// Class: CMSC 341
// Project 5
//


#ifndef CMSC341PROJECT5_HASHTABLE_H
#define CMSC341PROJECT5_HASHTABLE_H

#include <cstring>
#include "primes.h"

class HashTable {
public:
    unsigned int hashCode(const char *str);
    HashTable(int n=101) ;
    ~HashTable() ;
    HashTable (HashTable& other) ;
    const HashTable& operator= (HashTable& rhs) ;

    void insert(const char *str) ;
    void insertIntoSecondTable(const char *str);

    bool find(const char *str) ;

    bool findInTables(const char *str);

    char * remove(const char *str) ;
    void moveCluster(int);

    bool isRehashing() ;
    int tableSize(int table=0) ;
    int size(int table=0) ;
    const char * at(int index, int table=0) ;

    void removeClusterUP(const char *str);
    void removeClusterDOWN(const char *str);

    void moveRemainingItems();

    void dump() ;

    static char * const DELETED;

    void moveAllToThird();



private:

    bool isRehashTrue;
    bool giveUp;
    bool checkForInsertIntoSecond;


    char ** oldHash ;
    int hashTableCapacity;
    int hashSize;
    float loadFactor;

    int newCapacity;
    int newSize;
    int newLoadFactor;


    char ** newHash;
};


#endif //CMSC341PROJECT5_HASHTABLE_H
