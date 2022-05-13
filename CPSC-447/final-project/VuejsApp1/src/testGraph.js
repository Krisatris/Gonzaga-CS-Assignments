/*
    graph class for 447 network project
    based on an adjacency list graph representation
*/


export class Node {
    constructor(destination, weight) {
        this.destination = destination;
        this.weight = weight;
        this.next = null;
    }
}

export class LinkedList {
    constructor() {
        this.head = null;
    }
}

function insertAtHead(list, destination, weight) {
    let temp = new Node(destination, weight);
    temp.next = list.head;
    list.head = temp;
    return list;
}

export class Graph {

    constructor(vertexNum) {
        this.vertexNum = vertexNum;
        this.edgeNum = 0;
        this.adjacencyList = [];
        for (let i = 0; i < vertexNum; ++i) {
            let temp = new LinkedList();
            this.adjacencyList.push(temp);
        }
    }
}

export function addEdge(graph, source, destination, weight) {
    if (source < graph.vertexNum && destination < graph.vertexNum) {
        insertAtHead(graph.adjacencyList[source], destination, weight);
        insertAtHead(graph.adjacencyList[destination], source, weight);
        ++graph.edgeNum;
    }
}

function getEdge(graph, source, destination) {
    let temp = graph.adjacencyList[source].head;
    while (temp != null) {
        if (temp.destination == destination) {
            return temp.weight;
        }
        temp = temp.next;
    }
    return -1;
}

export function updateEdge(graph, source, destination, weight) {
    let temp = graph.adjacencyList[source].head;
    while (temp != null) {
        if (temp.destination == destination) {
            temp.weight = weight;
        }
        temp = temp.next;
    }
    temp = graph.adjacencyList[destination].head;
    while (temp != null) {
        if (temp.destination == source) {
            temp.weight = weight;
            return true;
        }
        temp = temp.next;
    }
    return false;
}

export function removeEdge(graph, source, destination) {
    let temp = graph.adjacencyList[source].head;
    let prev = temp;
    while (temp != null) {
        if (temp.destination == destination) {
            if (temp == graph.adjacencyList[source].head) {
                graph.adjacencyList[source].head = temp.next;
            } else {
                prev.next = temp.next;
            }
        }
        prev = temp;
        temp = temp.next;
    }
    temp = graph.adjacencyList[destination].head;
    prev = temp;
    while (temp != null) {
        if (temp.destination == source) {
            if (temp == graph.adjacencyList[destination].head) {
                graph.adjacencyList[destination].head = temp.next;
                --graph.edgeNum;
                return true;
            } else {
                prev.next = temp.next;
                --graph.edgeNum;
                return true;
            }
        }
        prev = temp;
        temp = temp.next;
    }
    return false;
}

export function dijkstra(graph, source) {
    let discovered = [];
    let path_costs = [];
    let path = [];
    for (let i = 0; i < graph.vertexNum; ++i) {
        discovered.push(false);
        path_costs.push(Number.MAX_SAFE_INTEGER);
        path.push(null);
    }
    discovered[source] = true;
    path_costs[source] = 0;
    path[source] = -1;

    let weight, min_dist, u_p, v_p;
    do {
        min_dist = -1;
        for (let u = 0; u < graph.vertexNum; ++u) {
            for (let v = 0; v < graph.vertexNum; ++v) {
                if (discovered[u] && !discovered[v] && getEdge(graph, u, v) != -1) {
                    weight = getEdge(graph, u, v);
                    if (min_dist > (path_costs[u] + weight) || min_dist == -1) {
                        u_p = u;
                        v_p = v;
                        min_dist = path_costs[u] + weight;
                    }
                }
            }
        }
        if (min_dist != -1) {
            discovered[v_p] = true;
            path_costs[v_p] = min_dist;
            path[v_p] = u_p;
        }
    } while (min_dist != -1);

    return path;
}

/*
export function tracePath(parents, source, destination) {
    let path = [];
    tracePathRec(path, parents, destination, source);
    return path;
}

function tracePathRec(path, parents, node, source) {
    if (parents[node] == -1) {
        path.push(node);
    } else {
        path.push(parents[node]);
        tracePathRec(path, parents, parents[node], source);
    }
}
*/

/*
let g1 = new Graph(4);
console.log(addEdge(g1, 0, 1, 1));
console.log(addEdge(g1, 1, 2, 1));
console.log(addEdge(g1, 2, 3, 1));
console.log(addEdge(g1, 3, 0, 1));
console.log(updateEdge(g1, 0, 1, 2));
console.log(removeEdge(g1, 2, 3));

let g = new Graph(6);
g.addEdge(0, 1, 1);
g.addEdge(1, 2, 1);
g.addEdge(2, 3, 1);
g.addEdge(3, 4, 1);
g.addEdge(4, 5, 1);
g.addEdge(5, 6, 1);
g.addEdge(0, 2, 2);
g.addEdge(0, 3, 1);
g.addEdge(1, 4, 2);
let path = g.dijkstra(0);
console.log(path);
*/