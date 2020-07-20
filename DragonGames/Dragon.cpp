// Author: Alex Simak
// Date Due: March 27, 2018
// Dragon Wars Spring 2018
// File Name: Dragon.cpp

#include "Dragon.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

// Name: Dragon() - Overloaded constructor
// Desc - Used to build a new dragon
// Preconditions - Requires name, type, isHatched, curSize, maxSize, and rarity (from file)
// Postconditions - Creates a new dragon
Dragon::Dragon(string name, string type, bool isHatched, dragonSize curSize, dragonSize maxSize, int rarity){
  
  SetName(name);
  SetType(type);
  
  m_isHatched = false;
  if(isHatched){
    HatchDragon();
  }
  
  SetCurSize(curSize);
  SetMaxSize(maxSize);
  SetRarity(rarity);
    
}

// Name: SetName(string)
// Desc - Allows the user to change the name of the dragon
// Preconditions - Dragon exists
// Postconditions - Sets name of dragon
void Dragon::SetName(string name){
  m_name = name;   
}

// Name: SetType(string)
// Desc - Allows the user to change the type of the dragon
// Preconditions - Dragon exists
// Postconditions - Sets type of dragon
void Dragon::SetType(string type){
  m_type = type;
}

// Name: HatchDragon()
// Desc - Setter for if dragon is hatched
// Preconditions - Unhatched Dragon (In Egg form) exists
// Postconditions - If unhatched, changes isHatched to 1
void Dragon::HatchDragon(){
  m_isHatched = true;
}

// Name: SetCurSize(int)
// Desc - Setter for the current dragon size
// Preconditions - Dragon exists
// Postconditions - Sets size of dragon (1-5)
void Dragon::SetCurSize(dragonSize curSize){
  m_curSize = curSize;
}

// Name: SetMaxSize(int)
// Desc - Setter for the maximum dragon size
// Preconditions - Dragon exists
// Postconditions - Sets maximum size of dragon (1-5)
void Dragon::SetMaxSize(dragonSize maxSize){
  m_maxSize = maxSize;
}

// Name: SetRarity()
// Desc - Setter for dragon rarity
// Preconditions - Dragon exists
// Postconditions - Sets rarity of dragon from (1-10)
void Dragon::SetRarity(int rarity){
  m_rarity = rarity;
}

// Name: GetName()
// Desc - Getter for Dragon name
// Preconditions - Dragon exists
// Postconditions - Returns the name of the dragon
string Dragon::GetName(){
  return m_name;
}

// Name: GetType()
// Desc - Getter for dragon type
// Preconditions - Dragon Exists
// Postconditions - Returns the type of the dragon
string Dragon::GetType(){
  return m_type;
}

// Name: GetIsHatched()
// Desc - Getter for if dragon is hatched
// Preconditions - Dragon exists
// Postconditions - Returns if the dragon has hatched from an egg
bool Dragon::GetIsHatched(){
  return m_isHatched;
}

// Name: GetCurSize()
// Desc - Getter for dragon's current size
// Preconditions - Dragon exists
// Postconditions - Returns current size from 1 - 5
dragonSize Dragon::GetCurSize(){
  return m_curSize;
}

// Name: GetMaxSize()
// Desc - Getter for dragon max size
// Preconditions - Dragon exists
// Postconditions - Returns maximum size from 1 - 5
dragonSize Dragon::GetMaxSize(){
  return m_maxSize;
}

// Name: GetRarity()
// Desc - Getter for dragon rarity
// Preconditions - Dragon exists
// Postconditions - Returns rarity of dragon (1-10)
int Dragon::GetRarity(){
  return m_rarity;
}

// Name: AttemptGrow()
// Desc - After a dragon wins a fight, if possible, it grows larger
// Preconditions - Dragons exist
// Postconditions - If possible, curSize increases, if increases, returns true else false
bool Dragon::AttemptGrow(){
  // If the dragon's current size is less than its Max Size
  if(GetCurSize() < GetMaxSize()){
    if(GetCurSize() == tiny){
      SetCurSize(small);
    }
    else if(GetCurSize() == small){
      SetCurSize(medium);
    }
    else if(GetCurSize() == medium){
      SetCurSize(large);
    }
    else if(GetCurSize() == large){
      SetCurSize(huge);
    }
    cout << "Your dragon grows a bit larger\n";
    return true;
  }
  // When the dragon already is at its Max Size
  else{
    cout << "Your dragon cannot grow any larger\n";
    return false;
  }
}

// Name: AttackDragon(Dragon&)
// Desc - Allows the user to attack an enemy dragon
// Preconditions - Dragons exist
// Postconditions - Returns if dragon lives or dies (true lives, dies false)
bool Dragon::AttackDragon(Dragon& dragon){
  
  cout << "Your " << GetName() << " attacks the " << dragon.GetName() << "!\n";
  srand(time(NULL));
  int randBreath = rand() % 100 + 1;
  // Only a 5% chance that the dragon will breathe and win
  if(randBreath <= 5){
    cout << dragon.GetName() << " was taken down by ";
    cout << GetName() << "'s " << BreathAttack() << endl;
    return true;
  }
  else if(GetCurSize() > dragon.GetCurSize()){
    return true;
  }
  else if(GetCurSize() == dragon.GetCurSize()){
    cout << "The battle results in a draw\n";
    return true;
  }
  
  else if(GetCurSize() < dragon.GetCurSize()){
    return false;
  }
  return false;
}

// Name: BreathAttack()
// Desc - Allows the user to attack an enemy dragon using a special breath attack
//        Returns the string of the specific attack (different for acid, water, ice, fire, wind)
// Preconditions - During normal attack, 5% chance a special breath attack called
// Postconditions -  Automatically kills enemy dragon
string Dragon::BreathAttack(){
  return GetType();
  // Kill enemy done in Attack Dragon and Game Attack()
  
}

