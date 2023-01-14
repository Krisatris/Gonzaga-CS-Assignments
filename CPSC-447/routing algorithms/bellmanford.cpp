#include <bits/stdc++.h>
#include <vector>
#include <unordered_map>

struct Edge {
    int src, dst, weight;
};

struct Graph {
    int vertexNum, edgeNum;

    struct Edge* edge;
};

struct Graph* createGraph(int v, int e) {
    struct Graph* graph = new Graph;
    graph->vertexNum = v;
    graph->edgeNum = e;
    graph->edge = new Edge[e];
    return graph;   
};

void printArr(int dist[], std::unordered_map<int, int> forwardingTable, int n) {
    printf("Vertex\tDistance from source\n");
    for(int i = 0; i < n; ++i) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
    printf("\nDestination \t Link\n");
    for(int i = 0; i < n; ++i) {
        printf("%d \t\t (4,%d)\n", i, forwardingTable[i]);
    }
}

int getForwarding(std::vector<int> table, int node, int src){
    if(table[node] == src){
        return node;
    }
    return getForwarding(table, table[node], src);
}

void BellmanFord(struct Graph* graph, int src) {

    int v = graph->vertexNum;
    int e = graph->edgeNum;
    int dist[v];
    std::vector<int> parent (v, -1);

    for(int i = 0; i < v; ++i) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;
    parent[src] = -1;

    int s, t, weight;
    for(int i = 1; i <= v - 1; ++i) {
        for(int j = 0; j < e; ++j) {
            s = graph->edge[j].src;
            t = graph->edge[j].dst;
            weight = graph->edge[j].weight;
            if(dist[s] != INT_MAX && dist[s] + weight < dist[t]) {
                dist[t] = dist[s] + weight;
                parent[t] = s;
            }
        }
    }

    // build forwarding table
    std::unordered_map<int, int> forwardingTable;
    for(int i = 0; i < v; ++i) {
        forwardingTable[i] = getForwarding(parent, i, 4);
    }
    forwardingTable[src] = src;

    printArr(dist, forwardingTable, v);
}

int main() {
    
    struct Graph* graph = createGraph(5, 6);

    // u - > v
    graph->edge[0].src = 1;
    graph->edge[0].dst = 0;
    graph->edge[0].weight = 1;

    // u - > y
    graph->edge[1].src = 3;
    graph->edge[1].dst = 0;
    graph->edge[1].weight = 2;

    // v - > x
    graph->edge[2].src = 2;
    graph->edge[2].dst = 1;
    graph->edge[2].weight = 3;

    // y - > x
    graph->edge[3].src = 2;
    graph->edge[3].dst = 3;
    graph->edge[3].weight = 3;

    // z  - > x
    graph->edge[4].src = 4;
    graph->edge[4].dst = 2;
    graph->edge[4].weight = 2;

    // z -> v
    graph->edge[5].src = 4;
    graph->edge[5].dst = 1;
    graph->edge[5].weight = 6;

    BellmanFord(graph, 4);

    return 0;
}