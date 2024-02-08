#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void printArray(int numbers[], int size){
    printf("\n[");
    for (int i = 0; i < size; ++i) {
        if (i == size - 1) {
            printf("%d", numbers[i]);
            break;
        }
        printf("%d, ", numbers[i]);

    }
    printf("]\n");
}

void something(char* str){
    char chars[] = "52";
    char* chars2 = "52";
    int* stack = calloc(strlen(str), sizeof(int));
    int i = 0;
    while(str[i] != '\0') {
        printArray(stack, strlen(str));
        printf("i: %d, heap: %c,\n", i, str[i]);
        switch (str[i]) {
            case '+':
                stack[i] = stack[i-2] + stack[i-1];
                break;
            case '-':
                stack[i] = stack[i-2] - stack[i-1];
                break;
            case '*':
                stack[i] = stack[i-2] * stack[i-1];
                break;
            case '/':
                stack[i] = stack[i-2] / stack[i-1];
                break;
            default:
                stack[i] = str[i] - '0';
        }
        i++;
    }
}

int main(){
    something("53*132-++");
    return 0;
}