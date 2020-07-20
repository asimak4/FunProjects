#include "chess.h"
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include <linux/random.h>
#include <linux/mutex.h>
#include <linux/ctype.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>

DEFINE_MUTEX(lockingMutex);

static char *chessBoard[8][8];
static char user_input[18] = {'0','0','0','0','0','0','0','0','0','0','0','0','0',
'0','0','0','0','0'};
static int globalBufferLen = 132;
static char globalBuffer[132];
static int gameOn = 0;
char userColor;
char cpuColor = 'W';
int playerTurn = 1;
int isCheckVar = 0;

char* changePiece(char color,char piece){
    if(color == 'W'){
        if(piece == 'P'){
            return "WP";
        }
        if(piece == 'R'){
            return "WR";
        }
        if(piece == 'N'){
            return "WN";
        }
        if(piece == 'B'){
            return "WB";
        }
        if(piece == 'Q'){
            return "WQ";
        }
        if(piece == 'K'){
            return "WK";
        }
    }
    else if(color == 'B'){
        if(piece == 'P'){
            return "BP";
        }
        if(piece == 'R'){
            return "BR";
        }
        if(piece == 'N'){
            return "BN";
        }
        if(piece == 'B'){
            return "BB";
        }
        if(piece == 'Q'){
            return "BQ";
        }
        if(piece == 'K'){
            return "BK";
        }
    }
    return "**";
}

int compChar(char a, char b){
    if(a == b)
        return 1;
    else
        return 0;
}

int isMate(char color){
    int i = 0;
    int j = 0;
    int xKingPosition = 0;
    int yKingPosition = 0;
    char oppositeColor = 'B';
    char *tempBoard[8][8];
    char cpuPiece = 'P';
    unsigned int pickRandPiece = 0;
    unsigned int getRandMoveX = 0;
    unsigned int getRandMoveY = 0;
    unsigned int randPiece = 0;
    int pieceCounter = 0;
    int keepingTrackofMoveX = 0;
    int keepingTrackofMoveY = 0;
    int validMoveVar;
    int checkingVar = 0;
    int makingSureNoLoop = 0;
    int makingNoLoopforMate = 0;
    char *pieceMoving = "**";
    char *pieceBefore = "**";


    if(color == 'B'){
        oppositeColor = 'W';
    }

    // looking where the opposite color King is
    for(i = 0; i < 8;i++){
        for(j = 0; j < 8; j++){
            if(chessBoard[i][j][0] == oppositeColor && chessBoard[i][j][1] == 'K'){
                xKingPosition = i;
                yKingPosition = j;
                i = 10;
                j = 10;
            }            
        }
    }

    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            tempBoard[i][j] = chessBoard[i][j];
        }
    }

    // ----------------------------------------------------
    validMoveVar = validMove(cpuColor,cpuPiece,getRandMoveX,getRandMoveY,keepingTrackofMoveX,keepingTrackofMoveY,chessBoard);
    while(validMoveVar != 1){
        // get a random piece to search for there are PRNBKQ - 6
        pickRandPiece = get_random_int() % 6;
        if(pickRandPiece == 0){
            cpuPiece = 'P';
        }
        else if(pickRandPiece == 1){
            cpuPiece = 'R';
        }
        else if(pickRandPiece == 2){
            cpuPiece = 'N';
        }
        else if(pickRandPiece == 3){
            cpuPiece = 'B';
        }
        else if(pickRandPiece == 4){
            cpuPiece = 'K';
        }
        else if(pickRandPiece == 5){
            cpuPiece = 'Q';
        }

        if(isCheck(userColor,chessBoard) == 1 && makingSureNoLoop < 10){
            cpuPiece = 'K';
        }

        // find a random piece from the selected type (find the 5th pawn or find the first rook)
        for(i = 0; i < 8; i++){
            for(j = 0;j < 8; j++){
                if(chessBoard[i][j][1] == cpuPiece && chessBoard[i][j][0] == cpuColor){
                    pieceCounter++;
                }
            }
        }
        // if there are none of that type look again
        if(pieceCounter == 0){
            continue;
        }
        // pick a random num from 0-that num and pick that specific piece ( fifth pawn)
        randPiece = get_random_int() % pieceCounter;
        pieceCounter = 0;
        for(i = 0; i < 8; i++){
            for(j = 0;j < 8; j++){
                if(chessBoard[i][j][1] == cpuPiece && chessBoard[i][j][0] == cpuColor){
                    if(pieceCounter == randPiece){
                        keepingTrackofMoveX = i;
                        keepingTrackofMoveY = j;
                        // get out of both loops
                        i = 10;
                        j = 10;
                    }
                    pieceCounter++;
                }
            }
        }

        // get a random location to move to anywhere on board then check if valid 
        getRandMoveX = get_random_int() % 8;
        getRandMoveY = get_random_int() % 8;

        pieceMoving = chessBoard[getRandMoveX][getRandMoveY];
        pieceBefore = chessBoard[keepingTrackofMoveX][keepingTrackofMoveY];

        
        // -- tempboard copy
        for(i = 0; i < 8; i++){
            for(j = 0; j < 8; j++){
                tempBoard[i][j] = chessBoard[i][j];
            }
        }
        // applying move to temp Board
        if(strcmp(pieceMoving,"**") == 0){
            tempBoard[getRandMoveX][getRandMoveY] = pieceBefore;
            tempBoard[keepingTrackofMoveX][keepingTrackofMoveY] = pieceMoving;
        }
        else{
            tempBoard[getRandMoveX][getRandMoveY] = pieceBefore;
            tempBoard[keepingTrackofMoveX][keepingTrackofMoveY] = "**";    
        }

        checkingVar = isCheck(userColor, tempBoard);

        if(pieceBefore[1] > cpuPiece || pieceBefore[1] < cpuPiece || checkingVar == 1){
                makingSureNoLoop++;
                makingNoLoopforMate++;
                continue;
        }

        validMoveVar = validMove(cpuColor,cpuPiece,getRandMoveX,getRandMoveY,keepingTrackofMoveX,keepingTrackofMoveY,chessBoard);
        if(makingNoLoopforMate > 2000){
            break;
        }
        
    }
    if(makingNoLoopforMate > 2000){
        return 1;
    }
    else{
        return 0;
    }


    // --------------------------------------------------
    return 1;

}

int isCheck(char color, char *board[8][8]){
    int i;
    int j;
    int xKingPosition = 0;
    int yKingPosition = 0;
    char oppositeColor = 'B';
    char piece;
    char tempColor;

    if(color == 'B'){
        oppositeColor = 'W';
    }
    // looking where the opposite color King is
    for(i = 0; i < 8;i++){
        for(j = 0; j < 8; j++){
            if(board[i][j][0] == oppositeColor && board[i][j][1] == 'K'){
                xKingPosition = i;
                yKingPosition = j;
                i = 10;
                j = 10;
            }            
        }
    }

    // 
    for(i = 0; i < 8;i++){
        for(j = 0; j < 8; j++){
            piece = board[i][j][1];
            tempColor = board[i][j][0];
            if(compChar(piece,'*') == 0 && (tempColor == color)){
                if(validMove(color,piece,xKingPosition,yKingPosition,i,j,board) == 1){
                    isCheckVar = 1;
                    return 1;
                }            
            }
        }
    }
    isCheckVar = 0;
    return 0;
    

}

int validMove(char color, char piece, int movingToX,int movingToY, int startingX, int startingY, char *board[8][8]){
    int i;
    int j;
    int x;
    char pieceMovingToColor = board[movingToX][movingToY][0];

    if(movingToY == startingY && movingToX == startingX){
        return 0;
    }

    if(piece == 'P' && (pieceMovingToColor > color || pieceMovingToColor < color)){
        // checking for move in first spot (can move either one or two forward)
        if((color == 'W' && startingX == 1)){
            if((movingToX == (startingX + 2) && startingY == movingToY) && strcmp(board[movingToX][movingToY],"**") == 0){
                if(strcmp(board[startingX + 1][movingToY],"**") == 0){
                    return 1;
                }                
            }
        }
        if(color == 'W'){
            if((movingToX == (startingX + 1) && startingY == movingToY) && strcmp(board[movingToX][movingToY],"**") == 0){
                return 1;
            }            
            // beating a piece going down and left
            if((movingToX == (startingX + 1) && movingToY == (startingY - 1)) && strcmp(board[movingToX][movingToY],"**") != 0){
                return 1;
            }
            // beating a piece going down and right
            if((movingToX == (startingX + 1) && movingToY == (startingY + 1)) && strcmp(board[movingToX][movingToY],"**") != 0){
                return 1;
            }
        }
        if(color == 'B' && startingX == 6){
            if((movingToX == (startingX - 2) && startingY == movingToY) && strcmp(board[movingToX][movingToY],"**") == 0){
                if(strcmp(board[startingX - 1][movingToY],"**") == 0){
                    return 1;
                } 
            }
        }
        if(color == 'B'){
            if((movingToX == (startingX - 1) && startingY == movingToY) && strcmp(board[movingToX][movingToY],"**") == 0){
                return 1;
            }
            // beating a piece going down and right
            if((movingToX == (startingX - 1) && movingToY == (startingY + 1)) && strcmp(board[movingToX][movingToY],"**") != 0){
                return 1;
            }
            // beating a piece going down and left
            if((movingToX == (startingX - 1) && movingToY == (startingY - 1)) && strcmp(board[movingToX][movingToY],"**") != 0){
                return 1;
            }
        }
    }

    else if(piece == 'R' && (pieceMovingToColor > color || pieceMovingToColor < color)){
        // moving Horizontally 
        if(startingX == movingToX){
            for(i = startingY + 1; i < movingToY; i++){
                if(strcmp(board[startingX][i],"**") != 0){
                    return 0;
                }
            }
            for(i = startingY - 1; i > movingToY; i--){
                if(strcmp(board[startingX][i],"**") != 0){
                    return 0;
                }
            }
            return 1;
        }

        // moving Vertically
        if(startingY == movingToY){
            for(i = startingX + 1; i < movingToX;i++){
                if(strcmp(board[i][startingY],"**") != 0){
                    return 0;
                }
            }
        
            for(i = startingX - 1; i > movingToX; i--){
                if(strcmp(board[i][startingY],"**") != 0){
                    return 0;
                }
            }
            return 1;
        }
    }

    else if(piece == 'N' &&  (pieceMovingToColor > color || pieceMovingToColor < color)){
        if(movingToX == (startingX - 2) && movingToY == (startingY + 1)){
            return 1;
        }
        if(movingToX == (startingX - 1) && movingToY == (startingY + 2)){
            return 1;
        }
        if(movingToX == (startingX + 2) && movingToY == (startingY + 1)){
            return 1;
        }
        if(movingToX == (startingX + 1) && movingToY == (startingY + 2)){
            return 1;
        }
        if(movingToX == (startingX + 2) && movingToY == (startingY - 1)){
            return 1;
        }
        if(movingToX == (startingX + 1) && movingToY == (startingY - 2)){
            return 1;
        }
        if(movingToX == (startingX - 2) && movingToY == (startingY - 1)){
            return 1;
        }
        if(movingToX == (startingX - 1) && movingToY == (startingY - 2)){
            return 1;
        }
        return 0;
        
    }

    else if(piece == 'B' && (compChar(pieceMovingToColor,color) == 0)){
        int absVal = movingToX - startingX;
        if(absVal < 0){
            absVal = (-absVal);
        }
        // moving up to the right diagonal
        if(movingToY > startingY && movingToX < startingX){
            for(i = 1; i <= absVal; i++){
                j = startingY + i;
                x = startingX - i;
                if(j < 8 && x >= 0){
                    if(x == movingToX && j == movingToY){
                        return 1;
                    }
                    if(strcmp(board[x][j],"**") != 0){
                        return 0;
                    }
                }
            }
            return 0;
        }
        if(movingToY < startingY && movingToX < startingX){
            // moving up to the left diagonal
            for(i = 1; i <= absVal; i++){
                j = startingY - i;
                x = startingX - i;
                if(j >= 0 && x >= 0){
                    if(x == movingToX && j == movingToY){
                        return 1;
                    }
                    if(strcmp(board[x][j],"**") != 0){
                        return 0;
                    }
                }
            }
            return 0;
        }
        // moving down to the left diagonal
        if(movingToY < startingY && movingToX > startingX){
            j = startingY - 1;
            for(i = 1; i <= absVal; i++){
                j = startingY - i;
                x = startingX + i;
                if(j >= 0 && x < 8){
                    if(x == movingToX && j == movingToY){
                        return 1;
                    }
                    if(strcmp(board[x][j],"**") != 0){
                        return 0;
                    } 
                }
            }
            return 0;
        }
        if(movingToY > startingY && movingToX > startingX){
            // moving down to the right diagonal
            for(i = 1; i <= absVal; i++){
                j = startingY + i;
                x = startingX + i;
                if(j < 8 && x < 8){
                    if(x == movingToX && j == movingToY){
                        return 1;
                    }
                    if(strcmp(board[x][j],"**") != 0){
                        return 0;
                    }
                }
            }
            return 0;
        }
        return 0;
    }

    else if(piece == 'Q' && compChar(pieceMovingToColor,color) == 0){
        int absVal = movingToX - startingX;
        if(absVal < 0){
            absVal = (-absVal);
        }
        // moving up to the right diagonal
        if(movingToY > startingY && movingToX < startingX){
            for(i = 1; i <= absVal; i++){
                j = startingY + i;
                x = startingX - i;
                if(j < 8 && x >= 0){
                    if(x == movingToX && j == movingToY){
                        return 1;
                    }
                    if(strcmp(board[x][j],"**") != 0){
                        return 0;
                    }
                }
            }
            return 0;
        }
        if(movingToY < startingY && movingToX < startingX){
            // moving up to the left diagonal
            for(i = 1; i <= absVal; i++){
                j = startingY - i;
                x = startingX - i;
                if(j >= 0 && x >= 0){
                    if(x == movingToX && j == movingToY){
                        return 1;
                    }
                    if(strcmp(board[x][j],"**") != 0){
                        return 0;
                    }
                }
            }
            return 0;
        }
        // moving down to the left diagonal
        if(movingToY < startingY && movingToX > startingX){
            j = startingY - 1;
            for(i = 1; i <= absVal; i++){
                j = startingY - i;
                x = startingX + i;
                if(j >= 0 && x < 8){
                    if(x == movingToX && j == movingToY){
                        return 1;
                    }
                    if(strcmp(board[x][j],"**") != 0){
                        return 0;
                    }
                }
            }
            return 0;
        }
        if(movingToY > startingY && movingToX > startingX){
            // moving down to the right diagonal
            for(i = 1; i <= absVal; i++){
                j = startingY + i;
                x = startingX + i;
                if(j < 8 && x < 8){
                    if(x == movingToX && j == movingToY){
                        return 1;
                    }
                    if(strcmp(board[x][j],"**") != 0){
                        return 0;
                    }
                }
            }
            return 0;
        }
         // moving Horizontally 
        if(startingX == movingToX){
            for(i = startingY + 1; i < movingToY; i++){
                if(strcmp(board[startingX][i],"**") != 0){
                    return 0;
                }
            }
            for(i = startingY - 1; i > movingToY; --i){
                if(strcmp(board[startingX][i],"**") != 0){
                    return 0;
                }
            }
            return 1;
        }

        // moving Vertically
        if(startingY == movingToY){
            for(i = startingX + 1; i < movingToX;i++){
                if(strcmp(board[i][startingY],"**") != 0){
                    return 0;
                }
            }
        
            for(i = startingX - 1; i > movingToX; i--){
                if(strcmp(board[i][startingY],"**") != 0){
                    return 0;
                }
            }
            return 1;
        }
    }
    else if(piece == 'K' && (pieceMovingToColor > color || pieceMovingToColor < color)){
        //DOWN
        if(movingToX == startingX + 1 && movingToY == startingY){
            return 1;
        }
        //UP
        else if(movingToX == startingX - 1 && movingToY == startingY){
            return 1;
        }
        //RIGHT
        else if(movingToX == startingX && movingToY == startingY + 1){
            return 1;
        }
        //LEFT
        else if(movingToX == startingX && movingToY == startingY - 1){
            return 1;
        }
        // Right Down
        else if(movingToX == startingX + 1 && movingToY == startingY + 1){
            return 1;
        }
        // Left Down
        else if(movingToX == startingX + 1 && movingToY == startingY - 1){
            return 1;
        }
        // Right Up
        else if(movingToX == startingX - 1 && movingToY == startingY + 1){
            return 1;
        }
        // Left Up
        else if(movingToX == startingX - 1 && movingToY == startingY - 1){
            return 1;
        }

        else{
            return 0;
        }    
    }
    return 0;
}

int convertLetterToNum(char letter){
    if(letter == 'a')
        return 0;
    else if(letter == 'b')
        return 1;
    else if(letter == 'c')
        return 2;
    else if(letter == 'd')
        return 3;
    else if(letter == 'e')
        return 4;
    else if(letter == 'f')
        return 5;
    else if(letter == 'g')
        return 6;
    else if(letter == 'h')
        return 7;
    else if(letter == '1')
        return 0;
    else if(letter == '2')
        return 1;
    else if(letter == '3')
        return 2;
    else if(letter == '4')
        return 3;
    else if(letter == '5')
        return 4;
    else if(letter == '6')
        return 5;
    else if(letter == '7')
        return 6;
    else if(letter == '8')
        return 7;
    return -1;
}


int chess_open(struct inode *pinode, struct file *pfile){
    LOG_INFO("In function %s\n", __FUNCTION__);
    return 0;
}
ssize_t chess_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
    int rv = 0;
    int checkUserCopy = 0;
    int i = 0;
    mutex_lock(&lockingMutex);
    LOG_INFO("In function %s\n", __FUNCTION__);
    if(globalBufferLen){
        checkUserCopy = copy_to_user(buffer, globalBuffer, globalBufferLen);
        rv = globalBufferLen;
        globalBufferLen = 0;
    }

    for(i = 0; i < 18; i++){
        user_input[i] = '0';
    }

    mutex_unlock(&lockingMutex);
    return rv;
}

ssize_t chess_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset){
    int i = 0;
    int j = 0;

    char *pieceMoving = "**";
    char *pieceBefore = "**";

    static char menu_choice[2];
    mutex_lock(&lockingMutex);
    LOG_INFO("In function %s\n", __FUNCTION__);
    // acquiring user input using get_user
    for(i = 0; i < length; i++){
        get_user(user_input[i],buffer++);
    }

    // setting the menu_choice to the first two inputs from the user (which should be 00,01..etc)
    for(i = 0; i < 2; i++){
        menu_choice[i] = user_input[i];
    }

    // ------------------ 00 ----------------------------------------------------------
    if(strcmp(menu_choice,"00") == 0){
        globalBufferLen = 0;
        gameOn = 1;

        for (i = 5; i < 18; i++)
        {
            if(compChar(user_input[i],'0') == 0){
                memcpy(globalBuffer,"INVFMT\n",7);
                globalBufferLen = 7;
                mutex_unlock(&lockingMutex);
                return length;
            }
        }

        // initialize game with "**" in empty spots
        for (i = 0; i < 8; i++){
            for (j = 0; j < 8; j++){
                chessBoard[i][j] = "**";
            }
        }

        // ------------- White Pieces -----------------
        // pawns
        for(i = 0; i < 8; i++){
            chessBoard[1][i] = "WP"; 
        }
        // rooks
        chessBoard[0][7] = "WR";
        chessBoard[0][0] = "WR";
        // knights
        chessBoard[0][6] = "WN";
        chessBoard[0][1] = "WN";
        // bishops
        chessBoard[0][5] = "WB";
        chessBoard[0][2] = "WB";
        // Queen
        chessBoard[0][4] = "WK";
        // King
        chessBoard[0][3] = "WQ";
        // ------------- Black Pieces ----------------
        for(i = 0; i < 8; i++){
            chessBoard[6][i] = "BP"; 
        }
        
        // rooks
        chessBoard[7][7] = "BR";
        chessBoard[7][0] = "BR";
        // knights
        chessBoard[7][6] = "BN";
        chessBoard[7][1] = "BN";
        // bishops
        chessBoard[7][5] = "BB";
        chessBoard[7][2] = "BB";
        // King
        chessBoard[7][4] = "BK";
        // Queen
        chessBoard[7][3] = "BQ";
        // Reading whether the player chooses B or W

        userColor = user_input[3];

        if(userColor == 'W'){
            cpuColor = 'B';
            playerTurn = 0;
        }
        else{
            playerTurn = 1;
            cpuColor = 'W';
        }

        memcpy(globalBuffer,"OK\n",3);
        globalBufferLen = 3;
        mutex_unlock(&lockingMutex);
        return length;
    }

    else if(strcmp(menu_choice,"01") == 0){
        globalBufferLen = 0;       
        for (i = 3; i < 18; i++)
        {
            if(compChar(user_input[i],'0') == 0){
                memcpy(globalBuffer,"INVFMT\n",7);
                globalBufferLen = 7;
                mutex_unlock(&lockingMutex);
                return length;
            }
        }

        // making sure gameBoard is already set up
        if(gameOn != 1){
            memcpy(globalBuffer,"NOGAME\n",7);
            globalBufferLen = 7;
            mutex_unlock(&lockingMutex);
            return length;
        }

        for(i = 0; i < 8; i++){
            for(j = 0; j < 8; j++){   
                globalBuffer[globalBufferLen] = chessBoard[i][j][0];
                globalBufferLen++;
                globalBuffer[globalBufferLen] = chessBoard[i][j][1];
                globalBufferLen++;
            }
        }
        globalBuffer[globalBufferLen] = '\n';
        globalBufferLen++;
        mutex_unlock(&lockingMutex);
        return length;
    }
    // checking validation of input
    else if(strcmp(menu_choice,"02") == 0 && (compChar(user_input[2],' ') == 0)){
        memcpy(globalBuffer,"INVFMT\n",7);
        globalBufferLen = 7;
        mutex_unlock(&lockingMutex);
        return length; 

    }
    else if(strcmp(menu_choice,"02") == 0 && 
    (user_input[3] == '0' || user_input[4] == '0' || user_input[5] == '0' || user_input[6] == '0'
    || user_input[7] == '0' || user_input[8] == '0' || user_input[9] == '0')){

        memcpy(globalBuffer,"INVFMT\n",7);
        globalBufferLen = 7;
        mutex_unlock(&lockingMutex);
        return length; 

    }
    else if(strcmp(menu_choice,"02") == 0){
        
        int boardLocationXOriginal;
        int boardLocationYOriginal;

        int boardLocationXToMove;
        int boardlocationYToMove;

        char CpuPieceToBeat[3];
        char changingPawn[3];
        char *pieceChange;

        char userPiece[3] = {'0'};
        char userOriginalPosition[3] = {'0'};
        char userMovingTo[3] = {'0'};
        globalBufferLen = 0;

        userOriginalPosition[2] = '\0';
        userMovingTo[2] = '\0';
        userPiece[2] = '\0';

        // making sure gameBoard is already set up
        if(gameOn != 1){
            memcpy(globalBuffer,"NOGAME\n",7);
            globalBufferLen = 7;
            mutex_unlock(&lockingMutex);
            return length;
        }
        
        // ------ checking to make sure correct turn
        if(playerTurn % 2 != 0){
            memcpy(globalBuffer,"OOT\n",4);
            globalBufferLen = 4;
            mutex_unlock(&lockingMutex);
            return length;
        }
        
        // ---- checking to make sure user selected their correct color
        if(compChar(userColor,user_input[3]) == 0){
            memcpy(globalBuffer,"ILLMOVE\n",8);
            globalBufferLen = 8;
            mutex_unlock(&lockingMutex);
            return length;
        }

        // Converting the move ex: E2 to [1,4]
        boardLocationXOriginal = convertLetterToNum(user_input[6]);
        boardLocationYOriginal = convertLetterToNum(user_input[5]);
        

        // grabbing what the user has at that position ex [1,4] == WP
        userOriginalPosition[0] = chessBoard[boardLocationXOriginal][boardLocationYOriginal][0];
        userOriginalPosition[1] = chessBoard[boardLocationXOriginal][boardLocationYOriginal][1];
        
        // grabbing the userPiece ex: WP
        userPiece[0] = user_input[3];
        userPiece[1] = user_input[4];

        // making sure the user is selecting the correct piece to move in the correct position 
        if(strcmp(userPiece,userOriginalPosition) != 0){
            memcpy(globalBuffer,"ILLMOVE\n",8);
            globalBufferLen = 8;
            mutex_unlock(&lockingMutex);
            return length;
        }

        // Getting the users moving position ,ex: e4 == [3,4]
        boardLocationXToMove = convertLetterToNum(user_input[9]);
        boardlocationYToMove = convertLetterToNum(user_input[8]);

        // we can check that the position is free or full ex: e4 == "**" or full
        userMovingTo[0] = chessBoard[boardLocationXToMove][boardlocationYToMove][0];
        userMovingTo[1] = chessBoard[boardLocationXToMove][boardlocationYToMove][1];

        // moving piece to same spot
        if(strcmp(chessBoard[boardLocationXToMove][boardlocationYToMove],chessBoard[boardLocationXOriginal][boardLocationYOriginal]) == 0){
            memcpy(globalBuffer,"ILLMOVE\n",8);
            globalBufferLen = 8;
            mutex_unlock(&lockingMutex);
            return length;
        }

        CpuPieceToBeat[0] = user_input[11];
        CpuPieceToBeat[1] = user_input[12];
        CpuPieceToBeat[2] = '\0';

        // checking to make sure the player is moving to an empty spot if they are not beating anyone
        if(validMove(userColor,userPiece[1],boardLocationXToMove,boardlocationYToMove,boardLocationXOriginal,boardLocationYOriginal,chessBoard) == 1){
            pieceMoving = chessBoard[boardLocationXOriginal][boardLocationYOriginal];
            pieceBefore = chessBoard[boardLocationXToMove][boardlocationYToMove];
            // moving without beating a piece (pawn)
            if(user_input[10] == 'y' && user_input[11] == userColor && user_input[4] == 'P' &&
            (user_input[12] == 'R' || user_input[12] == 'N' || user_input[12] == 'B' ||
            user_input[12] == 'Q' || user_input[12] == 'K') && 
            ((boardLocationXToMove == 7) || (boardLocationXToMove == 0)) &&
            strcmp(chessBoard[boardLocationXToMove][boardLocationYOriginal],"**") == 0){

                pieceChange = changePiece(userColor,user_input[12]);

                chessBoard[boardLocationXOriginal][boardLocationYOriginal] = "**";
                chessBoard[boardLocationXToMove][boardlocationYToMove] = pieceChange;

            }
            // beating a piece to move
            else if(user_input[10] == 'x' && strcmp(CpuPieceToBeat,pieceBefore) == 0 && 
             user_input[13] == 'y' && user_input[14] == userColor && 
            (user_input[15] == 'R' || user_input[15] == 'N' || user_input[15] == 'B' ||
            user_input[15] == 'Q' || user_input[15] == 'K') && 
            ((boardLocationXToMove == 7) || (boardLocationXToMove == 0)) && user_input[4] == 'P' &&
            strcmp(chessBoard[boardLocationXToMove][boardLocationYOriginal],"**") != 0){
            
                changingPawn[0] = userColor;
                changingPawn[1] = user_input[15];
                changingPawn[2] = '\0';

                pieceChange = changePiece(userColor,changingPawn[1]);
                chessBoard[boardLocationXOriginal][boardLocationYOriginal] = "**";
                chessBoard[boardLocationXToMove][boardlocationYToMove] = pieceChange;
            }
            else if(strcmp(pieceBefore,"**") == 0 && compChar(user_input[10],'x') == 0){
                if((user_input[4] == 'P') && (boardLocationXToMove == 7 || boardLocationXToMove == 0)){
                    memcpy(globalBuffer,"ILLMOVE\n",8);
                    globalBufferLen = 8;
                    mutex_unlock(&lockingMutex);
                    return length;
                }
                chessBoard[boardLocationXOriginal][boardLocationYOriginal] = pieceBefore;
                chessBoard[boardLocationXToMove][boardlocationYToMove] = pieceMoving;
            }
            else if(user_input[10] == 'x' && strcmp(CpuPieceToBeat,pieceBefore) == 0 && (compChar(user_input[13],'y') == 0)){ 
                if((user_input[4] == 'P') && (boardLocationXToMove == 7 || boardLocationXToMove == 0)){
                    memcpy(globalBuffer,"ILLMOVE\n",8);
                    globalBufferLen = 8;
                    mutex_unlock(&lockingMutex);
                    return length;
                }
                chessBoard[boardLocationXOriginal][boardLocationYOriginal] = "**";
                chessBoard[boardLocationXToMove][boardlocationYToMove] = pieceMoving;
            }

            else{
                memcpy(globalBuffer,"ILLMOVE\n",8);
                globalBufferLen = 8;
                mutex_unlock(&lockingMutex);
                return length;
            }
            // checking if the user is in check it will be illegal
            if(isCheck(cpuColor,chessBoard) == 1){
                chessBoard[boardLocationXOriginal][boardLocationYOriginal] = pieceMoving;
                chessBoard[boardLocationXToMove][boardlocationYToMove] = pieceBefore;

                memcpy(globalBuffer,"ILLMOVE\n",8);
                globalBufferLen = 8;
                mutex_unlock(&lockingMutex);
                return length;
            }
            
            playerTurn++;
            if(isCheck(userColor,chessBoard) == 1){
                if(isMate(userColor) == 1){
                    memcpy(globalBuffer,"MATE\n",5);
                    globalBufferLen = 5;
                    gameOn = 0;
                    mutex_unlock(&lockingMutex);
                    return length;
                }
                memcpy(globalBuffer,"CHECK\n",6);
                globalBufferLen = 6;
                mutex_unlock(&lockingMutex);
                return length;
                
            }
            else{
                memcpy(globalBuffer,"OK\n",3);
                globalBufferLen = 3;
                mutex_unlock(&lockingMutex);
                return length;
            }
        }

        else{
            memcpy(globalBuffer,"ILLMOVE\n",8);
            globalBufferLen = 8;
            mutex_unlock(&lockingMutex);
            return length;
        }
    mutex_unlock(&lockingMutex);
    return length;
    }
    else if(strcmp(menu_choice,"03") == 0){

        char cpuPiece = 'P';
        unsigned int pickRandPiece = 0;
        unsigned int getRandMoveX = 0;
        unsigned int getRandMoveY = 0;
        unsigned int randPiece = 0;
        int pieceCounter = 0;
        int i;
        int j;
        char *tempBoard[8][8];
        int keepingTrackofMoveX = 0;
        int keepingTrackofMoveY = 0;
        int validMoveVar;
        int checkingVar = 0;
        int makingSureNoLoop = 0;
        char *switchPawn = "**";

        for (i = 3; i < 18; i++)
        {
            if(compChar(user_input[i],'0') == 0){
                memcpy(globalBuffer,"INVFMT\n",7);
                globalBufferLen = 7;
                mutex_unlock(&lockingMutex);
                return length;
            }
        }

        // making sure gameBoard is already set up
        if(gameOn != 1){
            memcpy(globalBuffer,"NOGAME\n",7);
            globalBufferLen = 7;
            mutex_unlock(&lockingMutex);
            return length;
        }
        
        // ------ checking to make sure correct turn
        if(playerTurn % 2 == 0){
            memcpy(globalBuffer,"OOT\n",4);
            globalBufferLen = 4;
            mutex_unlock(&lockingMutex);
            return length;
        }

        validMoveVar = validMove(cpuColor,cpuPiece,getRandMoveX,getRandMoveY,keepingTrackofMoveX,keepingTrackofMoveY,chessBoard);
        while(validMoveVar != 1){
            // get a random piece to search for there are PRNBKQ - 6
            pickRandPiece = get_random_int() % 6;
            if(pickRandPiece == 0){
                cpuPiece = 'P';
            }
            else if(pickRandPiece == 1){
                cpuPiece = 'R';
            }
            else if(pickRandPiece == 2){
                cpuPiece = 'N';
            }
            else if(pickRandPiece == 3){
                cpuPiece = 'B';
            }
            else if(pickRandPiece == 4){
                cpuPiece = 'K';
            }
            else if(pickRandPiece == 5){
                cpuPiece = 'Q';
            }

            if(isCheck(userColor,chessBoard) == 1 && makingSureNoLoop < 10){
                cpuPiece = 'K';
            }

            // find a random piece from the selected type (find the 5th pawn or find the first rook)
            for(i = 0; i < 8; i++){
                for(j = 0;j < 8; j++){
                    if(chessBoard[i][j][1] == cpuPiece && chessBoard[i][j][0] == cpuColor){
                        pieceCounter++;
                    }
                }
            }
            // if there are none of that type look again
            if(pieceCounter == 0){
                continue;
            }
            // pick a random num from 0-that num and pick that specific piece ( fifth pawn)
            randPiece = get_random_int() % pieceCounter;
            pieceCounter = 0;
            for(i = 0; i < 8; i++){
                for(j = 0;j < 8; j++){
                    if(chessBoard[i][j][1] == cpuPiece && chessBoard[i][j][0] == cpuColor){
                        if(pieceCounter == randPiece){
                            keepingTrackofMoveX = i;
                            keepingTrackofMoveY = j;
                            // get out of both loops
                            i = 10;
                            j = 10;
                        }
                        pieceCounter++;
                    }
                }
            }

            // get a random location to move to anywhere on board then check if valid 
            getRandMoveX = get_random_int() % 8;
            getRandMoveY = get_random_int() % 8;

            pieceMoving = chessBoard[getRandMoveX][getRandMoveY];
            pieceBefore = chessBoard[keepingTrackofMoveX][keepingTrackofMoveY];

            // -- tempboard copy
            for(i = 0; i < 8; i++){
                for(j = 0; j < 8; j++){
                    tempBoard[i][j] = chessBoard[i][j];
                }
            }
            // applying move to temp Board
            if(strcmp(pieceMoving,"**") == 0){
                tempBoard[getRandMoveX][getRandMoveY] = pieceBefore;
                tempBoard[keepingTrackofMoveX][keepingTrackofMoveY] = pieceMoving;
            }
            else{
                tempBoard[getRandMoveX][getRandMoveY] = pieceBefore;
                tempBoard[keepingTrackofMoveX][keepingTrackofMoveY] = "**";    
            }

            checkingVar = isCheck(userColor, tempBoard);

            if(pieceBefore[1] > cpuPiece || pieceBefore[1] < cpuPiece || checkingVar == 1){
                    makingSureNoLoop++;
                    continue;
            }

            validMoveVar = validMove(cpuColor,cpuPiece,getRandMoveX,getRandMoveY,keepingTrackofMoveX,keepingTrackofMoveY,chessBoard);
        }
        // finishing the goto
        
        makingSureNoLoop = 0;
        if(strcmp(pieceMoving,"**") == 0){
            chessBoard[getRandMoveX][getRandMoveY] = pieceBefore;
            chessBoard[keepingTrackofMoveX][keepingTrackofMoveY] = pieceMoving;
        }
        else if(pieceBefore[1] == 'P' && (getRandMoveX == 7 || getRandMoveX == 0)){
            // random piece for pawn to change to
            pickRandPiece = get_random_int() % 6;
            if(pickRandPiece == 0){
                cpuPiece = 'P';
            }
            else if(pickRandPiece == 1){
                cpuPiece = 'R';
            }
            else if(pickRandPiece == 2){
                cpuPiece = 'N';
            }
            else if(pickRandPiece == 3){
                cpuPiece = 'B';
            }
            else if(pickRandPiece == 4){
                cpuPiece = 'K';
            }
            else if(pickRandPiece == 5){
                cpuPiece = 'Q';
            }

            switchPawn = changePiece(cpuColor,cpuPiece);

            chessBoard[getRandMoveX][getRandMoveY] = switchPawn;
            chessBoard[keepingTrackofMoveX][keepingTrackofMoveY] = "**"; 
        }
        
        else{
            chessBoard[getRandMoveX][getRandMoveY] = pieceBefore;
            chessBoard[keepingTrackofMoveX][keepingTrackofMoveY] = "**";    
        }

        playerTurn++;
        if(isCheck(cpuColor,chessBoard) == 1){
                if(isMate(cpuColor) == 1){
                    memcpy(globalBuffer,"MATE\n",5);
                    globalBufferLen = 5;
                    gameOn = 0;
                    mutex_unlock(&lockingMutex);
                    return length;
                }
                memcpy(globalBuffer,"CHECK\n",6);
                globalBufferLen = 6;
                mutex_unlock(&lockingMutex);
                return length;
                
            }
        else{
                memcpy(globalBuffer,"OK\n",3);
                globalBufferLen = 3;
                mutex_unlock(&lockingMutex);
                return length;
            }           
        
    }
    else if(strcmp(menu_choice,"04") == 0){
        if(gameOn != 1){
            memcpy(globalBuffer,"NOGAME\n",7);
            globalBufferLen = 7;
            return length;
        }


        if(playerTurn % 2 != 0){
            memcpy(globalBuffer,"OOT\n",4);
            globalBufferLen = 4;
            return length;
        }        

        for (i = 3; i < 18; i++)
        {
            if(compChar(user_input[i],'0') == 0){
                memcpy(globalBuffer,"INVFMT\n",7);
                globalBufferLen = 7;
                return length;
            }
        }

        memcpy(globalBuffer,"OK\n",3);
        gameOn = 0;
        globalBufferLen = 3;
        return length;
        

    }
    else if((strcmp(menu_choice,"04") != 0) && (strcmp(menu_choice,"03") != 0) 
    && (strcmp(menu_choice,"02") != 0) && (strcmp(menu_choice,"01") != 0) 
    && (strcmp(menu_choice,"01") != 0)){

        memcpy(globalBuffer,"UNKCMD\n",7);
        globalBufferLen = 7;
        return length;

    }
    else{
        memcpy(globalBuffer,"INVFMT\n",7);
        globalBufferLen = 7;
        return length; 
    }

    return length;
}

int chess_release(struct inode *pinode, struct file *pfile){
    LOG_INFO("In function %s\n", __FUNCTION__);
    return 0;
}
