# File: proj3.py
# Author: Alex Simak
# Date: 11/28/17
# Section: 26
# E-mail: asimak1@umbc.edu
# Description:Program is supposed to recursively find a path
# for a maze from the starting point to the end
 

ROWSCOLSSTART = 2 #the index from the list which starts looking at each individual box 

#Indicies of the directions
RIGHT = 0 
BOTTOM = 1
LEFT = 2
TOP = 3

#represents closed wall
WALL = 1 


#####################################################################
# getValidInput() gets a valid integer from the user that
#                 falls within the appropriate range; uses
#                 a prompt provided at function call
# Input:          newInt;  an integer that will be inputed
#                 maximum; a maximum integer
# Output:         newInt; an integer within the range

def getValidInput(newInt, maximum):    
    while  newInt > maximum or newInt < 0:
        newInt = input("Invalid, enter a number between 0 and "+  \
                       str(maximum) + "(inclusive): ")
        newInt = int(newInt)
    return newInt

#####################################################################
# readMaze()      This function should read in the maze specification
#                 from the filename specified, and return a maze data 
#                 structure
# Input:          filename; the file that will be read from
# Output:         mazeList; a 2D list that has all the values from 
#                 the file

def readMaze(filename):
    ifp = open(filename, "r")
    myFile = ifp.readlines()
    ifp.close()
    mazeList = []
    for i in range(len(myFile)):
        line = myFile[i].strip()
        eachLine = []
        line = line.split()
        for j in range(len(line)):
            eachLine.append(int(line[j]))
        mazeList.append(eachLine)     
    return mazeList
    

#####################################################################
# getMaxAndFinishDataList()   This function should read in the maze 
#                 specification and gets the top two rows and stores 
#                 them in their own seperate list 
# Input:          mazeList; the file that will be read from with the 
#                 whole file in a 2D list
# Output:         sepRowsAndCols; a 2D list that has the values from 
#                 the top two rows to get the demensions of the board

def getMaxAndFinishDataList(mazeList):
    sepRowsAndCols = []
    for i in range(ROWSCOLSSTART):
        sepRowsAndCols.append(mazeList[i])
    return sepRowsAndCols


#####################################################################
# getOpenClosedSidesList()  This function reads in the maze 
#                 specification data and gets rows after the first 
#                 two rows and stores them in their  own seperate list  
# Input:          originalMazeList; a 2D list that contains the 
#                 original data from the file  
# Output:         openCloseList; a 2D list that has the values to know  
#                 which side of the cell is open or closed 

def getOpenClosedSidesList(originalMazeList):
    openCloseList = []
    for i in range(ROWSCOLSSTART, len(originalMazeList)):
        openCloseList.append(originalMazeList[i])
        
    return openCloseList

#####################################################################
# buildMazeList() This function will read in the maze specification 
#                 from a 2D list and make a 3D list from it                  
# Input:          openCloseList; a 2D list with specifications for 
#                 the maze which includes side data for each cell    
#                 maxRow; the maximum rows 
#                 maxCol; the maximum Columns
# Output:         mazeList; a 3D list that has the values to know  
#                 which part of the cell is open or closed at each 
#                 row and column

def buildMazeList(openCloseList, maxRow, maxCol):
    mazeList = []
    openCloseListCounter = 0
    for i in range(maxRow):
        rowList = []
        for j in range(maxCol):
            rowList.append(openCloseList[openCloseListCounter])
            openCloseListCounter += 1
        mazeList.append(rowList)
        
    return mazeList

#####################################################################
# searchMaze()    Using recursion, this function will find and 
#                 return a path from current point to a finish point
# Input:          mazeList; the file that will be read from
#                 pathList; 2D list with the path to the destination
#                 traveledList; a 2D list with points that have been 
#                 traveled to already so it doesnt go back and forth
#                 currentPoint; a list that holds the current point 
#                 finishPoint; the final point where it has to reach
# Output:         pathList; a 2D list that has all the points found
#                 from start to finish

def searchMaze(mazeList,pathList,traveledList,currentPoint,finishPoint):
    #base case, when the current point is equal to the final point
    if(currentPoint == finishPoint):
        pathList.append(currentPoint)
        return pathList
    
    #recursive cases
    else:
        currentRow = currentPoint[0]
        currentCol = currentPoint[1]
        #appends current point to traveled list so that the point 
        #does not get added to the pathlist multiple times so it 
        #wont get stuck in a loop
        traveledList.append(currentPoint)
        tempPathList = []
        
        #gets to see if there is a wall to the RIGHT using 
        #indexing from a 3D list (mazeList)
        if mazeList[currentRow][currentCol][RIGHT] != WALL:
            newCurrentPoint = [currentRow, currentCol + 1]
            #uses the function isPointInList to make sure the point is 
            #not already in the pathList or the traveled List then
            #if its all false, adds it to the pathList
            if(isPointInList(traveledList, newCurrentPoint) == False):
                if(isPointInList(pathList, currentPoint) == False):
                    pathList.append(currentPoint)
                copyPathList = getDeepCopy(pathList)
                tempPathList = (searchMaze(mazeList, copyPathList, traveledList, newCurrentPoint, finishPoint))
                #if the point is already in the list, the temporary
                #path list is returned empty 
                if(tempPathList != []):
                    return tempPathList
        #same idea as the previous if statements but this one checks
        #BOTTOM instead of right
        if mazeList[currentRow][currentCol][BOTTOM] != WALL:
            newCurrentPoint = [currentRow + 1, currentCol]
            if(isPointInList(traveledList, newCurrentPoint) == False):
                if(isPointInList(pathList, currentPoint) == False):
                    pathList.append(currentPoint)
                copyPathList = getDeepCopy(pathList)
                tempPathList = (searchMaze(mazeList, copyPathList, traveledList, newCurrentPoint, finishPoint))
                if(tempPathList != []):
                    return tempPathList
                

        #LEFT
        if mazeList[currentRow][currentCol][LEFT] != WALL:
            newCurrentPoint = [currentRow, currentCol - 1]
            if(isPointInList(traveledList, newCurrentPoint) == False):
                if(isPointInList(pathList, currentPoint) == False):
                    pathList.append(currentPoint)
                copyPathList = getDeepCopy(pathList)
                tempPathList = (searchMaze(mazeList, copyPathList, traveledList, newCurrentPoint, finishPoint))
                if(tempPathList != []):
                    return tempPathList
            
        #TOP        
        if mazeList[currentRow][currentCol][TOP] != WALL:
            newCurrentPoint = [currentRow - 1, currentCol]
            if(isPointInList(traveledList, newCurrentPoint) == False):
                if(isPointInList(pathList, currentPoint) == False):
                    pathList.append(currentPoint)
                copyPathList = getDeepCopy(pathList)
                tempPathList = (searchMaze(mazeList, copyPathList, traveledList, newCurrentPoint, finishPoint))
                if(tempPathList != []):
                    return tempPathList
    
    return tempPathList

#####################################################################
# isPointInList() This function will check if the current point is 
#                 already in a list, meant to check traveled List 
# Input:          traveledList; a 2D list with the points traveled 
#                 which the point has already taken
#                 currentPoint; a list with the current point values
# Output:         Boolean; a true or false value

def isPointInList(traveledList,currentPoint):
    for i in range(len(traveledList)):
        if(currentPoint == traveledList[i]):
            return True
    return False

#####################################################################
# getDeepCopy()   This function will make a deep copy of any 2D list 
# Input:          anyList; a 2D list that should be deep copied
# Output:         newList; a list copy of a 2D list

def getDeepCopy(anyList):
    newList = []
    for i in range(len(anyList)):
        inner = list(anyList[i])
        newList.append(inner)
    return newList

#####################################################################
# printList()     This function will print the path in a rows  
# Input:          pathList; a 2D list that contains the path
# Output:         None; doesnt return anything because it prints

def printList(pathList):
    for i in range(len(pathList)):
        print("("+ str(pathList[i][0])+ ", " + str(pathList[i][1])+ ")")
    print()
    
def main():
    print("Welcome to the Maze Solver!")
    filename = input("Please enter the filename of the maze: ")
    #initializes the mazeList
    initialMazeList = readMaze(filename)
    openCloseList = getOpenClosedSidesList(initialMazeList)
    sepRowsAndCols = getMaxAndFinishDataList(initialMazeList)
    
    #gets the maximum rows from the sepRowsAndCols list
    #prompts the user for the starting row 
    #validates the number of rows
    maximumRow = int(sepRowsAndCols[0][0]) - 1 
    startRow = int(input("Please enter the starting row: "))
    startRow = getValidInput(startRow, maximumRow)
   
    #gets the maximum columns from the sepRowsAndCols list
    #prompts the user for the starting column 
    #validates the number of columns
    maximumCol = int(sepRowsAndCols[0][1]) - 1 
    startCol =  int(input("Please enter the starting column: "))
    startCol = getValidInput(startCol, maximumCol)
    
    #makes the 2D openCloseList into mazeList into a 3D list
    mazeList = buildMazeList(openCloseList, maximumRow + 1, maximumCol + 1)
    
    #initializes the traveledList
    #initializes the pathList
    #initializes the current point
    #finds the finishRow and finishCol
    traveledList = []
    pathList = []
    currentPoint = [startRow, startCol]
    finishRow = int(sepRowsAndCols[1][0])
    finishCol = int(sepRowsAndCols[1][1])
    
    finishPoint = [finishRow, finishCol] 
    pathList = searchMaze(mazeList, pathList, traveledList, currentPoint, finishPoint)
    #checks to see if the pathList has any elements in it
    if(len(pathList) > 0):
        print("Solution Found!")
        printList(pathList)
    else:
        print("No Solution Found!")
main()
