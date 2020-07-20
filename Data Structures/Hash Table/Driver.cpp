// File: Driver.cpp
// Author: Alex Simak
// Testing the functions
#include <iostream>
#include <cstdlib>
#include <set>
using namespace std ;

#include "HashTable.h"
#include "words.h"


bool isInSet(set<string>& S, const char * str) ;
void addToSet(set<string>& S, const char *str) ;
void removeFromSet(set<string>& S, const char *str) ;
void sanityCheck(HashTable& T, set<string> S) ;


int main() {
   HashTable A(107) ;

   set<string> S ;
   
   for(int i = 0; i < 800; i+=10){
     A.insert(words[i]);
   }
    
   cout << "----------------------------------------------------\n" ;
   cout << "Original hash table\n" ;
   cout << "----------------------------------------------------\n" ;
   cout << "Size should be 80 and Capacity should be 331" << endl;
   A.dump() ;
   cout << "----------------------------------------------------\n" ;
   
   
   for (int i=500 ; i < 600 ; i+=10) {
     if(A.find(words[i])){
       cout << "Found: " << words[i] << endl;
     }
     else
       cout << "Did not find :" << words[i] << endl;
   }
   
   
   char *ptr ;
   const char *str ;
   // testing different remove operations 
   
   ptr = A.remove(str=words[1000]) ;
   if (ptr == NULL) {
     cout << "String " << str << " not found, not removed\n" ;
   } else {
     cout << "Removed string = " << ptr << endl ;
     free(ptr) ;
   }
   
   
   ptr = A.remove(str=words[100]) ;
   if (ptr == NULL) {
     cout << "String " << str << " not found, not removed\n" ;
   } else {
     cout << "Removed string = " << ptr << endl ;
     free(ptr) ;
   }
   
   
   cout << "----------------------------------------------------\n" ;
   cout << "Hash table after a couple Finds and Deletions \n" ;
   cout << "----------------------------------------------------\n" ;
   A.dump() ;
   cout << "----------------------------------------------------\n" ;



   // starts a massive test with lots of inserts and finds 
   HashTable T(883) ;
    // insert 30,000 words
    for (int i=20000 ; i < 50000 ; i++) {
        T.insert(words[i]) ;  addToSet(S,words[i]) ;
    }

    int r ;
    int Tcount = 0 ;
    int Scount = 0 ;
    srand(843150) ;
    for (int i=0 ; i<10000 ; i++) {
        r = rand() % numWords ;
        if ( T.find(words[r]) ) Tcount++ ;
        if ( isInSet(S,words[r]) ) Scount++ ;
    }

    if (Tcount == Scount) {
        cout << "Passed random find() tests: "
             << "Tcount = " << Tcount << ", "
             << "Scount = " << Scount << endl ;
    } else {
        cout << "***Failed random find() tests: "
             << "Tcount = " << Tcount << ", "
             << "Scount = " << Scount << endl ;
    }

    sanityCheck(T,S) ;

    return 0 ;
}


bool isInSet(set<string>& S, const char * str) {
    set<string>::iterator it ;

    it = S.find(str) ;
    if (it != S.end() ) return true ;
    return false ;
}


void addToSet(set<string>& S, const char *str) {
    pair< set<string>::iterator, bool>  p ;

    p = S.insert(str) ;
}


void removeFromSet(set<string>& S, const char *str) {
    S.erase(str) ;
}


void sanityCheck(HashTable& T, set<string> S) {

    int Tsize ;
    const char * ONE = (char *) 1 ;

    // Check hash table size vs set size
    //
    if ( T.isRehashing() ) {
        Tsize = T.size(0) + T.size(1) ;
    } else {
        Tsize = T.size(0) ;
    }

    if ( Tsize == S.size() ) {
        cout << "Sets sizes are both " << Tsize << endl ;
    } else {
        cout << "Sets sizes are different:  "
             << "T size = " << Tsize << ", "
             << "S.size() = " << S.size() << endl ;
    }

    // Construct STL set<string> for all strings in the hash table
    //
    set<string> Tset ;
    const char *str ;

    int n = T.tableSize(0) ;
    for (int i=0 ; i < n ; i++) {
        str = T.at(i,0) ;
        if (str != NULL && str != ONE) addToSet(Tset,str) ;
    }
    if ( T.isRehashing() ) {
        n = T.tableSize(1) ;
        for (int i=0 ; i < n ; i++) {
            str = T.at(i,1) ;
            if (str != NULL && str != ONE) addToSet(Tset,str) ;
        }
    }

    set<string>::iterator it ;

    int inSnotT = 0 ;
    int inTnotS = 0 ;

    for (it = S.begin() ; it != S.end() ; it++) {
        if (! isInSet(Tset, it->c_str()) ) inSnotT++ ;
    }

    for (it = Tset.begin() ; it != Tset.end() ; it++) {
        if (! isInSet(S, it->c_str()) ) inTnotS++ ;
    }

    if (inSnotT == 0 && inTnotS == 0) {
        cout << "Passed set equality test\n" ;
    } else {
        cout << "***Failed set equality test\n" ;
        cout << "   " << inSnotT << " words in set S but not in hash table T.\n" ;
        cout << "   " << inTnotS << " words in hash table T but not in set S.\n" ;
    }

}
   
   
