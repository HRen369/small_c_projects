#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 15
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
int createSnakeBodyRow(int row, int directionStart, int prevColLength);
int createSnakeColumnRow(int row,int directionStart, int bodyLength);

char *board;
time_t t;

int main(int argc, char *argv[]){
    srand((unsigned) time(&t)); //Always use this once. Using it multple times causes them to get the same number

    board = (char*)malloc(LENGTH*LENGTH);
    intializeBoard();

    int i,turn,prevBodyLength, prevColLength;
    turn = prevBodyLength = prevColLength= i = 0;
    while(i < LENGTH){
        if(turn == 0){
            prevBodyLength = createSnakeBodyRow(i,LEFT,prevBodyLength);
            i++;
        }
        else if(turn == 1){
            prevColLength = createSnakeColumnRow(i,LEFT,prevBodyLength);
            i += prevColLength;
        }
        else if(turn == 2){
            prevBodyLength += createSnakeBodyRow(i,RIGHT,prevBodyLength);
            i++;
        }
        else{
            prevColLength = createSnakeColumnRow(i,RIGHT,prevBodyLength);
            i += prevColLength;
            turn = -1;
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

int createSnakeBodyRow(int row,int directionStart, int prevBodyLength){
    int i;
    int bodyLength = (rand() % (LENGTH-prevBodyLength))+1;

    if(directionStart ==LEFT){
        for(i=0;i<bodyLength;i++){
            board[(row*LENGTH)+i] = SNAKE_BODY;
        }    
    }
    else{
        int limit = prevBodyLength + bodyLength;
        for(i=prevBodyLength-1;i< limit;i++){
            board[(row*(LENGTH))+i] = SNAKE_BODY;
        }        
        
        /*
        for(i=LENGTH-bodyLength;i<LENGTH;i++){
            board[(row*(LENGTH))+i] = SNAKE_BODY;
        }*/
    }
    printf("%d ", bodyLength);
    return bodyLength;
}


int createSnakeColumnRow(int row,int directionStart, int bodyLength){
    int colLength = (rand() % 2)+1;

    int i;
    for(i = 0;i<colLength;i++){
        board[((row+i)*LENGTH)+bodyLength-1] = SNAKE_BODY;
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