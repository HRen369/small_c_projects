/*
Rock,Paper,Scissors Game 
by Humberto Rendon
9/1/2022

R,p,s game over the console.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define WON 1
#define EQUAL 0
#define LOSS -1

#define ROCK '1'
#define PAPER '2'
#define SCISSORS '3'

char randomChoice();

char result(char userChoice, char aiChoice);
void displayAiChoice(char aiChoice);
void displayUserChoice(char userChoice);


int comparePaper(char otherPlayer);
int compareScissors(char otherPlayer);
int compareRock(char otherPlayer);


int main(){
    char userPick, aiPick, answer;

    printf("*** Rock Paper Scissors Game ***\n");
    printf("Pick one of the following choices\n");
    printf("[ 1 ] Rock\n");
    printf("[ 2 ] Paper\n");
    printf("[ 3 ] Scissors\n");
    printf("----------------------\n");

    userPick = getchar();
    aiPick = randomChoice();
    printf("----------------------\n");

    displayUserChoice(userPick);
    displayAiChoice(aiPick);
    printf("----------------------\n");

    answer = result(userPick,aiPick);
    if(answer == WON){
        printf("Player Won\n");
    }
    else if(answer == LOSS){
        printf("Player Lost\n");
    }
    else{
        printf("Player and Computer Tied\n");
    }
}

char randomChoice(){
    time_t t;
    srand((unsigned) time(&t)); //Always use this once. Using it multple times causes them to get the same number

    return (rand() % 3)+49;
}

char result(char userChoice, char aiChoice){
    char answer;
    switch (userChoice){
        case PAPER:
            answer = comparePaper(aiChoice);
            break;
        case SCISSORS:
            answer = compareScissors(aiChoice);
            break;
        case ROCK:
            answer = compareRock(aiChoice);
            break;
        default:
            answer = ' ';
            break;
    }
    return answer;
}

void displayUserChoice(char userChoice){
    switch (userChoice){
        case PAPER:
            printf("You picked Paper!\n");
            break;
        case SCISSORS:
            printf("You picked Scissors!\n");
            break;
        case ROCK:
            printf("You picked Rock!\n");
            break;
        default:
            printf("You picked Nothing!\n");
            break;
    }
    
}

void displayAiChoice(char aiChoice){

    switch (aiChoice){
        case PAPER:
            printf("AI picked Paper!\n");
            break;
        case SCISSORS:
            printf("AI picked Scissors!\n");
            break;
        case ROCK:
            printf("AI picked Rock!\n");
            break;
        default:
            printf("AI picked Nothing!\n");
            break;
    }
}

int comparePaper(char otherPlayer){
    if(otherPlayer == SCISSORS ){
        return LOSS;
    }
    else if(otherPlayer == ROCK){
        return WON;
    }
    return EQUAL;
}


int compareScissors(char otherPlayer){
    if(otherPlayer == ROCK ){
        return LOSS;
    }
    else if(otherPlayer == PAPER){
        return WON;
    }
    return EQUAL;
}


int compareRock(char otherPlayer){
    if(otherPlayer == PAPER ){
        return LOSS;
    }
    else if(otherPlayer == SCISSORS){
        return WON;
    }
    return EQUAL;
}