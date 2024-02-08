#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct animal {
    char* name;
    char* question;
    int height;
    struct animal* yes;
    struct animal* no;
};

struct animalDictionary {
    char* question;
    char* animal;
};

//interface for the tree
struct animalDictionary animalDictionary[] = {
        {"Big?", NULL},
        {"Fluffy?","Elephant"},
        {NULL,"Bear"},
        {NULL,},
        {NULL,"Mouse"},

};
int i = 0;

struct animal* generateTree(int nodesToGenerate){
    if (nodesToGenerate == 0) return NULL;
    struct animal *animal = malloc(sizeof(struct animal));
    int newNodesToGenerateForYes = nodesToGenerate / 2;
    int newNodesToGenerateForNo = nodesToGenerate - newNodesToGenerateForYes - 1;
    animal->name = animalDictionary[i].animal;
    animal->question = animalDictionary[i].question;
    i++;
    animal->yes = generateTree(newNodesToGenerateForYes);
    animal->no = generateTree(newNodesToGenerateForNo);
    animal->yes->height = animal->height + 1;
    animal->no->height = animal->height + 1;
    return animal;
}

char getAnswer(char* question){
    printf("%s (y/n): ", question);
    char answer;
    do{
        answer = (char)getchar();
    } while (answer != 'y' && answer != 'n');
    return answer;
}


int main() {
    char answer;
    struct animal* head = generateTree(sizeof(animalDictionary)/sizeof(animalDictionary[0]));
    struct animal* current = head;
    while (current != NULL) {
        if (current->name != NULL) {
            printf("\n\nI guess it's a %s\n", current->name);
            answer = getAnswer("Is it correct?");
            if(answer == 'y'){
                printf("\n\nI'm the best!");
                return 0;
            }
            if (current->question == NULL) {
                printf("\n\nI'm out of ideas!");
                return 1;
            }
            printf("\nToo bad!\nLet's continue!\n");
        }
        if (current->question != NULL) {
            answer = getAnswer(current->question);
            if (answer == 'y') {
                current = current->yes;
            }
            if (answer == 'n') {
                current = current->no;
            }
        }
    }
    return 0;
}