// Author: Alex Simak
// Date Due: 3/27/18
// Dragon Wars Spring 2018 Project
// File Name: Game.cpp

#include "Dragon.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>

using namespace std;
const int TOTAL_NUM_OF_CHAR = 255;

// Name: Game() Default Constructor
// Desc - Builds a new game by:
// 1. Asking user for their name,
// 2. Loading all dragons from file (function call)
// Preconditions - None
// Postconditions - m_dragons is populated
Game::Game(){ // Constructor for Game

  cout << "Welcome to Dragon Wars\n";
  cout << "What is your name?\n";
  getline(cin,m_name);
  LoadDragons();
  
}

// Name: StartGame()
// Desc - Manages the game itself including win conditions continually
//        calling the main menu
void Game::StartGame(){
  MainMenu();  
}

// Name: Attack()
// Desc - Manages the dragons attacking each other
// Preconditions - Player has hatched dragons
// Postconditions - Player attacks a random dragon of random size
void Game::Attack(){

  cout << "Attack!" << endl;
  // Seeds random to make sure the random is different everytime
  srand(time(NULL));

  // Randomly picks a dragon from the whole m_dragons vector to fight against 
  int randomDragonToFight = rand() % m_dragons.size();
  cout << "You found a ";
  cout << m_dragons[randomDragonToFight].GetName() << " to fight!\n" << endl;

  // Makes sure the dragon is hatched and ready to fight
  m_dragons[randomDragonToFight].HatchDragon();

  // Gets a random size for the random dragon to fight against
  int randDragonSizeVar = 0;
  if(m_dragons[randomDragonToFight].GetMaxSize() != 0){
    randDragonSizeVar = rand() % m_dragons[randomDragonToFight].GetMaxSize() + 1;
  }

  // Converts to enum through an array to get the enum
  dragonSize randDragonSize[] = {tiny,small,medium,large,huge};
  m_dragons[randomDragonToFight].SetCurSize(randDragonSize[randDragonSizeVar]);
  
  string userChoiceToFight;
  cout << "Do you want to fight it? (y/n)\n";
  cin >> userChoiceToFight;

  // If the user chooses not to fight, they return  back to the main menu
  if(userChoiceToFight == "n"){
    return;
  }
  else{
    // Checks to make sure m_myDragons actually has some dragons in it
    // Then asks the user to pick a dragon they want to fight with
    if(m_myDragons.size() > 0){
      DisplayMyDragons();
      int userDragonSelection;
      cout << "Which dragon would you like to fight with?\n";
      cin >> userDragonSelection;
      // Have to make it '-1' because the vector starts from 0 but displays 1
      userDragonSelection = userDragonSelection - 1;
      
      // Originally the Dragons are eggs
      if(!m_myDragons[userDragonSelection].GetIsHatched()){
	cout << "Please choose a dragon, not an egg next time you attack!\n";
      }
      else{
	DisplayMyDragons();
	cout << "Fight\n";
	// Uses the AttackDragon method to fight the two dragons 
	// If the user wins, the AttackDragon is True
	if(m_myDragons[userDragonSelection].AttackDragon(m_dragons[randomDragonToFight])){
	  cout << "Your " << m_myDragons[userDragonSelection].GetName();
	  cout << " defeats the enemy " << m_dragons[randomDragonToFight].GetName() << "!\n";
	  m_myDragons[userDragonSelection].AttemptGrow();
	}
	// If the Dragon the user selects loses
	else{
	  cout << "The enemy " << m_dragons[randomDragonToFight].GetName();
	  cout << " defeated your " << m_myDragons[userDragonSelection].GetName() <<endl;
	  // Erases that defeated dragon from myDragons
	  m_myDragons.erase(m_myDragons.begin()+ userDragonSelection);
	}
      }
    }
    // In Case the user tries to Attack but their m_myDragons is empty
    else{
      cout << "You have no Dragons!\n";
    }
  }

}

// Name: LoadDragons
// Desc - Loads each dragon into m_dragon from file
// Preconditions - Requires file with valid dragon data
// Postconditions - m_dragons is populated with Dragon objects
void Game::LoadDragons(){
  
  ifstream inputStream;
  inputStream.open(PROJ2_DRAGONS.c_str());
  // Making a temp array to hold line by line
  // Max char that a line can be is 255 chars
  char line[TOTAL_NUM_OF_CHAR];
  inputStream.getline(line,TOTAL_NUM_OF_CHAR);

  // As long as the inputStream can still input data
  while(inputStream){
    // Initializing all the variables
    string dragonName = "";
    string dragonType = "";
    int dragonMaxSize = 0;
    string rarity = "";
    int dragonRarity = 0;
    int commaCnt = 0;
    char dragonMaxSizeCStr[1];

    // Goes through the line to get each individual Varible
    // such as Name, Type, Sizes, Raritys
    for(int i = 0; i < TOTAL_NUM_OF_CHAR;i++){
      if(line[i] == ','){
	// Uses the commas to seperate the variables from each other
	commaCnt += 1;
      }
      // First comma is the Name
      if (line[i] != ',' && commaCnt == 0){
	dragonName += line[i];
      }
      // Second comma is the Type
      if (line[i] != ',' && commaCnt == 1){
        dragonType += line[i];
      }
      // Third comma is the MaxSize
      if (line[i] != ',' && commaCnt == 2){
	dragonMaxSizeCStr[0] = line[i];
	dragonMaxSize = atoi(dragonMaxSizeCStr);
      }
      // Fourth comma is for the rarity 
      if (line[i] != ',' && commaCnt == 3){
        rarity += line[i];
      }
      // Sets the i equal to 255 when the input is a endline char
      // So that the loops ends if needed 
      if(line[i] == '\n'){
	i = TOTAL_NUM_OF_CHAR;
      }
    }

    dragonSize enDragonMax;
    // Has to convert the int to the dragonSize Type
    if(dragonMaxSize == 1)
      enDragonMax = tiny;

    if(dragonMaxSize == 2)
      enDragonMax = small;

    if(dragonMaxSize == 3)
      enDragonMax = medium;

    if(dragonMaxSize == 4)
      enDragonMax = large;

    if(dragonMaxSize == 5)
      enDragonMax = huge;

    dragonRarity = atoi(rarity.c_str());
    // Makes the dragon object with each individual quality
    // Adds it to the m_dragons
    Dragon dragon(dragonName,dragonType,false,tiny,enDragonMax,dragonRarity);
    m_dragons.push_back(dragon);
    inputStream.getline(line,TOTAL_NUM_OF_CHAR);  
  }
  inputStream.close();
}

// Name: DisplayAllDragons (Test Function)
// Desc - Used to test that all dragons were loaded into m_dragons correctly
// Preconditions - Requires file with valid dragon data
// Postconditions - m_dragons is displayed (all relevant data from m_dragons)
void Game::DisplayAllDragons(){
  // Display uses a series of width changes and couts 
  // to display the output in an organized table

  unsigned int dragonSize = (int)m_dragons.size();
  cout <<  "********************\n";
  cout << "All Dragons\n";
  // using cout.width to display the output organized
  cout.width(30);
  cout << right << "Name";
  cout.width(10);
  cout << right << "Type";
  cout.width(15);
  cout << right << "Egg/Dragon";
  cout.width(15);
  cout << right << "Current Size";
  cout.width(10);
  cout << right << "MaxSize\n";
  
  // Loops through the m_dragons and prints out all the dragon objects 
  for(unsigned int i = 0; i < dragonSize; i++){  
    cout.width(4);
    cout << right << (i + 1) << ".";
    cout.width(25);
    cout << right << m_dragons[i].GetName();
    cout.width(10);
    cout << right << m_dragons[i].GetType();
    cout.width(15);
    
    if(m_dragons[i].GetIsHatched() == 0){
      cout << right << "egg";
    }
    else{
      cout << right << "dragon";
    }

    cout.width(15);
    //adding 1 because enum starts at 0
    cout << right << m_dragons[i].GetCurSize() + 1;
    cout.width(9);
    //adding 1 because enum starts at 0
    cout << right << m_dragons[i].GetMaxSize() + 1 <<  endl;
  }
}

// Name: SearchEgg
// Desc - Randomly chooses an egg and adds to players dragon vector
// Preconditions - m_dragons is populated
// Postconditions - m_myDragons is populated
void Game::SearchEgg(){

  int userRarity;

  do{
  cout << "What rarity egg would you like to search for?\n";
  cout << "Enter a rarity (1 = very common and 10 = very rare):\n";
  cin >> userRarity;
  }while(userRarity > 10 || userRarity < 1);
  
  unsigned int dragonSize = (int) m_dragons.size();
  // Temporary Dragons vector 
  vector <Dragon> tempDragon;
  // Takes all the dragons with the same raritys that the user selects
  // And copies them into a temp vector

  for(unsigned int i = 0; i < dragonSize-1; i++){
    if(m_dragons[i].GetRarity() == userRarity){
      // Checks to see if the found dragon is already in myDragons
      // To not add the same dragon twice
      bool found = false;
      unsigned int myDragonSize = (int)m_myDragons.size();
      for(unsigned int j = 0; j < myDragonSize; j++){
	if(m_myDragons[j].GetName() ==  m_dragons[i].GetName())
	    found = true;
      }
      // If not found in myDragons vector, it adds to the temp vector
      if(!found){
	tempDragon.push_back(m_dragons[i]); 
      }
    }
  }

  unsigned int tempDragonSize = (int)tempDragon.size();
  // gets a random number to pick from the temporary vector
  // seeds random based on time  
  // to make sure the random value is within the range
  unsigned int randDragonWithRarity;
  //checks to see if there are anymore dragons with that specific rarity
  
  if(tempDragonSize > 1){
    do{
      srand(time(NULL));
      randDragonWithRarity = rand() % tempDragonSize;
    }while((randDragonWithRarity < 0 || randDragonWithRarity > tempDragonSize));
    // gets a random number 1-100
    int randomChance = rand() % 100 + 1; 
    int likelihood = 100 - (userRarity * 9);
    // Gets the random chance, and if it is less than or equal to,
    // it adds the dragon that the user was searching for
    if(randomChance <= likelihood){
      cout << "You found a " << tempDragon[randDragonWithRarity].GetName()<<endl;
      m_myDragons.push_back(tempDragon[randDragonWithRarity]);
    }
    else
      cout << "Sorry, you did not find a dragon of that rarity.\n"; 
  }
  else
    cout << "Sorry, you did not find a dragon of that rarity.\n";
}

// Name: DisplayMyDragons()
// Desc - Displays the current dragons (both hatched and unhatched)
// Preconditions - Player has dragons (either hatched or unhatched)
// Postconditions - Displays a numbered list of dragons
void Game::DisplayMyDragons(){

  // Uses cout.width to organize the output of the dragon objects
  unsigned int dragonSize = (int)m_myDragons.size();
  
  cout <<  "********************\n";
  cout << m_name <<"'s Dragons\n";
  cout.width(30);
  cout << right <<"Name";
  cout.width(10);
  cout << right << "Type";
  cout.width(15);
  cout << right << "Egg/Dragon";
  cout.width(15);
  cout << right << "Current Size";
  cout.width(10);
  cout << right << "MaxSize\n";
  
  // Loops through the m_myDragons vector and outputs each different aspect 
  for(unsigned int i = 0; i < dragonSize; i++){

    cout.width(4);
    cout << right << (i + 1) << ".";
    cout.width(25);
    cout << right << m_myDragons[i].GetName();
    cout.width(10);
    cout << right << m_myDragons[i].GetType();
    cout.width(15);

    if(m_myDragons[i].GetIsHatched() == 0){
      cout << right << "egg";
    }
    else{
      cout << right << "dragon";
    }
    cout.width(15);
    cout << right << m_myDragons[i].GetCurSize() + 1;
    cout.width(9);
    cout  << right << m_myDragons[i].GetMaxSize() + 1 <<  endl;
  }
}
 
// Name: HatchEgg
// Desc - Tries to change from egg to small dragon
// Preconditions - m_dragons is populated
// Postconditions - m_myDragons is populated
void Game::HatchEgg(){

  // If the user tries to Hatch an egg and they dont have any Dragons
  if(m_myDragons.size() == 0){
    cout << "Sorry you dont have any dragons.\n";
  }
  
  else{
    DisplayMyDragons();
    unsigned int userHatchSelection;
    int counter = 0;

    // Checks to make sure the user selects a dragon they actually have
    do{
      if(counter > 0){
	cout << "Dragon Doesnt Exist, try again.\n";
      }
      cout << "Which Dragon would you like to try and hatch? \n";
    cin >> userHatchSelection;
    counter++;
    }while(userHatchSelection < 1 || userHatchSelection > m_myDragons.size());

    // 50% chance that the egg actually hatches 
    srand(time(NULL));
    int randHatch = rand() % 100 + 1;
    // 50% chance or if the dragon is already hatched
    if((randHatch > 50) || m_myDragons[userHatchSelection - 1].GetIsHatched()){
      cout << "The dragon did not hatch or is already hatched\n";
    }
    else{
      m_myDragons[userHatchSelection - 1].HatchDragon();
      cout << "Your " << m_myDragons[userHatchSelection - 1].GetName() << " egg hatches into a dragon!\n"; 
    }
  }
}
// Name: MainMenu()
// Desc - Displays and manages menu
// Preconditions - None
// Postconditions - Returns number indicating exit
int Game::MainMenu(){
  
  int userMenuChoice;
  // loops the main menu until the user quits by hitting 5 
  do{
    do{
      cout << "What would you like to do?\n";
      cout << "1. Search or an egg\n";
      cout << "2. Try to hatch egg\n";
      cout << "3. Display all dragons and eggs\n";
      cout << "4. Attack!\n";
      cout << "5. Quit\n";
      cin >> userMenuChoice;
    }while(userMenuChoice > 5 || userMenuChoice < 1);

    // Uses a switch statement to go around what the user selects to work on
    switch(userMenuChoice)
      {
      case 1:
	SearchEgg();
	break;
      case 2:
	HatchEgg();
	break;
      case 3:
	DisplayMyDragons();
	break;
      case 4:
	Attack();
	break;
      case 5:
	cout << "Thank you for playing Dragon Wars!\n";
	exit(1);
	break;
      default:
	cout << "Unknown Error...\n";
	exit(1);
      }
  }while(userMenuChoice != 5);
  return 0;
}


