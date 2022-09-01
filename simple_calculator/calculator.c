#include <stdio.h>
#include <stdlib.h>

#define CHAR_LIMIT 50

float add(int a, int b);
float sub(int a, int b);
float mul(int a, int b);
float divide(int a, int b);
float mod(int a, int b);

int main(int argc, char *argv[]){
    float num1,num2, ans;
    char operator;

    printf("*** Simple Calculator ***\n");
    printf("*** NOTE:Only Supports 2 operands\n");
    printf("EXAMPLE: 2+4\n");
    printf("**********************************\n");


    scanf("%f",&num1);
    scanf("%c",&operator);
    scanf("%f",&num2);

    switch (operator){
        case '+':
            ans = add(num1,num2);
            break;
        case '-':
            ans = sub(num1,num2);
            break;
        case '*':
            ans = mul(num1,num2);
            break;
        case '/':
            ans = divide(num1,num2);
            break;
        case '%':
            ans = mod(num1,num2);
            break;
        default:
            ans = 0;
            break;
    }
    printf("ANSWER: %.2f",ans);


    return 0;
}


float add(int a, int b){
    return a+b;
}
float sub(int a, int b){
    return a-b;
}
float mul(int a, int b){
    return a*b;
}
float divide(int a, int b){
    return a/b;
}

float mod(int a, int b){
    return a%b;
}
