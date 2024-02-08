#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#define NUM_NODES 10
#define FILE_PATH "../files_to_read/graph_topo.txt"
#define FROM 5
#define TO 3

struct node{
    int value;
    char* name;
    int paths[NUM_NODES];
    int pathsLength;
};

struct node nodeDictionary[] = {};

//just in case, no usage right now
void addNode(int value, char* name){
    nodeDictionary[value].value = value;
    nodeDictionary[value].name = name;
}

void addPath(int from, int to, int distance){
    if(nodeDictionary[from].pathsLength == 0){
        nodeDictionary[from].pathsLength = 1;
    }else{
        nodeDictionary[from].pathsLength++;
    }
    nodeDictionary[from].paths[to] = distance;
}


int main(){
    int S[NUM_NODES][NUM_NODES];
    char line[100];
    int num1, num2, num3;

    for(int i = 0; i < NUM_NODES; i++){
        for(int j = 0; j < NUM_NODES; j++) {
            if (i == j) S[i][j] = 0;
            else S[i][j] = INT_MAX;
        }
    }

    FILE *fp;
    fp = fopen(FILE_PATH, "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        perror("Error");
        return 1;
    }
    printf("\n\n-------------START-------------\n");
    while (fgets(line, 100, fp) != NULL) {
        sscanf(line, "%d %d %d", &num1, &num2, &num3);
        printf("from => %d | to => %d | distance => %d\n", num1, num2, num3);
        //Store the path in the matrix for multiple usage
        addPath(num1, num2, num3);
        S[num1][num2] = num3;
    }

    fclose(fp);

    //Floyd-Warshall algorithm
    for(int k = 0; k < NUM_NODES; k++){ //k: intermediate_vertex
        for(int i = 0; i < NUM_NODES; i++){ //i: start_vertex
            for(int j = 0; j < NUM_NODES; j++){ //j: end_vertex
                if(S[i][k] != INT_MAX && S[k][j] != INT_MAX && S[i][k] + S[k][j] < S[i][j]){
                    S[i][j] = S[i][k] + S[k][j];
                }
            }
        }
    }

    if(S[FROM][TO] == INT_MAX){
        printf("\n\nNo path from %d to %d\n\n", FROM, TO);
        return 1;
    } else printf("\n\nShortest path from %d to %d is %d\n", FROM, TO, S[FROM][TO]);

    
    //Prim's algorithm
    int min = INT_MAX;
    int min_i = 0;
    int min_j = 0;
    int visited[NUM_NODES] = {0};
    int visitedCount = 0;
    int totalDistance = 0;
    int path[NUM_NODES] = {0};
    int pathCount = 0;

    visited[FROM] = 1;
    visitedCount++;
    while(visitedCount < NUM_NODES){
        for(int i = 0; i < NUM_NODES; i++){
            for(int j = 0; j < NUM_NODES; j++){
                if(S[i][j] < min && visited[i] == 1 && visited[j] == 0){
                    min = S[i][j];
                    min_i = i;
                    min_j = j;
                }
            }
        }
        visited[min_j] = 1;
        visitedCount++;
        totalDistance += min;
        path[pathCount] = min_j;
        pathCount++;
        min = INT_MAX;
    }
    printf("\n\nmin_i = %d | min_j = %d | totalDistance = %d\n", min_i, min_j, totalDistance);
    printf("\npath = ");
    for(int i = 0; i < pathCount; i++){
        printf("%d ", path[i]);
    }
    


    printf("\n-------------END-------------\n\n");

    
    return 0;
}
