#include<bits/stdc++.h>
using namespace std;

// The function is used to search for an edge between two vertices.
bool search(vector<int> adjList[], int v1, int v2) {
    // The adjacency list for vertex v1 is iterated to find if v2 exists.
    for (int i = 0; i < adjList[v1-1].size(); i++) {
        // If a match is found, true is returned.
        if (adjList[v1-1][i] == v2-1) {
            return true;
        }
    }
    // If no match is found, false is returned.
    return false;
}

// An edge is added between two vertices.
void addEdge(vector<int> adjList[], int v1, int v2) {
    // Vertex v2 is added to the adjacency list of v1.
    adjList[v1 - 1].push_back(v2-1);
    // A message is displayed to confirm that the edge has been added.
    cout << "Edge added between " << v1 << " and " << v2 << endl;
}

// The adjacency list is displayed.
void displayList(vector<int> adjList[], int V) {
    cout << "The adjacency List is:" << endl;
    // Each vertex's adjacency list is displayed.
    for (int i = 0; i < V; i++) {
        cout << i + 1 << ": ";
        // The adjacency list for vertex i is sorted.
        sort(adjList[i].begin(), adjList[i].end());
        // Each adjacent vertex is displayed.
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << adjList[i][j] + 1 << ", ";
        }
        cout << endl;
    }
}

// Depth First Search (DFS) is performed to explore the graph.
void dfs(int node, int visited[], vector<int> adjList[], vector<int>& dfsTree, 
         int& start, int& finish, int dfsNo[], int dfsCompletionNo[]) {
    // The current node is marked as visited.
    visited[node] = 1;
    // The current node is added to the DFS tree.
    dfsTree.push_back(node);
    // The discovery time of the current node is recorded.
    dfsNo[node] = ++start;
    // Each adjacent node is visited if it hasn't been visited.
    for (int i = 0; i < adjList[node].size(); i++) {
        if (!visited[adjList[node][i]]) {
            // DFS is called recursively on unvisited adjacent nodes.
            dfs(adjList[node][i], visited, adjList, dfsTree, start, finish, dfsNo, dfsCompletionNo);
        }
    }
    // The finish time of the current node is recorded.
    dfsCompletionNo[node] = ++finish;
}

// The DFS tree is displayed along with discovery and completion times.
void dfsTreeDisplay(int node, vector<int> dfsForest[], int dfsNo[], int dfsCompletionNo[]) {
    // The current node and its discovery and completion times are displayed.
    cout << node + 1 << "(" << dfsNo[node] << "/" << dfsCompletionNo[node] << ")" << " ";
    // Each adjacent node's discovery and completion times are displayed.
    for (int i = 1; i < dfsForest[node].size(); i++) {
        int u = dfsForest[node][i];
        cout << "->" << u + 1 << "(" << dfsNo[u] << "/" << dfsCompletionNo[u] << ")" << " ";
    }
    cout << endl;
}

int main() {
    int V, E;
    // The number of vertices is requested from the user.
    cout << "Enter the no of vertices: ";
    cin >> V;
    // The number of edges is requested from the user.
    cout << "Enter the no of edges: ";
    cin >> E;

    // The number of vertices is validated to ensure it is non-negative.
    if (V < 0) {
        cout << "Give non-zero value of number of vertices" << endl;
        exit(1);
    }
    // The number of edges is validated to ensure it is within valid bounds.
    if (E < 0 || E > (V * (V - 1)) / 2) {
        cout << "Edge number should be between 0 to " << (V * (V - 1)) / 2 << endl;
        exit(1);
    }

    // An adjacency list for the graph is initialized.
    vector<int> adjList[V];
    int v1, v2;
    int edgeCount = 0;
    int start = 0;
    int finish = 0;
    vector<int> dfsForest[V];
    int dfsNo[V];
    int dfsCompletionNo[V];
    int visited[V];
    // The visited array, dfsNo, and dfsCompletionNo are initialized to zero.
    memset(visited, 0, sizeof(visited));
    memset(dfsNo, 0, sizeof(dfsNo));
    memset(dfsCompletionNo, 0, sizeof(dfsCompletionNo));

    // Edges are added to the graph until the specified number of edges is reached.
    while (edgeCount < E) {
        // The vertices for the edge are requested from the user.
        cout << "Enter first vertex of the edge to be added: ";
        cin >> v1;
        cout << "Enter second vertex of the edge to be added: ";
        cin >> v2;

        // Validation is performed to ensure the vertices are valid.
        if (v1 == v2) {
            cout << "Give different vertices as self loop is not considered" << endl;
        } else if (v1 < 1 || v1 > V || v2 < 1 || v2 > V) {
            cout << "Choose vertex between 1 to " << V << endl;
        } else if (search(adjList, v1, v2)) {
            // A check is performed to ensure the edge doesn't already exist.
            cout << "Edge already exists" << endl;
        } else {
            // The edge is added to the graph.
            addEdge(adjList, v1, v2);
            edgeCount++;
        }
    }

    int source;
    // The adjacency list is displayed.
    displayList(adjList, V);
    cout << "Enter the source vertex of dfs traversal. Choose between 1 to " << V << " " << endl;
    cin >> source;

    // The source vertex is validated to ensure it is within valid bounds.
    if (source < 1 || source > V) {
        cout << "Choose source vertex between 1 to " << V << endl;
        exit(1);
    }

    // DFS is performed starting from the source vertex.
    dfs(source - 1, visited, adjList, dfsForest[source - 1], start, finish, dfsNo, dfsCompletionNo);
    cout << "The corresponding dfs Tree is displayed along with the dfsNo and dfsCompletionNo" << endl;
    dfsTreeDisplay(source - 1, dfsForest, dfsNo, dfsCompletionNo);

    // DFS is performed on all unvisited vertices, and their DFS trees are displayed.
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, visited, adjList, dfsForest[i], start, finish, dfsNo, dfsCompletionNo);
            dfsTreeDisplay(i, dfsForest, dfsNo, dfsCompletionNo);
        }
    }
    return 0;
}
