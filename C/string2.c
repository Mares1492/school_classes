#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int length(const char *str){
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

void push(char *str, char c){
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    str[i] = c;
    str[i+1] = '\0';
}

char* calcString(char *str) {
    int isInBrackets = 0;
    int inner = 0;
    int num = 0;
    int outputSize = 10;
    // allocate memory for the strings
    char* inBracketsArr = calloc(outputSize, sizeof(char));
    char* output = calloc(outputSize ,sizeof(char));
    for (int i = 0; i < length(str); ++i) {
        if(length(output)+1 > outputSize || length(inBracketsArr)+1 > outputSize){
            outputSize *= 2;
            output = realloc(output, outputSize * sizeof(char));
            inBracketsArr = realloc(inBracketsArr, outputSize * sizeof(char));
            if(output == NULL) {
                printf("Error (re)allocating memory");
                exit(1);
            }
        }
        if (str[i] >= '0' && str[i] <= '9') {
            if(isInBrackets == 1){
                push(inBracketsArr, str[i]);
                continue;
            }
            num = num * 10 + (str[i] - '0');
            continue;
        }
        if (str[i] == '[') {
            inner++;
            if (isInBrackets == 1) {
                push(inBracketsArr, str[i]);
                continue;
            }
            isInBrackets = 1;
            continue;
        }
        if (str[i] == ']') {
            inner--;
            if (isInBrackets == 1) {
                if (inner == 0) {
                    isInBrackets = 0;
                    for (int j = 0; j < num; ++j) {
                        strcat(output, calcString(inBracketsArr));
                    }
                    memset(inBracketsArr, '\0', outputSize);
                    continue;
                }
                push(inBracketsArr, str[i]);
                continue;
            }
        }
        if (isInBrackets == 0) {
            push(output, str[i]);
            continue;
        }
        push(inBracketsArr, str[i]);
    }
    free(inBracketsArr);
    free(str);
    return output;
}

int main(){
    char* str = calcString("3[a2[b]2[t]]2[b2[cd]]g");
    printf("\n\n%s is gotten\n", str);
    printf("abbttabbttabbttbcdcdbcdcdg is expected\n");
    if(strcmp(str, "abbttabbttabbttbcdcdbcdcdg") == 0){
        printf("Test passed");
    } else {
        printf("Test failed");
    }

    free(str);  // free the memory allocated for the string
    return 0;
}

