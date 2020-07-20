#ifndef GAME_H //Header Guard
#define GAME_H //Header Guard

#include "Dragon.h"
#include <fstream>

const string PROJ2_DRAGONS = "proj2_data.txt"; //File constant

class Game{
public:
  /* Name: Game() Default Constructor
  // Desc - Builds a new game by: 
  // 1. Asking user for their name, 
  // 2. Loading all dragons from file (function call)
  // Preconditions - None
  // Postconditions - m_dragons is populated
  */ 
  Game(); //Default Constructor
  // Name: LoadDragons
  // Desc - Loads each dragon into m_dragon from file
  // Preconditions - Requires file with valid dragon data
  // Postconditions - m_dragons is populated with Dragon objects
  void LoadDragons();
  // Name: SearchEgg
  // Desc - Randomly chooses an egg and adds to players dragon vector
  // Preconditions - m_dragons is populated
  // Postconditions - m_myDragons is populated
  void SearchEgg();
  // Name: HatchEgg
  // Desc - Tries to change from egg to small dragon
  // Preconditions - m_dragons is populated
  // Postconditions - m_myDragons is populated
  void HatchEgg();
  // Name: StartGame()
  // Desc - Manages the game itself including win conditions continually
  //         calling the main menu 
  // Preconditions - Player has an egg or a dragon
  // Postconditions - Continually checks to see if player has an egg or a dragon
  void StartGame();
  // Name: DisplayMyDragons()
  // Desc - Displays the current dragons (both hatched and unhatched)
  // Preconditions - Player has dragons (either hatched or unhatched)
  // Postconditions - Displays a numbered list of dragons
  void DisplayMyDragons();
  // Name: MainMenu()
  // Desc - Displays and manages menu
  // Preconditions - Player has a dragon (either hatched or unhatched)
  // Postconditions - Returns number indicating exit
  int MainMenu();
  // Name: Attack()
  // Desc - Manages the dragons attacking each other
  // FYI: remove element at front of a vector is m_vectorName.erase(m_vectorName.begin());
  // Preconditions - Player has hatched dragons
  // Postconditions - Player attacks a random dragon of random size
  void Attack();
  // Name: DisplayAllDragons (Test Function)
  // Desc - Used to test that all dragons were loaded into m_dragons correctly
  // Preconditions - Requires file with valid dragon data
  // Postconditions - m_dragons is displayed (all relevant data from m_dragons)
  void DisplayAllDragons();
private:
  vector <Dragon> m_dragons; //All dragons in game
  vector <Dragon> m_myDragons; //Player's dragons
  int m_countHatchedDragons; //Current number of hatched dragons the player has (for attack)
  string m_name; //Player's name
};

#endif //Exit Header Guard
