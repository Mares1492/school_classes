#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char* hello_world() {
    char* str = malloc(13 * sizeof(char)); // allocate memory for the string
    strcpy(str, "Hello, world");           // copy the string into the allocated memory
    return str;                            // return the string
}

int main() {
    char* str = hello_world();
    printf("%s\n", str);
    free(str);                             // free the memory allocated for the string
    return 0;
}