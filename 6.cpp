#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
const int MAX_VERTICES = 100;

class Graph {
private:
    int V; 
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    bool visited[MAX_VERTICES] = {false};

public:
    Graph(int vertices) : V(vertices) { //constructor
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                adjMatrix[i][j] = (i == j) ? 0 : '-';  //adjMatrix[i][j] = INF; is also correct
    }

    void addEdge(int src, int dest, int weight) {
        adjMatrix[src][dest] = adjMatrix[dest][src] = weight; //undirected graph
    }

    string cityNames[MAX_VERTICES]; // Array to store city names
    void setCityName(int vertex, const string& name) {
        cityNames[vertex] = name;
    }

    void DFS(int v) {
        visited[v] = true;
        for (int i = 0; i < V; ++i) {
            if (adjMatrix[v][i] != '-' && !visited[i]) {
                DFS(i);
            }
        }
    }

    bool isConnected() {
        // Start DFS from the first vertex
        DFS(0);
        // Check if all vertices are visited
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                // If any vertex is not visited, the graph is not connected
                return false;
            }
        }
        return true;
    }

    void displayGraph() const {
    // Display city names
    cout << setw(8) << " ";
    for (int j = 0; j < V; ++j)
        cout << setw(8) << cityNames[j];
    cout << endl;

    // Display adjacency matrix
    for (int i = 0; i < V; ++i) {
        cout << setw(8) << cityNames[i];
        for (int j = 0; j < V; ++j) {
            if (adjMatrix[i][j] == '-')
                cout << setw(8) << "-";
            else
                cout << setw(8) << adjMatrix[i][j];
        }
        cout << endl;
    }
}

};

int main() {
    int numCities;
    cout << "Enter the number of cities: ";
    cin >> numCities;

    Graph g(numCities);

    for (int i = 0; i < numCities; ++i) {
        cout << "Enter the name of city " << i << ": ";
        cin >> g.cityNames[i];
    }

    char choice;
    for (int i = 0; i < numCities; ++i) {
        for (int j = i + 1; j < numCities; ++j) {
            cout << "Is there an edge between " << g.cityNames[i] << " and " << g.cityNames[j] << "? (y/n): ";
            cin >> choice;
            if (choice == 'y') {
                int weight;
                cout << "Enter the weight of the edge: ";
                cin >> weight;
                g.addEdge(i, j, weight);
            }
        }
    }

    cout << "Adjacency Matrix representing the weighted graph:" << endl;
    g.displayGraph();

    return 0;
}
