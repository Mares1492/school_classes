#include "stdio.h"
#define MAX_SIZE 6

void printArray(float numbers[], int size){
    printf("\n[");
    for (int i = 0; i < size; ++i) {
        if (i == size - 1) {
            printf("%f", numbers[i]);
            break;
        }
        printf("%f, ", numbers[i]);

    }
    printf("]\n");
}

int main(){
    float num, array[MAX_SIZE];
    int elements = 0,tipIndex;
    for (int i = 0; i < MAX_SIZE; ++i) {   // initialize array with 0 as empty value
        array[i] = 0;
    }
    printArray(array, MAX_SIZE);
    for (int i = 0; i < MAX_SIZE; ++i) {
        printf("\nEnter number: ");
        scanf("%f", &num);
        tipIndex = elements;
        while(1){
            if(tipIndex<0){
                printf("\n\nError\n\n");
                return 0;
            }
            if(array[tipIndex-1]>num){
                array[tipIndex] = array[tipIndex-1];
                array[tipIndex-1] = 0;
                --tipIndex;
                printf("\ntipIndex:%d\n",tipIndex);
            }
            if(tipIndex==0){
                array[tipIndex] = num;
                elements++;
                break;
            }
            if(array[tipIndex-1]<num || array[tipIndex-1] == num){
                array[tipIndex] = num;
                elements++;
                break;
            }
        }
        printf("\n\n%d\n\n",elements);
        printArray(array, MAX_SIZE);
    }
    return 1;
}