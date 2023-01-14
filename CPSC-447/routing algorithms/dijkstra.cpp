/*
    LEGEND:
    u = 0
    v = 1
    w = 2
    x = 3
    y = 4
    z = 5
*/
#include <algorithm>
#include <list>
#include <unordered_map>
#include <climits>

void print(int dist[], std::unordered_map<int,int> table){
    printf("LEGEND: u = 0, v = 1, w = 2, x = 3, y = 4, z = 5\n\n");
    printf("Vertex \t\t Distance from Source\n");
    for(int i = 0; i < 6; ++i){
        printf("%d \t\t %d\n", i, dist[i]);
    }
    printf("\nDestination \t Link\n");
    for(int i = 0; i < 6; ++i){
        printf("%d \t\t (5,%d)\n", i, table[i]);
    }
}


int getForwarding(std::unordered_map<int,int> table, int node, int src){
    if(table[node] == src){
        return node;
    }
    return getForwarding(table, table[node], src);
}


void dijkstra(int graph[6][6],int src){
    // init
    std::list<int> path;
    path.push_back(src);

    std::unordered_map<int,int> table;
    int dist[6];

    for(int i = 0; i < 6; ++i){
        if(graph[src][i] != 0){
            dist[i] = graph[src][i];
            table[i] = src;
        }else{
            dist[i] = INT_MAX;
            table[i] = -1;
        }
    }     
    dist[src] = 0;
    table[src] = 0;

    // loop for all nodes in path
    while(path.size() < 6){
        int min_index = -1;
        int min_value = INT_MAX;
        //find w
        for(int j = 0; j < 6; ++j){
            if(!(std::find(path.begin(), path.end(), j) != path.end())){
                if(dist[j] < min_value){
                min_index = j;
                min_value = dist[j];
                }
            }
            
        }
        // add w to path
        int w = min_index;
        path.push_back(w);
        // update dist(v) for v adjacent to w and not in path
        for(int v = 0; v < 6; ++v){
            if(!(std::find(path.begin(), path.end(), v) != path.end())){
                if(graph[w][v] != 0 ){
                int before_val = dist[v];
                dist[v] = std::min(dist[v],dist[w] + graph[w][v]);
                if(before_val != dist[v])
                    table[v] = w;
                }
            }
            
        }  

    }
    // forwarding table
    std::unordered_map<int,int> forwarding_table;
    for(int i = 0; i < 6; ++i){
        forwarding_table[i] = getForwarding(table, i, 5);
    }
    forwarding_table[src] = src;

    print(dist,forwarding_table);
}

int main() {

    //                   u, v, w, x, y, z
    int graph[6][6] = { {0, 2, 5, 1, 0, 0},    // u
                        {2, 0, 3, 2, 0, 0},    // v
                        {5, 3, 0, 3, 1, 5},    // w
                        {1, 2, 3, 0, 1, 0},    // x
                        {0, 0, 1, 1, 0, 2},    // y
                        {0, 0, 5, 0, 2, 0} };  // z

    dijkstra(graph, 5);

    return 0;
}