import math
import time
import numpy as np
import random as rand


print("Player X, select 1 for Human, 2 for Random, 3 for Minimax: ")
player1 = input("> ")
print("Player O, select 1 for Human, 2 for Random, 3 for Minimax: ")
player2 = input("> ")

if(int(player1) > 3 or int(player1) < 0):
    print("Invalid Input.")
    exit(0)
if(int(player2) > 3 or int(player2) < 0):
    print("Invalid Input.")
    exit(0)

# Global Variables 
PLAYERCHOICE1 = player1
PLAYERCHOICE2 = player2

COLUMNS = 7
ROWS = 6

PLAYER1 = 1
PLAYER2 = 2

WINVALUE = 100000000000000


def heuristic(board,player):
    heuristicVal = 0

    # Vertical
    verticalArray = []
    for c in range(COLUMNS):
        
        verticalArray = [int(i) for i in list(board[:,c])]
        for r in range(ROWS-3):
            tempBoard = verticalArray[r:r+4]
            heuristicVal += heuristicScoreBoard(tempBoard, player)
    
    # Horizontal
    horizontalArray = []
    for r in range(ROWS):
        horizontalArray = [int(i) for i in list(board[r,:])]
        for r in range(COLUMNS-3):
            tempBoard = horizontalArray[r:r+4]
            heuristicVal += heuristicScoreBoard(tempBoard, player)

	# + diagonal
    for r in range(ROWS-3):
        for c in range(COLUMNS-3):
            tempBoard = [board[r+i][c+i] for i in range(4)]
            heuristicVal += heuristicScoreBoard(tempBoard, player)

    # - diagonal    
    for r in range(ROWS-3):
        for c in range(COLUMNS-3):
            tempBoard = [board[r+3-i][c+i] for i in range(4)]
            heuristicVal += heuristicScoreBoard(tempBoard, player)

    
    middle_column = []
    # found this notation online using a regular for loop seemed to give different and worse results
    middle_column = [int(i) for i in list(board[:,COLUMNS//2])]
    # seeing how many times the player has already been in that specific column
    # the middle column is favored because the possible diagonals and horizontals have a 
    # higher chance to connect
    heuristicVal += (middle_column.count(player)) * COLUMNS//2

    return heuristicVal

# psuedo taken from wiki of Minimax 
# the whoIsGoing was just for me and debugging purposes 
def minimax(board, depth, maximizingPlayer,whoIsGoing):

    type2 = PLAYER2
    type1 = PLAYER1
    
    # base case scenario for Minimax checking if we are at the 0 depth or if game is done 
    if (depth == 0 or isGameFinished(board)):
        if (isGameFinished(board)):
            if (winningState(board, type2)):
                return (None, WINVALUE)
            elif (winningState(board, type1)):
                return (None, -WINVALUE)
            else: # Game is over, no more valid moves
                return (None, 0)
        else: # Depth is zero
            return (None, heuristic(board, type2))
    
    columnPick = rand.choice(getValidLocation(board))

    if(maximizingPlayer):
        keepingTrackofValues = -math.inf
        
        for columns in getValidLocation(board):
            # want to create a temporary board that mimics the game so minimax can afformulate a tree with the possiblities 
            tempBoard = board.copy()
            # drop piece into the tempBoard
            tempBoard[nextFreeRow(board, columns)][int(columns)-1] = type2
            # recurislvy calling minimax switching the min and max 
            highestVal = minimax(tempBoard, depth-1, False,whoIsGoing)[1]
            # if the value is higher ( want to maximize) go that path
            if(highestVal > keepingTrackofValues):
                keepingTrackofValues = highestVal
                columnPick = columns


    else:
        keepingTrackofValues = math.inf

        for columns in getValidLocation(board):
            tempBoard = board.copy()

            tempBoard[nextFreeRow(board, columns)][int(columns)-1] = type1

            lowestScore = minimax(tempBoard, depth-1, True,whoIsGoing)[1]
            
            if(lowestScore < keepingTrackofValues):
                keepingTrackofValues = lowestScore
                columnPick = columns

    return columnPick, keepingTrackofValues

def newBoard():
    return np.zeros((ROWS,COLUMNS))

def printBoard(board):
    print("1 2 3 4 5 6 7")
    # I want the board to output flipped so i start with the highest row and print opposite 
    r = ROWS - 1
    while(r > -1):
        for c in range(COLUMNS):
            if(board[r][c] == 0):
                print("-", end = " ")
            elif(board[r][c] == 1):
                print("X", end = " ")
            elif(board[r][c] == 2):
                print("O", end = " ")
        print()
        r -= 1
    print()

# printing a blank board to start with to show the players the options of where to go
board = newBoard()
printBoard(board)

def winningState(board,player):
    # Check horizontal locations for win
	for c in range(COLUMNS-3):
		for r in range(ROWS):
			if board[r][c] == player and board[r][c+1] == player and board[r][c+2] == player and board[r][c+3] == player:
				return True

	# Check vertical locations for win
	for c in range(COLUMNS):
		for r in range(ROWS-3):
			if board[r][c] == player and board[r+1][c] == player and board[r+2][c] == player and board[r+3][c] == player:
				return True

	# Check positively sloped diaganols
	for c in range(COLUMNS-3):
		for r in range(ROWS-3):
			if board[r][c] == player and board[r+1][c+1] == player and board[r+2][c+2] == player and board[r+3][c+3] == player:
				return True

	# Check negatively sloped diaganols
	for c in range(COLUMNS-3):
		for r in range(3, ROWS):
			if board[r][c] == player and board[r-1][c+1] == player and board[r-2][c+2] == player and board[r-3][c+3] == player:
				return True

def nextFreeRow(board,c):
    for r in range(ROWS):
        if((board[r][int(c)-1]) == 0):
            return r

def getValidLocation(board):
    validLocations = []
    for c in range(COLUMNS):
        if (board[ROWS-1][int(c)-1] == 0):
            validLocations.append(c)
    return validLocations

def heuristicScoreBoard(board, player):
    heuristicScore = 0
    enemy = PLAYER1
    if player == PLAYER1:
        enemy = PLAYER2

    # using .count to count the occurances of that player on the board
    # I tried a bunch of times to get random scores based on the results of the game thats why they are random 
    
    # postive player count
    if board.count(player) == 4:
        heuristicScore +=   500
    elif board.count(player) == 3 and board.count(0) == 1:
        heuristicScore += 20
    elif board.count(player) == 2 and board.count(0) == 2:
        heuristicScore += 10

    # negative player count
    elif board.count(enemy) == 3 and board.count(0) == 1:
        heuristicScore -= 25

    return heuristicScore

def isGameFinished(board):
    return (winningState(board, PLAYER1) or winningState(board, PLAYER2) or len(getValidLocation(board)) == 0)

def checkForTie(board):
    continGame = 0
    hasZero = 0
    for r in range(ROWS):
        for c in range(COLUMNS):
            if(board[r][c] == 0):
                hasZero = 1
                continGame = 0
            else:
                continGame = 1
    if(continGame == 1 and hasZero == 0):
        return True
    return False          

def playGame():
    
    winner = 0
    gameOver = False
    turn = rand.randint(1,2)

    while(not gameOver):
        
        if(checkForTie(board)):
            print("Game Over! Its a Tie!")
            gameOver = True
            break

        if(turn == PLAYER1):
            # --------------------------------------------------------- PLAYER 1 ---------------------------------------------------
            if(int(PLAYERCHOICE1) == 1):
                print("Player X move? ")
                col_input = input("> ")
                print()
            # ----------------------------------------------------------- RANDOM 1 -------------------------------------------------
            elif(int(PLAYERCHOICE1) == 2):
                col_input = rand.choice(getValidLocation(board))

                time.sleep(.5)
            # ----------------------------------------------------------- MINIMAX 1 ------------------------------------------------
            elif(int(PLAYERCHOICE1) == 3):
                col_input, a_ = minimax(board,4,True,PLAYER1)
            
            output = 0
            if(col_input == 0):
                    output = 7
                    print("X's Went: ", output)
            else:
                print("X's Went: ", col_input)

            if(board[ROWS-1][int(col_input)-1] == 0):
                row = nextFreeRow(board,col_input)

                board[row][int(col_input)-1] = PLAYER1
                if(winningState(board,PLAYER1)):
                    winner = PLAYER1
                    gameOver = True
                else:
                    turn += 1

        print("--------------")
        printBoard(board)  

        if(checkForTie(board)):
            print("Game Over! Its a Tie!")
            gameOver = True
            break
        # -----------------------------------------------------------PLAYER 2-------------------------------------------------------------
        if(turn == PLAYER2):
            if(int(PLAYERCHOICE2) == 1):
                print("Player O move? ")
                col_input = input("> ")
                print()
            # ----------------------------------------------------------- RANDOM 2 -------------------------------------------------
            elif(int(PLAYERCHOICE2) == 2):
                col_input = rand.choice(getValidLocation(board))
                time.sleep(.5)
            # ----------------------------------------------------------- MINIMAX 2 ------------------------------------------------
            elif(int(PLAYERCHOICE2) == 3):
                col_input, a_ = minimax(board,3,True,PLAYER2)
            if(col_input == 0):
                    output = 7
                    print("O's Went: ", output)
            else:
                print("O's Went: ", col_input)

            if(board[ROWS-1][int(col_input)-1] == 0):
                row = nextFreeRow(board,col_input)
                board[row][int(col_input)-1] = PLAYER2
                if(winningState(board,PLAYER2)):
                    print()
                    winner = PLAYER2
                    gameOver = True
                else:
                    turn -= 1

        if(winner == PLAYER1):
            output = "X"
        elif(winner == PLAYER2):
            output = "O"
        if(gameOver):
            print("Game over! " + output + "'s have won!")

        print("--------------")
        printBoard(board)
       
playGame()