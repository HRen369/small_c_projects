/*
Tic-Tac Toe
by Humberto Rendon
9/1/2022

A simple tic-tac-toe game made with C. Allows you to go against a person or an AI.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define LENGTH 3

#define PLAYER1 'X'
#define PLAYER2 'O'
#define EMPTY '-'

//Basic Methods
void initalizeBoard();
void printBoard();
int placeMark(int row, int col, char marker);

//Menus
void humanVsHuman();
void humanVsAi();

// Check for Wins, Loses or Ties
int isBoardFilled();
int checkWin(char currentMark, char otherMark);
int checkHorizontal(char playerMark, char otherMark);
int checkVertical(char playerMark, char otherMark);
int checkDiagonal(char playerMark, char otherMark);

void pickValidTile(char currentMark);

// AI Methods
void pickValidOption(char currentMark, char otherMark);
int blockBestOption(char currentMark, char otherMark);
int checkRandomOption(char currentMark);
int blockHumanVertical(char currentMark, char otherMark);
int blockHumanHorizontal(char currentMark, char otherMark);
int blockHumanDiagonal(char currentMark, char otherMark);

int winBestOption(char currentMark);
int winAiVertical(char currentMark);
int winAiHorizontal(char currentMark);
int winAiDiagonal(char currentMark);

char *board;

int main(){
    int choice, row, col;
    board = (char*)malloc(LENGTH*LENGTH*sizeof(char));

    choice = row = col = -1;

    initalizeBoard();
    printBoard();

    printf("*** Tic-Tac Toe Game ***\n");
    printf("[1] Vs Human\n");
    printf("[2] Vs AI\n");

    while((choice = getchar()-48) < 0 || choice > LENGTH){
        getchar(); // discard newline;
        printf("*** %d is not a digit ***\n",choice);
    }
    getchar(); // discard newline;

    switch(choice){
        case 1:
            humanVsHuman();
            break;
        case 2:
            humanVsAi();
            break;

    }

    free(board);

}

void initalizeBoard(){
    int i,j;
    for( i= 0; i < LENGTH; i++){
        for(j = 0; j < LENGTH; j++){
            board[(i*LENGTH)+j] = EMPTY;
        }
    }
}

void printBoard(){
    printf("*** Board ***\n");
    int i,j;
    for(i=0; i < LENGTH; i++){
        for(j=0; j < LENGTH; j++){
            printf("%c ",board[(i*LENGTH)+j]);
        }
        printf("\n");
    }

}

int placeMark(int row, int col, char marker){
    board[(row*LENGTH) + col] = marker;
    return TRUE;
}

int isBoardFilled(){
    int filledTiles = 0;
    int i,j;
    for(i=0; i < LENGTH; i++){
        for(j=0; j < LENGTH; j++){
            if(board[(i*LENGTH)+j] != EMPTY){
                filledTiles++;
            }
        }
    }
    return filledTiles == (LENGTH*LENGTH);
}

int checkWin(char playerMark, char otherMark){
    return checkHorizontal(playerMark,otherMark) || 
            checkVertical(playerMark,otherMark) || 
            checkDiagonal( playerMark, otherMark);
}

int checkHorizontal(char playerMark, char otherMark){
    int i,j,n;
    for(i=0; i < LENGTH; i++){
        n = 0;
        for(j=0; j < LENGTH; j++){
            if(board[(i*LENGTH) +j] == otherMark || board[(i*LENGTH)+j] == EMPTY ){        
                break;
            }
            n++;
        }

        if(n == LENGTH){
            return TRUE;
        }
    }
    return FALSE;
}

int checkVertical(char playerMark, char otherMark){
    int i, j,n;
   for(i=0; i < LENGTH; i++){
        n = 0;
        for(j=0; j < LENGTH; j++){
            if(board[(j*LENGTH) + i] == otherMark || board[(j*LENGTH)+i] == EMPTY ){        
                break;
            }
            n++;
        }        
        if(n == LENGTH){
            return TRUE;
        }
    }
    return FALSE;
}

int checkDiagonal(char playerMark, char otherMark){
    int i, j,n;
    j = LENGTH;
    
    n = 0;
    for(i=0; i < LENGTH; i++){
        if(board[(i*LENGTH)+i] == otherMark || board[(i*LENGTH)+i] == EMPTY ){        
            break;
        }
        n++;
            
        if(n == LENGTH){
            return TRUE;
        }
    }

    n = 0;
    for(i=0; i < LENGTH; i++){
        j--;
        if(board[(i*LENGTH)+j] == otherMark || board[(i*LENGTH)+j] == EMPTY ){        
            break;
        }
        n++;       
        
        if(n == LENGTH){
            return TRUE;
        }
    }

    return FALSE;
}
void humanVsHuman(){
    printf("*** Human VS Human ***\n");
    printBoard();
    printf("\n");

    int filled = FALSE;
    int over = FALSE;
    int turn = 0;

    while(!(filled = isBoardFilled()) && !over){
        int picked = FALSE;
        char currentMark;
        char otherMark;

        if(turn%2 == 0){
            printf("*** Player1's turn ***\n");
            currentMark = PLAYER1;
            otherMark = PLAYER2;
        }
        else{
            printf("*** Player2's turn ***\n");
            currentMark = PLAYER2;
            otherMark = PLAYER1;
        }

        pickValidTile(currentMark);
        turn++;
        over = checkWin(currentMark,otherMark);
        printBoard();

    }

    if(filled && !over){
        printf("*** Player1 and Player 2 Tie ***\n");
    }
    else if(over){
        turn--;
        if(turn%2 == 0){
            printf("*** Player1 Won ***\n");
        }
        else{
            printf("*** Player2 Won ***\n");
        }
    }

}

void pickValidTile(char currentMark){
        int picked = FALSE;
        while(!picked){
            //Place a mark ---- TURN INTO A FUNCTION
            int row, col;
            row = col = 0;
            printf("Pick a row from 1 to %d\n", LENGTH);

            while((row = getchar()-48) <= 0 || row > LENGTH){
                getchar(); // discard newline;
                printf("*** %d is not a valid row ***\n",row);
            }
            getchar(); // discard newline;

            printf("Pick a column from 1 to %d\n", LENGTH);
            
            while((col = getchar()-48) <= 0 || col > LENGTH){
                getchar(); // discard newline;
                printf("*** %c is not a valid column ***\n",row);
            }
            getchar(); // discard newline;

            if(board[(row-1)*LENGTH + (col-1)] == EMPTY){
                placeMark(row-1,col-1,currentMark);
                picked = TRUE;
            } 
            else{
                printf("Invalid Choice!\n");
            }       

        }
}


void humanVsAi(){
    printf("*** Human VS AI ***\n");
    printBoard();
    printf("\n");

    int filled = FALSE;
    int over = FALSE;
    int turn = 0;

    while(!(filled = isBoardFilled()) && !over){
        int picked = FALSE;
        char currentMark;
        char otherMark;

        if(turn%2 == 0){
            printf("*** Player1's turn ***\n");
            currentMark = PLAYER1;
            otherMark = PLAYER2;
            pickValidTile(currentMark);

        }
        else{
            printf("*** Computer's turn ***\n");
            currentMark = PLAYER2;
            otherMark = PLAYER1;
            pickValidOption(currentMark,otherMark);
        }
        turn++;
        over = checkWin(currentMark,otherMark);
        printBoard();
    }

    if(filled && !over){
        printf("*** Player1 and Computer Tie ***\n");
    }
    else if(over){
        turn--;
        if(turn%2 == 0){
            printf("*** Player Won ***\n");
        }
        else{
            printf("*** Computer Won ***\n");
        }
    }

}

void pickValidOption(char currentMark, char otherMark){
    if(!winBestOption(currentMark) && !blockBestOption(currentMark,otherMark)){
        checkRandomOption(currentMark);
    }
}

int blockBestOption(char currentMark, char otherMark){
    //It would be to find the random best option
    time_t t;
    srand((unsigned) time(&t));

    int choice = (rand() % 3);

    if(choice == 1){
        if(!blockHumanHorizontal(currentMark,otherMark)){
            choice = (rand() % 2);

            if(choice == 1){
                if(!blockHumanVertical(currentMark,otherMark)){
                    return blockHumanDiagonal(currentMark,otherMark);
                }
            }
            else{
                if(!blockHumanDiagonal(currentMark,otherMark)){
                    return blockHumanVertical(currentMark,otherMark);
                }
            }

        }

    }
    else if(choice == 2){
        if(!blockHumanVertical(currentMark,otherMark)){
            choice = (rand() % 2);

            if(choice == 1){
                if(!blockHumanHorizontal(currentMark,otherMark)){
                    return blockHumanDiagonal(currentMark,otherMark);
                }
            }
            else{
                if(!blockHumanDiagonal(currentMark,otherMark)){
                    return blockHumanHorizontal(currentMark,otherMark);
                }
            }

        }
    }
    else{
        if(!blockHumanDiagonal(currentMark,otherMark)){
            choice = (rand() % 2);

            if(choice == 1){
                if(!blockHumanHorizontal(currentMark,otherMark)){
                    return blockHumanVertical(currentMark,otherMark);
                }
            }
            else{
                if(!blockHumanVertical(currentMark,otherMark)){
                    return blockHumanHorizontal(currentMark,otherMark);
                }
            }

        }
    }
}

int blockHumanVertical(char currentMark, char otherMark){
    int i,j,opponentMarks,empty,bestRow,bestCol;
    bestRow = bestCol = opponentMarks= empty = -1;

    for(i = 0; i < LENGTH;i++){
        opponentMarks = 0;
        empty = 0;
        for(j=0;j< LENGTH;j++){
            if(board[(j*LENGTH)+i] == EMPTY){
                empty++;
                bestRow = j;
            }
            else if(board[(j*LENGTH)+i] == otherMark){
                opponentMarks++;
            }
        }

        if(opponentMarks==2 && empty == 1){
            bestCol = i;
            placeMark(bestRow,bestCol,currentMark);
            return TRUE;
        }
    }
    return FALSE;
}
int blockHumanHorizontal(char currentMark, char otherMark){
    int i,j,opponentMarks,empty,bestRow,bestCol;
    bestRow = bestCol = opponentMarks= empty = -1;

    for(i = 0; i < LENGTH;i++){
        opponentMarks = 0;
        empty = 0;
        for(j=0;j< LENGTH;j++){
            if(board[(i*LENGTH)+j] == EMPTY){
                empty++;
                bestCol = j;
            }
            else if(board[(i*LENGTH)+j] == otherMark){
                opponentMarks++;
            }
        }

        if(opponentMarks==2 && empty == 1){
            bestRow = i;
            placeMark(bestRow,bestCol,currentMark);
            return TRUE;
        }
    }
    return FALSE;
}
int blockHumanDiagonal(char currentMark, char otherMark){
    int i,j,opponentMarks,empty,bestRow,bestCol;
    bestRow = bestCol = opponentMarks= empty = -1;
    
    j = LENGTH;
    
    opponentMarks = 0;
    empty = 0;
    for(i=0; i < LENGTH; i++){
        if(board[(i*LENGTH)+i] == EMPTY ){        
            empty++;
            bestRow = i;
            bestCol = bestRow;
        }
        else if(board[(i*LENGTH)+i] == otherMark){
            opponentMarks++;
        }
            
         if(opponentMarks==2 && empty == 1){
            placeMark(bestRow,bestCol,currentMark);
            return TRUE;
        }
    }

    opponentMarks = 0;
    empty = 0;
    for(i=0; i < LENGTH; i++){
        j--;

        if(board[(i*LENGTH)+j] == EMPTY ){        
            empty++;
            bestRow = i;
            bestCol = j;
        }
        else if(board[(i*LENGTH)+j] == otherMark){
            opponentMarks++;
        }
            
         if(opponentMarks==2 && empty == 1){
            placeMark(bestRow,bestCol,currentMark);
            return TRUE;
        }

    }
   

    return FALSE;
}

int winBestOption(char currentMark){
    //It would be to find the random best option
    time_t t;
    srand((unsigned) time(&t));

    int choice = (rand() % 3);
    int isGood;

    if(choice == 1){
        if(!winAiHorizontal(currentMark)){
            choice = (rand() % 2);

            if(choice == 1){
                if(!winAiVertical(currentMark)){
                    return winAiDiagonal(currentMark);
                }
            }
            else{
                if(!winAiDiagonal(currentMark)){
                    return winAiVertical(currentMark);
                }
            }

        }

    }
    else if(choice == 2){
        if(!winAiVertical(currentMark)){
            choice = (rand() % 2);

            if(choice == 1){
                if(!winAiHorizontal(currentMark)){
                    return winAiDiagonal(currentMark);
                }
            }
            else{
                if(!winAiDiagonal(currentMark)){
                    return winAiHorizontal(currentMark);
                }
            }

        }
    }
    else{
        if(!winAiDiagonal(currentMark)){
            choice = (rand() % 2);

            if(choice == 1){
                if(!winAiHorizontal(currentMark)){
                    return winAiVertical(currentMark);
                }
            }
            else{
                if(!winAiVertical(currentMark)){
                    return winAiHorizontal(currentMark);
                }
            }

        }
    }
}
int winAiVertical(char currentMark){
    int i,j,marks,empty,bestRow,bestCol;
    bestRow = bestCol = marks= empty = -1;

    for(i = 0; i < LENGTH;i++){
        marks = 0;
        empty = 0;
        for(j=0;j< LENGTH;j++){
            if(board[(j*LENGTH)+i] == EMPTY){
                empty++;
                bestRow = j;
            }
            else if(board[(j*LENGTH)+i] == currentMark){
                marks++;
            }
        }

        if(marks==2 && empty == 1){
            bestCol = i;
            placeMark(bestRow,bestCol,currentMark);
            return TRUE;
        }
    }
    return FALSE;
}
int winAiHorizontal(char currentMark){
    int i,j,marks,empty,bestRow,bestCol;
    bestRow = bestCol = marks= empty = -1;

    for(i = 0; i < LENGTH;i++){
        marks = 0;
        empty = 0;
        for(j=0;j< LENGTH;j++){
            if(board[(i*LENGTH)+j] == EMPTY){
                empty++;
                bestCol = j;
            }
            else if(board[(i*LENGTH)+j] == currentMark){
                marks++;
            }
        }

        if(marks==2 && empty == 1){
            bestRow = i;
            placeMark(bestRow,bestCol,currentMark);
            return TRUE;
        }
    }
    return FALSE;
}
int winAiDiagonal(char currentMark){
    int i,j,marks,empty,bestRow,bestCol;
    bestRow = bestCol = marks= empty = -1;
    
    j = LENGTH;
    
    marks = 0;
    empty = 0;
    for(i=0; i < LENGTH; i++){
        if(board[(i*LENGTH)+i] == EMPTY ){        
            empty++;
            bestRow = i;
            bestCol = bestRow;
        }
        else if(board[(i*LENGTH)+i] == currentMark){
            marks++;
        }
    
        if(marks==2 && empty == 1){
            placeMark(bestRow,bestCol,currentMark);
            return TRUE;
        }
    }

    marks = 0;
    empty = 0;
    for(i=0; i < LENGTH; i++){
        j--;

        if(board[(i*LENGTH)+j] == EMPTY ){        
            empty++;
            bestRow = i;
            bestCol = j;
        }
        else if(board[(i*LENGTH)+j] == currentMark){
            marks++;
        }
            
         if(marks==2 && empty == 1){
            placeMark(bestRow,bestCol,currentMark);
            return TRUE;
        }

    }
   

    return FALSE;
}

int checkRandomOption(char currentMark){
    time_t t;

    srand((unsigned) time(&t));
    
    int row, col;
    row = col = -1;

    while((row == -1 && col == -1) || board[(row*LENGTH)+col] != EMPTY){
        row = (rand() % 3);
        col = (rand() % 3);
    }
    return placeMark(row,col,currentMark);

}