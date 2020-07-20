// File: test5.cpp
//
// Insertions trigger rehashing.
//
// Testing copy constructor and assignment operator
//


#include <iostream>
#include <cstdlib>
#include <set>
#include <string>
using namespace std ;

#include "HashTable.h"

bool isInSet(set<string>& S, const char * str) ;
void addToSet(set<string>& S, const char *str) ;
void removeFromSet(set<string>& S, const char *str) ;
void sanityCheck(HashTable& T, set<string> S) ;

int main() {
   HashTable T(107) ;

   T.insert("undulation") ;     //  9
   T.insert("impertinent") ;    // 10
   T.insert("maladies") ;       // 10 -> 11
   T.insert("dominions") ;	// 12

   T.insert("waspish") ;        // 52
   T.insert("wildebeest") ;     // 52 -> 53
   T.insert("reaction") ;       // 52 -> 54

   T.insert("pawns") ;          // 43
   T.insert("vacuously") ;      // 43 -> 44
   T.insert("firth") ;          // 43 -> 45
   T.insert("manipulator") ;    // 43 -> 46
   T.insert("dreariness") ;     // 43 -> 47

   T.insert("insanity") ;       // 105
   T.insert("enthronement") ;   // 105 -> 106
   T.insert("falsifiers") ;     // 105 -> 0
   T.insert("ignominious") ;    // 105 -> 1
   T.insert("mummified") ;      // 105 -> 2

   T.insert("tributes") ;	// 21
   T.insert("skulduggery") ;	// 22
   T.insert("convulse") ;	// 23
   T.insert("frothed") ;	// 24
   T.insert("horrify") ;	// 25
   T.insert("blackmailers") ;	// 26
   T.insert("defenestrated") ;	// 27
   T.insert("garrison") ;	// 23 -> 28
   T.insert("lidless") ;	// 22 -> 29
   T.insert("eye") ;            // 21 -> 30, should trigger inc. rehash

   set<string> S ;

   addToSet(S,"undulation") ;
   addToSet(S,"impertinent") ;
   addToSet(S,"maladies") ;
   addToSet(S,"dominions") ;
   addToSet(S,"waspish") ;
   addToSet(S,"wildebeest") ;
   addToSet(S,"reaction") ;
   addToSet(S,"pawns") ;
   addToSet(S,"vacuously") ;
   addToSet(S,"firth") ;
   addToSet(S,"manipulator") ;
   addToSet(S,"dreariness") ;
   addToSet(S,"insanity") ;
   addToSet(S,"enthronement") ;
   addToSet(S,"falsifiers") ;
   addToSet(S,"ignominious") ;
   addToSet(S,"mummified") ;
   addToSet(S,"tributes") ;
   addToSet(S,"skulduggery") ;
   addToSet(S,"convulse") ;
   addToSet(S,"frothed") ;
   addToSet(S,"horrify") ;
   addToSet(S,"blackmailers") ;
   addToSet(S,"defenestrated") ;
   addToSet(S,"garrison") ;
   addToSet(S,"lidless") ;
   addToSet(S,"eye") ;

   cout << "\nCheck original hash table T...\n" ;
   sanityCheck(T,S) ;

   // ----------------------------------------------------------------------
   
   HashTable *T2ptr = new HashTable(T) ;
   //HashTable T2(T);




   HashTable T3(*T2ptr) ;


   cout << "\nCheck hash tables T, *T2ptr & T3 after copying...\n" ;
   sanityCheck(T,S) ;
   sanityCheck(*T2ptr,S) ;
   sanityCheck(T3,S) ;

   delete T2ptr ;

   cout << "\nCheck hash tables T & T3 after deleting T2ptr...\n" ;
   sanityCheck(T,S) ;
   sanityCheck(T3,S) ;


   HashTable X(107) ;

   X.insert("undulation") ;     //  9
   X.insert("impertinent") ;    // 10
   X.insert("maladies") ;       // 10 -> 11
   X.insert("dominions") ;	// 12

   X.insert("waspish") ;        // 52
   X.insert("wildebeest") ;     // 52 -> 53
   X.insert("reaction") ;       // 52 -> 54

   X.insert("pawns") ;          // 43
   X.insert("vacuously") ;      // 43 -> 44
   X.insert("firth") ;          // 43 -> 45
   X.insert("manipulator") ;    // 43 -> 46
   X.insert("dreariness") ;     // 43 -> 47

   X.insert("insanity") ;       // 105
   X.insert("enthronement") ;   // 105 -> 106
   X.insert("falsifiers") ;     // 105 -> 0
   X.insert("ignominious") ;    // 105 -> 1
   X.insert("mummified") ;      // 105 -> 2

   X.insert("tributes") ;	// 21
   X.insert("skulduggery") ;	// 22
   X.insert("convulse") ;	// 23
   X.insert("frothed") ;	// 24
   X.insert("horrify") ;	// 25
   X.insert("blackmailers") ;	// 26
   X.insert("defenestrated") ;	// 27
   X.insert("garrison") ;	// 23 -> 28
   X.insert("lidless") ;	// 22 -> 29
   X.insert("eye") ;            // 21 -> 30, should trigger inc. rehash

   HashTable X2, X3 ;


   cout << "\nCheck original hash table X...\n" ;
   sanityCheck(X,S) ;

   X2 = X ;
  


   X3 = X2 ;
}
/*
   cout << "\nCheck hash tables X, X2 & X3 after assignment...\n" ;
   sanityCheck(X,S) ;
   sanityCheck(X2,S) ;
   sanityCheck(X3,S) ;

   X2.insert("wildcat") ;
   X2.insert("weightlessness") ;
   X2.insert("sorceress") ;
   X2.insert("enchantress") ;
   X2.insert("witchery") ;
   X2.insert("heliosphere") ;
   X2.insert("obstruct") ;

   cout << "\nCheck hash tables X & X3 after modifying X2...\n" ;
   sanityCheck(X,S) ;
   sanityCheck(X3,S) ;

}

*/


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
