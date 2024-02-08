#include <stdio.h>
#define MAX_SIZE 100

int main(){
    int arvud1[MAX_SIZE];
    int arvud1Pea = 0;
    int arvud2[MAX_SIZE];
    int arvud2Pea = 0;
    int n = 0;
    int x1 = 0;
    int x2;
    char vastus = 'j';
    float prots1,prots2;
    int arv;
    do{
        n = n + 1;
        printf("\nSisesta arv: ");
        scanf("%d",&arv);
        arvud1[arvud1Pea] = arv;
        arvud1Pea++;
        printf("\nKas on veel arve?: ");
        scanf("%s",&vastus);
    }while (vastus == 'j');
    for (int i = 0; i < arvud1Pea; i++)
    {
        if ((arvud1[i] % 2) == 0)
        {
            arvud2[arvud2Pea] = arvud1[i];
            arvud2Pea++;
            x1 = x1 + 1;
        }
    }
    x2 = n - x1;
    prots1 = (float)x1/(float)n * (float)100;
    prots2 = (float)x2/(float)n * (float)100;
    printf("\nSisestatud arvudest oli %0.1f protsenti paarisarvud ja %0.1f protsenti paaritud arvud.\n",prots1,prots2);
    printf("\nSisestatud paarisarvud olid jargmised: ");
    for (int i = 0; i < arvud2Pea; i++)
    {
        printf("%d, ",arvud2[i]);
    }     
    return 0;
}
