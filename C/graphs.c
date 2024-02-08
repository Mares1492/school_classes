#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_NODES 100

struct data{
    int left;
    int right;
};

int main(){
    char symbol;
    int heap = 0;
    int dataHeap = 0;
    char *line = calloc(100, sizeof(char));
    int **graph = (int **)calloc(MAX_NODES, sizeof(int *));
    for (int i = 0; i < MAX_NODES; i++) {
        graph[i] = (int *)calloc(MAX_NODES, sizeof(int));
    }
    int *dist = calloc(MAX_NODES, sizeof(int));
    int *visited = calloc(MAX_NODES, sizeof(int));
    FILE *fp;
    fp = fopen("../files_to_read/graph_topo.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        perror("Error");
        return 1;
    }
    printf("\n\n-------------START-------------\n");
    while (fscanf(fp, "%c", &symbol) != EOF) {
        if(symbol == '\n'){
            printf("%s\n", line);
            if(strlen(line) == 3){
                struct data data = {line[0] - '0', line[2] - '0'};
                graph[data.left][data.right] = 1;
                graph[data.right][data.left] = 1;
            }
            heap = 0;
            line = calloc(100, sizeof(char));
            continue;
        }
        line[heap] = symbol;
        heap++;
    }
    printf("\n-------------END-------------\n");
    return 0;
}
