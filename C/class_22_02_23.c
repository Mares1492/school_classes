#include <stdlib.h>
#include <stdio.h>

struct node{
    int value;
    struct node *next;
};



struct node* generateList(int branchesToGenerate){
    struct node *head = NULL,*current = NULL, *temp = NULL;
    while(branchesToGenerate > 0){
        temp = (struct node*)malloc(sizeof(struct node));
        temp->value = branchesToGenerate;
        temp->next = NULL;
        if(head == NULL){
            head = temp;
            current = temp;
        }else{
            current->next = temp;
            current = temp;
        }
        printf("\n\nGenerated value %d, %d branches leftS", temp->value, branchesToGenerate-1);
        branchesToGenerate--;
    }
    return head;
}

int main(){
    struct node *head = NULL;
    head = generateList(5);
    printf("\n\n------------------------");
    struct node* current = head;
    while (current != NULL){
        printf("\n\nValue: %d", current->value);
        current = current->next;
    }
    return 1;
}


