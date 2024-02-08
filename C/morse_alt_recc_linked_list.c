#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node{
    char value;
    struct node *dot;
    struct node *dash;
};

char* alphabet = " EISHVUFUARLAWPJTNDBXKCYMGZQOO";
int i = 0;


struct node* generateList(int nodesToGenerate){
    if(nodesToGenerate == 0){
        return NULL;
    }
    struct node *node = malloc(sizeof(struct node));
    int newNodesToGenerateLeft = nodesToGenerate/2;
    int newNodesToGenerateRight = nodesToGenerate - newNodesToGenerateLeft-1;
    node->value = alphabet[i];
    i++;
    node->dot = generateList(newNodesToGenerateLeft);
    node->dash = generateList(newNodesToGenerateRight);
    return node;
}

struct node* nextNode(struct node* current, struct node* head, char symbol){
    if(symbol == '.') {
        return current->dot;
    }
    if(symbol == '-'){
        return current->dash;
    }
    if(symbol == '/') {
        printf("%c",current->value);
        return head;
    }
    printf("\n\nError: %c{unknown symbol}\n\n", symbol);
    return NULL;
}

int main(){
    struct node *head = NULL;
    char symbol;
    FILE *fp;
    fp = fopen("D:/C/files_to_read/morse1.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        perror("Error");
        return 1;
    }

    head = generateList(strlen(alphabet));
    struct node* current = head;
    printf("\n\n-------------START-------------\n");
    while (fscanf(fp, "%c", &symbol) != EOF) {
        if(symbol == '\n'){
            printf("\n");
            continue;
        }
        current = nextNode(current, head ,symbol);
        if(current == NULL){
            break;
        }
    }
    printf("\n-------------END-------------\n");
    return 1;
}

