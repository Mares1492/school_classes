#include <stdio.h>
void printArray(int numbers[], int size){
    printf("\n[");
    for (int i = 0; i < size; ++i) {
        if (i == size - 1) {
            printf("%d", numbers[i]);
            break;
        }
        printf("%d, ", numbers[i]);

    }
    printf("]");
}
int main(){
    int choice, num, size,length=0,index;
    printf("Enter length of the arr: ");
    scanf("%d", &size);
    int numbers[size];
    for (int i = 0; i < size; ++i) {   // initialize array with 0 as empty value
        numbers[i] = 0;
    }
    do{
        printf("\nChoose action: ");
        printf("\n1. add to start, 2. add to end, 3. Add(index), 4.exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        printf("Enter number: ");
        scanf("%d", &num);
        if (length >= size) {
            // Stack overflow, can't push more values
            printf("Array is full");
            printArray(numbers, size);
            break;
        }
        switch(choice){
            case 1:
                for (int i = size-2;  i > 0 ; --i) {
                    if (numbers[i+1] == 0) {
                        numbers[i+1] = numbers[i];
                        numbers[i] = 0;
                    }
                }
                if (numbers[0] != 0) {
                    printf("Array is full");
                    length = size;
                    break;
                }
                numbers[0] = num;
                length++;
                break;
            case 2:
                for (int i = 1; i < size; ++i) {
                    if (numbers[i-1] == 0) {
                        numbers[i-1] = numbers[i];
                        numbers[i] = 0;
                    }
                }
                if (numbers[size-1] != 0) {
                    printf("Array is full");
                    length = size;
                    break;
                }
                numbers[size-1] = num;
                length++;
                break;
            case 3:
                printf("\nEnter index: ");
                scanf("%d", &index);
                if (index > size || index < 0) {
                    printf("Index is out of range");
                    break;
                }
                if (numbers[index] != 0) {
                    printf("Index is already occupied with a value %d", numbers[index]);
                    break;
                }
                numbers[index] = num;
                break;
            case 4:
                printf("\nExiting...");
                break;
            default:
                printf("\nInvalid choice");
        }
        printArray(numbers, size);
    }while(choice != 4);

}