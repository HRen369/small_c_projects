#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define ROW 8
#define COL 13
#define EMPTY ' '
#define LEN 100

#define STAND_ENDS COL-3

void initalizeHangman();
void printHangMan();
void createStand(int standEnds);
void createHangman(int locations,int headStart);


void createHead(int location, int headStart);
void createUpperBody(int location, int headStart);
void createLeftArm(int location, int headStart);
void createRightArm(int location, int headStart);
void createLowerBody(int location, int headStart);
void createLeftLeg(int location, int headStart);
void createRightLeg(int location, int headStart);


void createWordFinding(char *word,char *wordFinding);
void printWordFinding(char *wordFinding);

char printPrompt();
void currentStep(int count);
void considerLetter();
int checkLetter(char letter, char *word,char *wordFinding);
int isWordComplete(char *wordFinding);
int isLetterFound(char letter, char *word,char *wordFinding);

char *hangman;
char *word;
char *wordFinding;

int main(int argc, int *argv[]){
    int count;
    char letter;
    int standEnds = COL-3;

    word = malloc(sizeof(char)*LEN);
    wordFinding = malloc(sizeof(char)*LEN);
    hangman = malloc(sizeof(char)*ROW*COL);

    word = "aabb";
    createWordFinding(word,wordFinding);

    printf("****************\n");
    printf("*** Hangman ****\n");
    printf("****************\n");

    initalizeHangman();
    createStand(standEnds);    
    
    considerLetter(word,wordFinding);

    free(word);
    free(wordFinding);
    free(hangman);

    return 0;
}

//Inital Board Methods
void initalizeHangman(){
    int i,j;

    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            *(hangman+(i*COL)+j) = ' ';
        }
    }


}
void printHangMan(){
    int i,j;

    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            printf("%c ",*(hangman+(i*COL)+j));
        }
        printf("\n");
    } 
}
void createStand(int standEnds){
    int i,j;

    for(i=3;i<standEnds;i++){
        *(hangman+(i)) = '-';
    }

    for(i=1;i<ROW-1;i++){
        *(hangman+(i*COL)+3) = '|';
    }

    for(i=1;i<standEnds;i++){
        *(hangman+((ROW-1)*COL)+i) = '-';
    }
    *(hangman+(COL)+standEnds-1) = '-';

}

// Hangman Methods
void createHangman(int location, int headStart){
    createUpperBody(2,headStart);
    createLowerBody(2,headStart);
    createLeftArm(2,headStart);
    createRightArm(2,headStart);
    createLeftLeg(2,headStart);
    createRightLeg(2,headStart);
}
void createHead(int location, int headStart){
    *(hangman+(COL*location)+headStart) = 'O';
}
void createUpperBody(int location, int headStart){
    *(hangman+(COL*(location+1))+headStart) = '|';
}
void createLeftArm(int location, int headStart){
    *(hangman+(COL*(location+1))+headStart-1) = '/';
}
void createRightArm(int location, int headStart){
    *(hangman+(COL*(location+1))+headStart+1) = '\\';
}
void createLowerBody(int location, int headStart){
    *(hangman+(COL*(location+2))+headStart) = '|';
}
void createLeftLeg(int location, int headStart){
    *(hangman+(COL*(location+3))+headStart-1) = '/';

}
void createRightLeg(int location, int headStart){
    *(hangman+(COL*(location+3))+headStart+1) = '\\';
}

//Methods to deal with words
void printWordFinding(char *wordFinding){
    int i;
    for(i=0;wordFinding[i] !='\0';i++){
        printf("%c ", *(wordFinding+i));
    }
    printf("\n");
}
void createWordFinding(char *word, char *wordFinding){
    int i;
    for(i=0;word[i] !='\0';i++){
        wordFinding[i] = '_';
    }
    wordFinding[i] = '\0';
}

int checkLetter(char letter, char *word,char *wordFinding){
    int i = 0;

    while(word[i] != '\0'){
        if(word[i] == letter){
            return TRUE;
        }
        i++;
    }
    return FALSE;

}
int isWordComplete(char *wordFinding){
    int i = 0;

    while(wordFinding[i] != '\0'){
        if(wordFinding[i] == '_'){
            return FALSE;
        }
        i++;
    }
    return TRUE;
}
int isLetterFound(char letter, char *word,char *wordFinding){
    int i;
    for(i=0;word[i] != '\0';i++){
        if(word[i] == letter){
            wordFinding[i] = letter;
        }

    }
}

char printPrompt(){
    char letter;

    printf("****************\n");
    printHangMan();
    printf("****************\n");
    printf("Guess the word? \n");    
    printWordFinding(wordFinding);
    printf("\n****************\n");
    letter = getchar();
    getchar();
    return letter;
}

void currentStep(int count){
    int standEnds = COL-4;
    int location = 2;
    switch (count){
        case 0:
            createHead(location,standEnds);
            break;
        case 1:
            createUpperBody(location,standEnds);
            break;
        case 2:
            createLowerBody(location,standEnds);
            break;
        case 3:
            createLeftArm(location,standEnds);
            break;
        case 4:
            createRightArm(location,standEnds);
            break;
        case 5:
            createLeftLeg(location,standEnds);
            break;
        case 6:
            createRightLeg(location,standEnds);
            break;   
        default:
            break;
        }
    }

void considerLetter(char *word,char *wordFinding){
    int i,count;
    char letter;
    int *alphabet = malloc(sizeof(char)*26);
    for(i=0;i<26;i++){
        *(alphabet+i) = FALSE;
    }
    
    count = 0;

    while(count < 7 && !isWordComplete(wordFinding)){

        letter = printPrompt();
        int isLetterValid = checkLetter(letter,word,wordFinding);
        int alphaLocation = tolower(letter)-97;
        //printf("%d",alphaLocation);
        
        if(alphabet[alphaLocation] == FALSE && !isLetterValid){
            currentStep(count++);
        }
        else if(alphabet[alphaLocation] == FALSE && isLetterValid){
            isLetterFound(letter,word,wordFinding);
        }
        else{
            printf("****************\n");
            printf("Already used %c\n",alphaLocation+97);
        }
        alphabet[alphaLocation] = TRUE;
    }

    free(alphabet);

    if(count >=7){
        printf("****************\n");
        printHangMan();
        printf("****************\n");
        printf("You Lost! The word was %s",word);
    }
    else{
        printf("****************\n");
        printWordFinding(wordFinding);
        printf("****************\n");
        printf("You Won! The word is %s",word);
    }

}

