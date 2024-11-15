#include<bits/stdc++.h>
using namespace std;

// Function to check if an edge exists between two vertices in the adjacency list
bool search(vector<int> adjList[], int v1, int v2) {
    // Each vertex's adjacency list is iterated through to find if the edge exists
    for (int i = 0; i < adjList[v1 - 1].size(); i++) {
        if (adjList[v1 - 1][i] == v2 - 1) {
            return true; // If found, true is returned
        }
    }
    return false; // If no match is found, false is returned
}

// Function to add an edge to the adjacency list between two vertices
void addEdge(vector<int> adjList[], int v1, int v2) {
    // The second vertex is added to the adjacency list of the first vertex
    adjList[v1 - 1].push_back(v2 - 1);
    cout << "Edge added between " << v1 << " and " << v2 << endl;
}

// Function to display the adjacency list of the graph
void displayList(vector<int> adjList[], int V) {
    // The adjacency list is printed for each vertex
    cout << "The adjacency List is:" << endl;
    for (int i = 0; i < V; i++) {
        cout << i + 1 << ": "; // Vertex number is printed (1-based index)
        sort(adjList[i].begin(), adjList[i].end()); // The adjacency list for each vertex is sorted
        // Each adjacent vertex is printed
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << adjList[i][j] + 1 << ", "; // Convert back to 1-based index before printing
        }
        cout << endl;
    }
}

// Function to perform topological sorting on a directed graph using Kahn's Algorithm
vector<int> topologicalSort(vector<int> adjList[], int V) {
    queue<int> q; // Queue is used to process vertices with no incoming edges
    int indegree[V];
    memset(indegree, 0, sizeof(indegree)); // The indegree array is initialized to 0 for all vertices

    // The indegree of each vertex is calculated by iterating through all edges
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < adjList[i].size(); j++) {
            indegree[adjList[i][j]]++; // Increment the indegree for the destination vertex
        }
    }

    // All vertices with no incoming edges (indegree = 0) are added to the queue
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i); // Vertex is added to the queue
        }
    }

    vector<int> topo; // Vector to store the topologically sorted order
    while (!q.empty()) {
        int node = q.front(); // The front vertex is processed
        q.pop(); // The vertex is removed from the queue
        topo.push_back(node); // The vertex is added to the topological order

        // All the adjacent vertices of the processed node are checked
        for (int i = 0; i < adjList[node].size(); i++) {
            indegree[adjList[node][i]]--; // Decrement the indegree of the adjacent vertex
            if (indegree[adjList[node][i]] == 0) {
                q.push(adjList[node][i]); // If indegree becomes 0, the vertex is added to the queue
            }
        }
    }

    return topo; // Return the topologically sorted order
}

// Function to display the topological order of vertices
void displayTopologicalOrder(vector<int>& topoList, int V) {
    // The topological order is printed in a human-readable format
    cout << topoList[0] + 1; // The first vertex is printed
    for (int i = 1; i < V; i++) {
        cout << "->" << topoList[i] + 1 << " "; // The remaining vertices are printed with arrows
    }
    cout << endl;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V; // The number of vertices is read from the user
    cout << "Enter the number of edges: ";
    cin >> E; // The number of edges is read from the user

    // Input validation is done for the number of vertices and edges
    if (V < 0) {
        cout << "Give non-zero value of number of vertices" << endl;
        exit(1); // The program exits if the number of vertices is invalid
    }

    if (E < 0 || E > (V * (V - 1)) / 2) {
        cout << "Edge number should be between 0 to " << (V * (V - 1)) / 2 << endl;
        exit(1); // The program exits if the number of edges is out of range
    }

    vector<int> adjList[V]; // The adjacency list is created for the graph
    int v1, v2;
    int edgeCount = 0;

    // Loop to add edges until the specified number of edges is reached
    while (edgeCount < E) {
        cout << "Enter first vertex of the edge to be added: ";
        cin >> v1; // First vertex of the edge is input
        cout << "Enter second vertex of the edge to be added: ";
        cin >> v2; // Second vertex of the edge is input

        // Check for invalid or duplicate edges
        if (v1 == v2) {
            cout << "Give different vertices as self-loop is not considered" << endl;
        } else if (v1 < 1 || v1 > V || v2 < 1 || v2 > V) {
            cout << "Choose vertex between 1 to " << V << endl; // Validate vertices within bounds
        } else if (search(adjList, v1, v2)) {
            cout << "Edge already exists" << endl; // Prevent duplicate edges
        } else {
            // The edge is added if all checks pass
            addEdge(adjList, v1, v2);
            edgeCount++; // Increment the edge count
        }
    }

    // Display the adjacency list
    displayList(adjList, V);

    // Perform topological sort and store the result
    vector<int> topoList = topologicalSort(adjList, V);

    // Check if the topological sort was successful (i.e., no cycle exists)
    if (topoList.size() < V) {
        cout << "The Directed Graph is cyclic" << endl;
        exit(0); // The program exits if the graph contains a cycle
    }

    // Display the topological order if the graph is acyclic
    cout << "The directed graph is acyclic and the corresponding deterministic ordering of the vertices is:" << endl;
    displayTopologicalOrder(topoList, V);

    return 0;
}
