# project2-part1-asimak4
project2-part1-asimak4 created by GitHub Classroom

## README: Tic-Tac-Toe Alex Simak

0.  I first installed the 5.5.0 default linux kernel to work my module in 
1.  Started out with implementing the Driver program through the tutorial that iboutsi1 (421 TA) set up on youtube. 
2.  I moved on and started configure the 00 X/O step where i would perform a new game. I initially started to check the user input and checked the first component to check if it was a 00, 01, 02 or 03. Where after 00 is called, it checks if the user wants to be X or O. (Default is X -- user goes first) 
3.  In my Read function, i have it reading the user input to see which operation we want to perform. I then moved on with the test driver (ttt-program.c) that prof sebald made for us, and i moved on to working the 02 operation. Which used the user input to select the X and Y coordinate and to which i converted the data and used it to put the cooresponding letter on the baord. Say a X:1 Y:1 would be ****X**** on the board. Making sure the user only inputs the correct numbers and checks if the position is occupied -- which if it is it repeats with an invalid move and asked the player again. If the move is succesful a "OK\n" is delivered to the user. 
4.  Then i moved on to 01 to which the board is returned in order for the driver program to succesfully print. 
5.  The 03 was then implemented with the random computer move (still might implememt the AI if i have time). I have the CPU generate a random number, using get_random_int and taking the mod to get the cooresponding X,Y position. Then have the CPU check if that position is free(check if gameBoard == *), if place occupied have the CPU pick another random int but if it is free, it sets the gameboard to the correct letter. I also checked to make sure the user was not trying to make their turn, keeping track of the turns with a simple global variable. If player is trying to go, sends the OOT\n message. 
6.  If any other option other than 01,02,03,00 is selected it throws an error (UNKCMD\n) and if the input is not an integer, the application closes with the INVFMT\n error. (which is checked first in the read).
7.  Throughout the build, i was implementing locking, if there was a read going on, only the one process could have access to that, and same with the write. 
