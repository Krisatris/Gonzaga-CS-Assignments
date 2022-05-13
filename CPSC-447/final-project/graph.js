/*
    graph class for 447 network project
    based on an adjacency list graph representation
*/

class Node {
    constructor(destination, weight) {
        this.destination = destination;
        this.weight = weight;
        this.next = null;
    }
};

class LinkedList {
    constructor() {
        this.head = null;
    }

    insertAtHead(destination, weight) {
        let temp = new Node(destination, weight);
        temp.next = this.head;
        this.head = temp;
        return this;
    }
};

class Graph {

    constructor(vertexNum) {
        this.vertexNum = vertexNum;
        this.edgeNum = 0;
        this.adjacencyList = [];
        for(let i = 0; i < vertexNum; ++i) {
            let temp = new LinkedList();
            this.adjacencyList.push(temp);
        }
    }

    addEdge(source, destination, weight) {
        if(source < this.vertexNum && destination < this.vertexNum) {
            this.adjacencyList[source].insertAtHead(destination, weight);
            this.adjacencyList[destination].insertAtHead(source, weight);
            ++this.edgeNum;
        }
    }

    getEdge(source, destination) {
        let temp = this.adjacencyList[source].head;
        while(temp != null) {
            if(temp.destination == destination) {
                return temp.weight;
            }
            temp = temp.next;
        }
        return -1;
    }

    updateEdge(source, destination, weight) {
        let temp = this.adjacencyList[source].head;
        while(temp != null) {
            if(temp.destination == destination) {
                temp.weight = weight;
            }
            temp = temp.next;
        }
        temp = this.adjacencyList[destination].head;
        while(temp != null) {
            if(temp.destination == source) {
                temp.weight = weight;
                return true;
            }
            temp = temp.next;
        }
        return false;
    }

    removeEdge(source, destination) {
        let temp = this.adjacencyList[source].head;
        let prev = temp;
        while(temp != null) {
            if(temp.destination == destination) {
                if(temp == this.adjacencyList[source].head) {
                    this.adjacencyList[source].head = temp.next;
                } else {
                    prev.next = temp.next;
                }
            }
            prev = temp;
            temp = temp.next;
        }
        temp = this.adjacencyList[destination].head;
        prev = temp;
        while(temp != null) {
            if(temp.destination == source) {
                if(temp == this.adjacencyList[destination].head) {
                    this.adjacencyList[destination].head = temp.next;
                    --this.edgeNum;
                    return true;
                } else {
                    prev.next = temp.next;
                    --this.edgeNum;
                    return true;
                }
            }
            prev = temp;
            temp = temp.next;
        }
        return false;
    }

    dijkstra(source) {
        let discovered = [];
        let path_costs = [];
        let path = [];
        for(let i = 0; i < this.vertexNum; ++i) {
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
            for(let u = 0; u < this.vertexNum; ++u) {
                for(let v = 0; v < this.vertexNum; ++v) {
                    if(discovered[u] && !discovered[v] && this.getEdge(u, v) != -1) {
                        weight = this.getEdge(u, v);
                        if(min_dist > (path_costs[u] + weight) || min_dist == -1) {
                            u_p = u;
                            v_p = v;
                            min_dist = path_costs[u] + weight;
                        }
                    }
                }
            }
            if(min_dist != -1) {
                discovered[v_p] = true;
                path_costs[v_p] = min_dist;
                path[v_p] = u_p;
            }
        } while(min_dist != -1);

        return path;
    }
};

let g1 = new Graph(4);
console.log(g1.addEdge(0, 1, 1));
console.log(g1.addEdge(1, 2, 1));
console.log(g1.addEdge(2, 3, 1));
console.log(g1.addEdge(3, 0, 1));
console.log(g1.updateEdge(0, 1, 2));
console.log(g1.removeEdge(2, 3));

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