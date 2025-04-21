/*Consider the scenario of the supply chain management system. The supply chain involves 
multiple locations, such as suppliers, warehouses, distribution centers, and retail stores, 
connected by transportation networks. Find the shortest possible route using Dijkstra's 
algorithm to optimize transportation path and inventory management. */
#include <iostream>  // For input and output
using namespace std;

#define INF 99999999  // Represents infinity (i.e., no connection between nodes)
#define V 5           // Number of locations/nodes

// Graph class to handle the supply chain network
class Graph {
public:
    // Names of locations in the supply chain
    string locations[V] = {"Supplier", "Warehouse", "Distribution", "Retail1", "Retail2"};

    // Adjacency matrix to store distances between locations
    int G[V][V];

    // Function to read the adjacency matrix from user input
    void readGraph() {
        cout << "Enter distances between locations (" << V << "x" << V << " matrix):" << endl;

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cin >> G[i][j];  // Read distance from i to j

                // If no direct connection and it's not the same node, mark it as infinity
                if (G[i][j] == 0 && i != j) {
                    G[i][j] = INF;
                }
            }
        }
    }

    // Function to print the adjacency matrix (graph)
    void printGraph() {
        cout << "\nAdjacency Matrix (Distances):" << endl;

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // Print INF instead of large number for clarity
                if (G[i][j] == INF)
                    cout << "INF ";
                else
                    cout << G[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Dijkstra's algorithm to find the shortest path from a source location
    void dijkstra(int src) {
        int dist[V];           // Stores the shortest distances from source
        bool visited[V] = {false}; // Keeps track of visited locations

        // Initialize all distances as infinity
        for (int i = 0; i < V; i++)
            dist[i] = INF;

        dist[src] = 0;  // Distance from source to itself is 0

        // Repeat V-1 times to find shortest path to all nodes
        for (int count = 0; count < V - 1; count++) {
            int min = INF, u = -1;

            // Find the unvisited node with the smallest distance
            for (int i = 0; i < V; i++) {
                if (!visited[i] && dist[i] <= min) {
                    min = dist[i];
                    u = i;
                }
            }

            visited[u] = true;  // Mark the selected node as visited

            // Update distances of adjacent unvisited nodes
            for (int v = 0; v < V; v++) {
                if (!visited[v] && G[u][v] != INF && dist[u] + G[u][v] < dist[v]) {
                    dist[v] = dist[u] + G[u][v];  // Relax the edge
                }
            }
        }

        // Output the shortest distances from the source
        cout << "\nShortest paths from " << locations[src] << ":" << endl;
        for (int i = 0; i < V; i++) {
            cout << locations[src] << " -> " << locations[i] << " : ";
            if (dist[i] == INF)
                cout << "Unreachable" << endl;
            else
                cout << dist[i] << endl;
        }
    }
};

// Main function to run the program
int main() {
    Graph g;             // Create graph object
    g.readGraph();       // Read graph input from user
    g.printGraph();      // Display the adjacency matrix

    int source;
    // Ask user to choose a source location
    cout << "\nEnter the source location (0-" << V - 1 << "): ";
    cin >> source;

    // Run Dijkstra's algorithm from the chosen source
    g.dijkstra(source);

    return 0;
}
 