//You have a business with several offices; you want to lease phone lines to connect them up with each other; and the phone company charges different amounts of money to connect different pairs of cities. You want a set of lines that connects all your offices with a minimum total cost. Solve the problem by suggesting appropriate data structures. 

#include <iostream>
using namespace std;

// Structure to represent a graph edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Function to create a graph
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

// Function to find the subset of an element
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// Function to do union of two subsets
void Union(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

// Function to find the minimum spanning tree
void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int i = 0, e = 0;
    int parent[V];
    for (int i = 0; i < V; i++)
        parent[i] = -1;

    // Sort all the edges in non-decreasing order of their weight
    for (int i = 0; i < graph->E; i++) {
        for (int j = i + 1; j < graph->E; j++) {
            if (graph->edge[i].weight > graph->edge[j].weight)
                swap(graph->edge[i], graph->edge[j]);
        }
    }

    // Pick the smallest edge and check if it forms a cycle with the spanning tree formed so far
    while (e < V - 1) {
        struct Edge next_edge = graph->edge[i++];
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);
        if (x != y) {
            result[e++] = next_edge;
            Union(parent, x, y);
        }
    }

    // Print the edges of the minimum spanning tree
    cout << "Edges of the minimum spanning tree:\n";
    for (i = 0; i < e; ++i)
        cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;
    cout << "Minimum Spanning Tree" << endl;
}

int main() {
    int V = 0, E = 0;

    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    struct Graph* graph = createGraph(V, E);

    // Add edges to the graph
    for (int i = 0; i < E; ++i) {
        cout << "Enter source, destination, and weight of edge " << i + 1 << ": ";
        cin >> graph->edge[i].src >> graph->edge[i].dest >> graph->edge[i].weight;
    }

    KruskalMST(graph);

    return 0;
}
