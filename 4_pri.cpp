/*Represent a graph of your college campus using adjacency list /adjacency matrix. Nodes should 
represent the various departments and links should represent the distance between them. Find a 
minimum spanning tree using Kruskal’s algorithm or using Prim’s algorithm. */
#include <iostream>
using namespace std;
#define INF 99999999
#define V 5

class Graph {
public:
    string departments[V] = {"Admin", "Library", "CSE", "ECE", "Mechanical"};
    int G[V][V];

    void readGraph() {
        cout << "Enter distances between departments (" << V << "x" << V << " matrix):" << endl;  
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cin >> G[i][j];
            }
        }
    }

    void printGraph() {
        cout << "\nAdjacency Matrix (Distances):" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << G[i][j] << " ";
            }
            cout << endl;
        }
    }

    void prims() {
        int no_edge = 0;
        int totalCost = 0;
        bool visited[V] = {false};

        visited[0] = true;
        cout << "\nMinimum Selected Edges : Distance" << endl;

        while (no_edge < V - 1) {
            int min = INF;
            int row = -1, col = -1;

            for (int i = 0; i < V; i++) {
                if (visited[i]) {
                    for (int j = 0; j < V; j++) {
                        if (!visited[j] && G[i][j] && G[i][j] < min) {
                            min = G[i][j];
                            row = i;
                            col = j;
                        }
                    }
                }
            }

            if (row != -1 && col != -1) {
                cout << departments[row] << " - " << departments[col] << " : " << G[row][col] << endl;
                visited[col] = true;
                totalCost += G[row][col];
                no_edge++;
            }
        }

        cout << "Total Distance of MST: " << totalCost << endl;
    }
};

int main() {
    Graph g;
    g.readGraph();
    g.printGraph();
    g.prims();
    return 0;
}
