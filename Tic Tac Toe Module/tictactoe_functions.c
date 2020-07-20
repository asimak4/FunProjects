#include "tictactoe.h"
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/random.h>
#include <linux/mutex.h>
#include <linux/ctype.h>


static char *input_pointer;
char userLetter = 'X';
static char otherLetter = 'O';
static char gameBoard[10] = {0};
static int whoseTurn = 0;

static char user_input[9];
static int gameON = 0;
static char globalBuff[80];

static int bufferLen = 80;

static char ok[] = {'O','K','\n'};
static char tie[] = {'T','I','E','\n'};
static char win[] = {'W','I','N','\n'};
static char oot[] = {'O','O','T','\n'};
static char noGame[] = {'N','O','G','A','M','E','\n'};
static char fmt[] = {'I','N','V','F','M','T','\n'};
static char illMove[] = {'I','L','L','M','O','V','E','\n'};
static char unk[] = {'U','N','K','C','M','D','\n'};


DEFINE_MUTEX(lockingMutex);

int checkWinStates(char playerLetter){
    int win = 1;
    int nothing = 0;

    // -----------------------------------------------------------------------------------------------
    if(gameBoard[0] == playerLetter && gameBoard[1] == playerLetter && gameBoard[2] == playerLetter){
        return win;
    }
    // -----------------------------------------------------------------------------------------------
    else if(gameBoard[0] == playerLetter && gameBoard[3] == playerLetter && gameBoard[6] == playerLetter){
        return win;
    }
    // -----------------------------------------------------------------------------------------------
    else if(gameBoard[1] == playerLetter && gameBoard[4] == playerLetter && gameBoard[7] == playerLetter){
        return win;
    }
    // -----------------------------------------------------------------------------------------------
    else if(gameBoard[3] == playerLetter && gameBoard[4] == playerLetter && gameBoard[5] == playerLetter){
        return win;
    }
    // -----------------------------------------------------------------------------------------------
    else if(gameBoard[6] == playerLetter && gameBoard[7] == playerLetter && gameBoard[8] == playerLetter){
        return win;
    }
    // -----------------------------------------------------------------------------------------------
    else if(gameBoard[2] == playerLetter && gameBoard[5] == playerLetter && gameBoard[8] == playerLetter){
        return win;
    }
    // -----------------------------------------------------------------------------------------------
    else if(gameBoard[0] == playerLetter && gameBoard[4] == playerLetter && gameBoard[8] == playerLetter){
        return win;
    }
    else if(gameBoard[2] == playerLetter && gameBoard[4] == playerLetter && gameBoard[6] == playerLetter){
        return win;
    }
    return nothing;
}
int pieceInBoard(char letter, char x, char y){

        if((x == '0' && y == '0') && gameBoard[0] == '*'){
            gameBoard[0] = letter;
            return 1;
        }
        else if((x == '1' && y == '0') && gameBoard[1] == '*' ){
            gameBoard[1] = letter;
            return 1;
        }
        else if((x == '2' && y == '0') && gameBoard[2] == '*' ){
            gameBoard[2] = letter;
            return 1;
        }
        else if((x == '0' && y == '1') && gameBoard[3] == '*'){
            gameBoard[3] = letter;
            return 1;
        }
        else if((x == '1' && y == '1') && gameBoard[4] == '*'){
            gameBoard[4] = letter;
            return 1;
        }
        else if((x == '2' && y == '1') && gameBoard[5] == '*'){
            gameBoard[5] = letter;
            return 1;
        }
        else if((x == '0' && y == '2') && gameBoard[6] == '*'){
            gameBoard[6] = letter;
            return 1;
        }
        else if((x == '1' && y == '2') && gameBoard[7] == '*'){
            gameBoard[7] = letter;
            return 1;
        }
        else if((x == '2' && y == '2') && gameBoard[8] == '*'){
            gameBoard[8] = letter;
            return 1;
        }
    
    return 0;
        

}

int tictactoe_open(struct inode *pinode, struct file *pfile){
    LOG_INFO("In function %s\n", __FUNCTION__);
    return 0;
}
ssize_t tictactoe_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
    int rv = 0;
    int i = 0;
    if(bufferLen){
        for(i = 0; i < bufferLen; i++){
            put_user(globalBuff[i],buffer++);    
        }
        rv = bufferLen;
        bufferLen = 0;
    }
    
    mutex_unlock(&lockingMutex);
    return rv;
}

ssize_t tictactoe_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset){
    int i = 0;
    int j = 0;
    static char menu_choice[2];
    LOG_INFO("In function %s\n", __FUNCTION__);
    mutex_lock(&lockingMutex);
    while(i < 9 && i < length){
        get_user(user_input[i],buffer+i);
        i++;
    }
    input_pointer = user_input;
    LOG_INFO("USERINPUT: %s\n",user_input);
    
    // --------------------------------------------------------------------------------
    
    while(j < 2){
        menu_choice[j] = user_input[j];
        j++;
    }
    // ---------------------------------- NOT CORRECT FORMAT -----------------------------------------------------
     if(!isdigit(menu_choice[0]) || !isdigit(menu_choice[1]) || menu_choice == NULL){
        bufferLen = 0;
        for(i = 0; i < 7; i++){
            globalBuff[i] = fmt[i];
            bufferLen++;
        }
        mutex_unlock(&lockingMutex);
        return length;   
    }

    // ---------------------------------- 00 ------------------------------------------------------------------------
    if(strcmp(menu_choice,"00") == 0){
        bufferLen = 0;
        gameBoard[9] = '\n';
        gameON = 1;
        for (i = 0; i < 9; i++){
            gameBoard[i] = '*';
        }
        for(i = 0; i < 3; i++){
            globalBuff[i] = ok[i];
            bufferLen++;
        }
        if(user_input[3] == 'O'){
            userLetter = 'O';
            otherLetter = 'X';
        }
        
        mutex_unlock(&lockingMutex);
        return length;
    }

    // ---------------------------------- 01 ------------------------------------------------------------------------
    else if(strcmp(menu_choice,"01") == 0){
        LOG_INFO("Returning the board from 01\n");
        bufferLen = 0;
        for(i = 0; i <= 9; i++){
            globalBuff[i] = gameBoard[i];
            bufferLen++;
        }
        LOG_INFO("Board: %s\n", gameBoard);
        mutex_unlock(&lockingMutex);
        return length;
    }
    // ---------------------------------- 02 ------------------------------------------------------------------------
    else if(strcmp(menu_choice,"02") == 0){
        int placePiece;
        int j = 0;
        int spaceLeft = 1;

        LOG_INFO("Inside menu choice 02\n");

        LOG_INFO("User X move: %c\n", user_input[3]);
        LOG_INFO("User Y move: %c\n", user_input[5]);

        whoseTurn = 1;
        
        // checking if the game is being played
        if(!gameON){
                bufferLen = 0;
                for(i = 0; i < 7; i++){
                    globalBuff[i] = noGame[i];
                    bufferLen++;
                }
            
            mutex_unlock(&lockingMutex);
            return length;
        }
        
        placePiece = pieceInBoard(userLetter,user_input[3],user_input[5]);
        
        if(placePiece == 1){
            // place holder
            
        }
        else{
            bufferLen = 0;
            for(i = 0; i < 8; i++){
                globalBuff[i] = illMove[i];
                bufferLen++;
            }
            mutex_unlock(&lockingMutex);
            return length;
        }
        
        // ----- Looking for the Win -----
        if(checkWinStates(userLetter) == 1){
            bufferLen = 0;
            for(i = 0; i < 4; i++){
                globalBuff[i] = win[i];
                bufferLen++;
            }
            mutex_unlock(&lockingMutex);
            return length;
        }
        
        // ----- Looking for the Tie -----
        for(j = 0; j < 9; j++){
            if(gameBoard[j] == '*'){
                spaceLeft = 0;
            }
        }
        if(spaceLeft == 1){
            bufferLen = 0;
            for(i = 0; i < 4; i++){
                globalBuff[i] = tie[i];
                bufferLen++;
            }
            mutex_unlock(&lockingMutex);
            return length;
        }

        LOG_INFO("GameBoard: %s\n", gameBoard);
        bufferLen = 0;
        for(i = 0; i < 3; i++){
            globalBuff[i] = ok[i];
            bufferLen++;
        }
        
        mutex_unlock(&lockingMutex);
        return length;
    }
    // ---------------------------------- 03 ------------------------------------------------------------------------
    else if(strcmp(menu_choice,"03") == 0){
        int j = 0;         
        static int validMove = 0;
        static int spaceLeft = 0;

        whoseTurn = 2;
        if(whoseTurn == 1){
            int rv = 0;
            for(i = 0; i < 4; i++){
                globalBuff[i] = oot[i];
                rv++;
            }
            bufferLen = rv;
            mutex_unlock(&lockingMutex);
            return length; 
        }

        // checking if the game is being played
        if(!gameON){
           bufferLen = 0;
            for(i = 0; i < 7; i++){
                globalBuff[i] = noGame[i];
                bufferLen++;
            }
            mutex_unlock(&lockingMutex);
            return length;
        }


        LOG_INFO("Inside of menu choice 03\n");

        // have the CPU generate a random number
        // have the CPU check if that position is free ( check if gameBoard == *)
        // if place occupied have the CPU pick another random int
        // set the gameboard equal to that location

        for(j = 0; j < 9; j++){
            if(gameBoard[j] == '*'){
                spaceLeft = 0;
            }
        }

        while(validMove != 1 && spaceLeft == 0){
            unsigned int getRandX = get_random_int() % 3;
            unsigned int getRandY = get_random_int() % 3;
            unsigned int placePiece = 0;
            char getX = '0';
            char getY = '0';
            spaceLeft = 1;

            for(j = 0; j < 9; j++){
                if(gameBoard[j] == '*'){
                    spaceLeft = 0;
                }
            }

            if(getRandX == 1){
                getX = '1';
            }
            if(getRandX == 2){
                getX = '2';
            }

            if(getRandY == 1){
                getY = '1';
            }
            if(getRandY == 2){
                getY = '2';
            }
            placePiece = pieceInBoard(otherLetter,getX,getY);

            if(placePiece == 1){
                validMove = 1;
            }
        }
        validMove = 0;


        // ---- Looking for the Tie
        for(j = 0; j < 9; j++){
            if(gameBoard[j] == '*'){
                spaceLeft = 0;
            }
        }
        if(spaceLeft == 1){
            bufferLen = 0;
            for(i = 0; i < 4; i++){
                globalBuff[i] = tie[i];
                bufferLen++;
            }
            
            mutex_unlock(&lockingMutex);
            return length;
        }
        // ----- Looking for the Win
        if(checkWinStates(otherLetter) == 1){
            bufferLen = 0;
            for(i = 0; i < 4; i++){
                globalBuff[i] = win[i];
                bufferLen++;
            }
            mutex_unlock(&lockingMutex);
            return length;
        }

        // ----- Sending the ok
        bufferLen = 0;
        for(i = 0; i < 3; i++){
           globalBuff[i] = ok[i];
           bufferLen++;
        }
        mutex_unlock(&lockingMutex);
        return length;
    }
    // ---------------------------------- UNKCMD ------------------------------------------------------------------------
    else{
        bufferLen = 0;
        for(i = 0; i < 7; i++){
            globalBuff[i] = unk[i];
            bufferLen++;
        }
        mutex_unlock(&lockingMutex);
        return length;
    }

    // ----------------------------------------------------------------------------------
    mutex_unlock(&lockingMutex);
    return length;
}

int tictactoe_release(struct inode *pinode, struct file *pfile){
    LOG_INFO("In function %s\n", __FUNCTION__);
    return 0;
}
