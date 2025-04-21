#include <iostream>
using namespace std;

#define V 5
#define INF 99999999

class Graph {
public:
    // Departments (Nodes of the campus graph)
    string departments[V] = {"Admin", "Library", "CSE", "ECE", "Mechanical"};
    int G[V][V]; // Adjacency matrix for distances (edges)

    struct Edge {
        int src, dest, weight;
    };

    int parent[V];

    // Read the adjacency matrix representing distances between departments
    void readGraph() {
        cout << "Enter distances between departments (" << V << "x" << V << " matrix):" << endl;  
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cin >> G[i][j];
            }
        }
    }

    // Display the adjacency matrix
    void printGraph() {
        cout << "\nAdjacency Matrix (Distances):" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << G[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Find function for union-find
    int find(int i) {
        while (parent[i] != i)
            i = parent[i];
        return i;
    }

    // Union function for union-find
    void unionSet(int u, int v) {
        int uRoot = find(u);
        int vRoot = find(v);
        parent[uRoot] = vRoot;
    }

    // Kruskal's algorithm to find the Minimum Spanning Tree (MST)
    void kruskal() {
        Edge edges[V * V];
        int edgeCount = 0;

        // Convert adjacency matrix to edge list
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (G[i][j] != 0) {
                    edges[edgeCount++] = {i, j, G[i][j]};
                }
            }
        }

        // Sort edges by weight (simple bubble sort)
        for (int i = 0; i < edgeCount - 1; i++) {
            for (int j = 0; j < edgeCount - i - 1; j++) {
                if (edges[j].weight > edges[j + 1].weight) {
                    swap(edges[j], edges[j + 1]);
                }
            }
        }

        // Initialize each node as its own parent
        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        int totalCost = 0;
        int selectedEdges = 0;

        cout << "\nMinimum Spanning Tree using Kruskal's Algorithm:" << endl;
        cout << "Selected Edges : Distance" << endl;

        for (int i = 0; i < edgeCount && selectedEdges < V - 1; i++) {
            int u = edges[i].src;
            int v = edges[i].dest;
            int set_u = find(u);
            int set_v = find(v);

            if (set_u != set_v) {
                cout << departments[u] << " - " << departments[v] << " : " << edges[i].weight << endl;
                totalCost += edges[i].weight;
                unionSet(set_u, set_v);
                selectedEdges++;
            }
        }

        cout << "Total Distance of Minimum Spanning Tree: " << totalCost << endl;
    }
};

int main() {
    Graph g;
    g.readGraph();
    g.printGraph();
    g.kruskal();
    return 0;
}
