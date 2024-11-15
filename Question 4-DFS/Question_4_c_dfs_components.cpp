#include<bits/stdc++.h>
using namespace std;

// The function is used to search for an edge between two vertices.
bool search(vector<int> adjList[], int v1, int v2) {
    // The adjacency list for vertex v1 is iterated to check if v2 is present.
    for (int i = 0; i < adjList[v1-1].size(); i++) {
        // If an edge is found, true is returned.
        if (adjList[v1-1][i] == v2-1) {
            return true;
        }
    }
    // If no edge is found, false is returned.
    return false;
}

// An edge is added between two vertices in the adjacency list.
void addEdge(vector<int> adjList[], int v1, int v2) {
    // The adjacency list for both vertices is updated.
    adjList[v1 - 1].push_back(v2-1);
    adjList[v2 - 1].push_back(v1-1);
    // A confirmation message is displayed.
    cout << "Edge added between " << v1 << " and " << v2 << endl;
}

// The adjacency list is displayed.
void displayList(vector<int> adjList[], int V) {
    cout << "The adjacency List is:" << endl;
    // Each vertex's adjacency list is displayed after sorting.
    for (int i = 0; i < V; i++) {
        cout << i + 1 << ": ";
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
    // The node is added to the DFS tree.
    dfsTree.push_back(node);
    // The discovery time of the node is recorded.
    dfsNo[node] = ++start;
    // Each adjacent node is visited recursively if not already visited.
    for (int i = 0; i < adjList[node].size(); i++) {
        if (!visited[adjList[node][i]]) {
            // DFS is called on the unvisited adjacent node.
            dfs(adjList[node][i], visited, adjList, dfsTree, start, finish, dfsNo, dfsCompletionNo);
        }
    }
    // The finish time of the node is recorded.
    dfsCompletionNo[node] = ++finish;
}

// The DFS tree is displayed along with discovery and completion times.
void dfsTreeDisplay(int node, vector<int> dfsForest[], int dfsNo[], int dfsCompletionNo[]) {
    // The current node is displayed along with its discovery and completion times.
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

    // The number of vertices is validated to ensure it is positive.
    if (V < 0) {
        cout << "Give non-zero value of number of vertices" << endl;
        exit(1);
    }
    // The number of edges is validated to ensure it is within valid bounds.
    if (E < 0 || E > (V * (V - 1)) / 2) {
        cout << "Edge number should be between 0 to " << (V * (V - 1)) / 2 << endl;
        exit(1);
    }

    // The adjacency list for the graph is initialized.
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

        // The input is validated to ensure valid vertices.
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

    // The adjacency list is displayed.
    displayList(adjList, V);

    cout << "The components are displayed along with the dfsNo and dfsCompletionNo" << endl;
    int components = 0;
    // DFS is performed for each component in the graph.
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            components++;
            cout << "component " << components << ": ";
            // DFS is called on each unvisited node, and the DFS tree is displayed.
            dfs(i, visited, adjList, dfsForest[i], start, finish, dfsNo, dfsCompletionNo);
            dfsTreeDisplay(i, dfsForest, dfsNo, dfsCompletionNo);
        }
    }
    // The total number of components is displayed.
    cout << "The number of components are - " << components << endl;
    return 0;
}
