/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
#define MAX_EDGES 6000
#define INF 0x3f3f3f3f

int dist[MAX_NODES + 1];

struct Edge {
    int source;
    int dest;
    int weight;
};

struct Graph {
    int numNodes;
    int numEdges;
    struct Edge edges[MAX_EDGES];
};

void initialize(int startNode, int numNodes) {
    for (int i = 1; i <= numNodes; i++) {
        dist[i] = INF;
    }
    dist[startNode] = 0;
}

void bellmanFord(struct Graph graph, int startNode) {
    initialize(startNode, graph.numNodes);

    for (int i = 1; i <= graph.numNodes - 1; i++) {
        for (int j = 0; j < graph.numEdges; j++) {
            int u = graph.edges[j].source;
            int v = graph.edges[j].dest;
            int weight = graph.edges[j].weight;

            if (dist[u] != INF && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative weight cycles
    for (int i = 0; i < graph.numEdges; i++) {
        int u = graph.edges[i].source;
        int v = graph.edges[i].dest;
        int weight = graph.edges[i].weight;

        if (dist[u] != INF && dist[v] > dist[u] + weight) {
            printf("There is a negative weight cycle in the graph\n");
            exit(0);
        }
    }
}

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k){
    struct Graph graph;
    graph.numNodes = n;
    graph.numEdges = timesSize;

    for (int i = 0; i < timesSize; i++) {
        int source = times[i][0];
        int dest = times[i][1];
        int weight = times[i][2];

        graph.edges[i].source = source;
        graph.edges[i].dest = dest;
        graph.edges[i].weight = weight;
    }

    bellmanFord(graph, k);

    int maxTime = -1;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) {
            return -1;
        }
        if (dist[i] > maxTime) {
            maxTime = dist[i];
        }
    }

    return maxTime;
}

int main() {
    int timesArr[3][3] = {{2,1,1},{2,3,1},{3,4,1}};
    int n = 4;
    int k = 2;

    // Convert input to format expected by function
    int** times = (int**) malloc(sizeof(int*) * 3);
    for (int i = 0; i < 3; i++) {
        times[i] = (int*) malloc(sizeof(int) * 3);
        for (int j = 0; j < 3; j++) {
            times[i][j] = timesArr[i][j];
        }
    }
    int timesSize = 3;
    int timesColSize[3] = {3, 3, 3};

    int result = networkDelayTime(times, timesSize, timesColSize, n, k);
    printf("Result: %d\n", result);
}

    // Free dynamically allocated
