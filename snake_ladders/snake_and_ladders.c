/*
Snake and Ladders 
by Humberto Rendon
9/5/2022

Currently only creates a snake wih the given length
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 10
#define LEFT 4
#define RIGHT 6


#define PLAYER 'P'
#define SNAKE_TAIL 'T'
#define SNAKE_BODY '-'
#define SNAKE_HEAD 'H'

#define SNAKE 's'
#define LADDER 'L'

void intializeBoard();
void printBoard();

int createSnakeColumnRow(int row, int bodyLength);
int createSnakeBodyLeftToRight(int row, int start);
int createSnakeBodyRightToLeft(int row, int start);

char *board;
time_t t;

int main(int argc, char *argv[]){
    srand((unsigned) time(&t)); //Always use this once. Using it multple times causes them to get the same number

    board = (char*)malloc(LENGTH*LENGTH);
    intializeBoard();

    int i,turn,prevLastCell, prevColLength;
    turn = prevLastCell = prevColLength= i = 0;
    while(i < LENGTH){
        switch (turn){
        case 0:
            prevLastCell = createSnakeBodyLeftToRight(i,prevLastCell);
            i++;
            break;
        case 1:
            prevColLength = createSnakeColumnRow(i,prevLastCell);
            i += prevColLength;
            break;        
        case 2:
            prevLastCell = createSnakeBodyRightToLeft(i,prevLastCell);
            i++;
            break;  
        case 3:
            prevColLength = createSnakeColumnRow(i,prevLastCell);
            i += prevColLength;
            turn = -1;
            break;       
        default:
            printf("ERROR!!!");
            break;
        }
        turn++;
    }

    printf("\n");
    printBoard();


    free(board);
}

void intializeBoard(){
    int i,j;
    for(i=0;i<LENGTH;i++){
        for(j=0;j<LENGTH;j++){
            board[(i*LENGTH) +j] = 177;
        }
    }
}

int createSnakeBodyLeftToRight(int row, int start){
    int i,rowLength,end;
    i = rowLength = end = 0;

    rowLength = (rand() % LENGTH)+1;

    end = start+rowLength;
    
    if(end > LENGTH){
        end = start+(LENGTH-start);
    }

    for(i=start;i<end;i++){
        *(board + (row*LENGTH)+i) = SNAKE_BODY; 
    }

    return i-1;
}

int createSnakeBodyRightToLeft(int row, int start){
    int i,rowLength,end;
    i = rowLength = end = 0;
    rowLength = (rand() % LENGTH)+1;

    end = start-rowLength;
    printf("start: %d, end: %d, rowLength: %d",start,end,rowLength);

    if(end < -1){
        end = -1;
    }

    for(i=start;i>end;i--){
        *(board + (row*LENGTH)+i) = SNAKE_BODY; 
    }

    return i+1;
}

int createSnakeColumnRow(int row, int start){
    int i,colLength;

    if(row == LENGTH-2){
        colLength = 1;
    }
    else{
        colLength = (rand() % 2)+1;
    }

    for(i=0;i<colLength;i++){
        *(board + (row+i)*LENGTH+start) = SNAKE_BODY; 
    }

    return colLength;
}

void printBoard(){
    int i,j;

    for(i=0;i<LENGTH;i++){
        for(j=0;j<LENGTH;j++){
            printf("%c",board[(i*LENGTH)+j]);
        }
        printf("\n");
    }
}