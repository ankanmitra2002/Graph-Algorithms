#include<bits/stdc++.h>
using namespace std;

// The search function is used to check if an edge exists between two vertices.
bool search(vector<int> adjList[], int v1, int v2) {
    // The adjacency list of vertex v1 is iterated to find if v2 is present.
    for (int i = 0; i < adjList[v1-1].size(); i++) {
        // If a match is found, true is returned.
        if (adjList[v1-1][i] == v2-1) {
            return true;
        }
    }
    // If no match is found, false is returned.
    return false;
}

// An edge is added between two vertices in the adjacency list.
void addEdge(vector<int> adjList[], int v1, int v2) {
    // Both v1 and v2 are added to each other's adjacency list.
    adjList[v1 - 1].push_back(v2-1);
    adjList[v2 - 1].push_back(v1-1);
    // A message is displayed confirming the edge has been added.
    cout << "Edge added between " << v1 << " and " << v2 << endl;
}

// The adjacency list is displayed.
void displayList(vector<int> adjList[], int V) {
    // A message is printed indicating that the adjacency list is being displayed.
    cout << "The adjacency List is:" << endl;
    for (int i = 0; i < V; i++) {
        cout << i+1 << ": ";
        // The adjacency list for vertex i is sorted to ensure ordered traversal.
        sort(adjList[i].begin(), adjList[i].end());
        for (int j = 0; j < adjList[i].size(); j++) {
            // Each vertex in the adjacency list is printed.
            cout << adjList[i][j] + 1 << ", ";
        }
        cout << endl;
    }
}

// Depth-First Search (DFS) is performed on the graph to explore nodes.
void dfs(int node, int visited[], vector<int> adjList[], vector<int>& dfsTree, 
         int& start, int& finish, int dfsNo[], int dfsCompletionNo[]) {
    // The node is marked as visited.
    visited[node] = 1;
    // The node is added to the DFS tree.
    dfsTree.push_back(node);
    // The start time of the node is recorded.
    dfsNo[node] = ++start;
    for (int i = 0; i < adjList[node].size(); i++) {
        // If a node has not been visited, DFS is called recursively on it.
        if (!visited[adjList[node][i]]) {
            dfs(adjList[node][i], visited, adjList, dfsTree, start, finish, dfsNo, dfsCompletionNo);
        }
    }
    // The finish time of the node is recorded after visiting all adjacent nodes.
    dfsCompletionNo[node] = ++finish;
}

// The DFS tree is displayed along with the discovery and completion times.
void dfsTreeDisplay(int node, vector<int> dfsForest[], int dfsNo[], int dfsCompletionNo[]) {
    // The node and its discovery and completion times are printed.
    cout << node + 1 << "(" << dfsNo[node] << "/" << dfsCompletionNo[node] << ")" << " ";
    for (int i = 1; i < dfsForest[node].size(); i++) {
        int u = dfsForest[node][i];
        // Each adjacent node's discovery and completion times are printed.
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

    // Validation is performed to ensure the number of vertices is non-negative.
    if (V < 0) {
        cout << "Give non-zero value of number of vertices" << endl;
        exit(1);
    }
    // Validation is performed to ensure the number of edges is within valid bounds.
    if (E < 0 || E > (V * (V - 1)) / 2) {
        cout << "Edge number should be between 0 to " << (V * (V - 1)) / 2 << endl;
        exit(1);
    }

    // An adjacency list is created for the graph.
    vector<int> adjList[V];
    int v1, v2;
    int edgeCount = 0;
    int start = 0;
    int finish = 0;
    vector<int> dfsForest[V];
    int dfsNo[V];
    int dfsCompletionNo[V];
    int visited[V];
    // The visited, dfsNo, and dfsCompletionNo arrays are initialized to zero.
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
        
        // Validation is performed to ensure the vertices are not the same and within valid bounds.
        if (v1 == v2) {
            cout << "Give different vertices as self loop is not considered" << endl;
        } else if (v1 < 1 || v1 > V || v2 < 1 || v2 > V) {
            cout << "Choose vertex between 1 to " << V << endl;
        } else if (search(adjList, v1, v2)) {
            // A check is performed to see if the edge already exists.
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
    
    // Validation is performed to ensure the source vertex is within valid bounds.
    if (source < 1 || source > V) {
        cout << "Choose source vertex between 1 to " << V << endl;
        exit(1);
    }
    
    // DFS is performed starting from the source vertex.
    dfs(source - 1, visited, adjList, dfsForest[source - 1], start, finish, dfsNo, dfsCompletionNo);
    cout << "The corresponding dfs Tree is displayed along with the dfsNo and dfsCompletionNo" << endl;
    dfsTreeDisplay(source - 1, dfsForest, dfsNo, dfsCompletionNo);
    
    // DFS is performed on unvisited vertices and their DFS trees are displayed.
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, visited, adjList, dfsForest[i], start, finish, dfsNo, dfsCompletionNo);
            dfsTreeDisplay(i, dfsForest, dfsNo, dfsCompletionNo);
        }
    }
    return 0;
}
