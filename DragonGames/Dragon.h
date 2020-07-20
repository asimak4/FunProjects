#ifndef DRAGON_H //Include/Header Guard
#define DRAGON_H //Include/Header Guard

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>
using namespace std;

enum dragonSize { tiny, small, medium, large, huge};

class Dragon{
 public:
  // Name: Dragon() - Overloaded constructor
  // Desc - Used to build a new dragon
  // Preconditions - Requires name, type, isHatched, curSize, maxSize, and rarity (from file)
  // Postconditions - Creates a new dragon
  Dragon(string name, string type, bool isHatched, dragonSize curSize, 
	 dragonSize maxSize, int rarity);
  // Name: GetName()
  // Desc - Getter for Dragon name
  // Preconditions - Dragon exists
  // Postconditions - Returns the name of the dragon
  string GetName();
  // Name: SetName(string)
  // Desc - Allows the user to change the name of the dragon
  // Preconditions - Dragon exists
  // Postconditions - Sets name of dragon
  void SetName(string name);
  // Name: GetType()
  // Desc - Getter for dragon type
  // Preconditions - Dragon Exists
  // Postconditions - Returns the type of the dragon
  string GetType();
  // Name: SetType(string)
  // Desc - Allows the user to change the type of the dragon
  // Preconditions - Dragon exists
  // Postconditions - Sets type of dragon
  void SetType(string Type);
  // Name: GetIsHatched()
  // Desc - Getter for if dragon is hatched
  // Preconditions - Dragon exists
  // Postconditions - Returns if the dragon has hatched from an egg
  bool GetIsHatched();
  // Name: HatchDragon()
  // Desc - Setter for if dragon is hatched
  // Preconditions - Unhatched Dragon (In Egg form) exists
  // Postconditions - If unhatched, changes isHatched to 1
  void HatchDragon();
  // Name: GetCurSize()
  // Desc - Getter for dragon's current size
  // Preconditions - Dragon exists
  // Postconditions - Returns current size from 1 - 5
  dragonSize GetCurSize();
  // Name: SetCurSize(int)
  // Desc - Setter for the current dragon size
  // Preconditions - Dragon exists
  // Postconditions - Sets size of dragon (1-5)
  void SetCurSize(dragonSize curSize);
  // Name: GetMaxSize()
  // Desc - Getter for dragon max size
  // Preconditions - Dragon exists
  // Postconditions - Returns maximum size from 1 - 5
  dragonSize GetMaxSize();
  // Name: SetMaxSize(int)
  // Desc - Setter for the maximum dragon size
  // Preconditions - Dragon exists
  // Postconditions - Sets maximum size of dragon (1-5)
  void SetMaxSize(dragonSize maxSize);
  // Name: GetRarity()
  // Desc - Getter for dragon rarity
  // Preconditions - Dragon exists
  // Postconditions - Returns rarity of dragon (1-10)
  int GetRarity();
  // Name: SetRarity()
  // Desc - Setter for dragon rarity
  // Preconditions - Dragon exists
  // Postconditions - Sets rarity of dragon from (1-10)
  void SetRarity(int rarity);
  // Name: AttemptGrow()
  // Desc - After a dragon wins a fight, if possible, it grows larger
  // Preconditions - Dragons exist
  // Postconditions - If possible, curSize increases, if increases, returns true else false
  bool AttemptGrow();
  // Name: AttackDragon(Dragon&)
  // Desc - Allows the user to attack an enemy dragon
  // Preconditions - Dragons exist
  // Postconditions - Returns if dragon lives or dies (true lives, dies false)
  bool AttackDragon(Dragon&);
  // Name: BreathAttack(Dragon&)
  // Desc - Allows the user to attack an enemy dragon using a special breath attack
  //        Returns the string of the specific attack (different for acid, water, ice, fire, wind)
  // Preconditions - During normal attack, 5% chance a special breath attack called
  // Postconditions -  Automatically kills enemy dragon
  string BreathAttack();
 private:
  string m_name; //Name of Dragon
  string m_type; //Type of Dragon(water, fire, ice, acid, or wind)
  bool m_isHatched; //Egg or Hatched?
  dragonSize m_curSize; //What is the current dragon size?
  dragonSize m_maxSize; //What is the maximum dragon size?
  int m_rarity; //How rare is the dragon type (1-10)
};

#endif //Exit Header Guard
