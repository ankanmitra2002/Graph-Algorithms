#include<bits/stdc++.h>
using namespace std;

// The function checks if an edge exists between v1 and v2 in the adjacency list.
bool search(vector<int> adjList[], int v1, int v2) {
    for (int i = 0; i < adjList[v1 - 1].size(); i++) {
        if (adjList[v1 - 1][i] == v2 - 1) {
            return true;
        }
    }
    return false;
}

// An edge is added between vertices v1 and v2 in the graph.
void addEdge(vector<int> adjList[], int v1, int v2) {
    adjList[v1 - 1].push_back(v2 - 1);
    adjList[v2 - 1].push_back(v1 - 1);
    cout << "Edge added between " << v1 << " and " << v2 << endl;
}

// The adjacency list is displayed with the vertices and their neighbors sorted.
void displayList(vector<int> adjList[], int V) {
    cout << "The adjacency List is:" << endl;
    for (int i = 0; i < V; i++) {
        cout << i + 1 << ": ";
        sort(adjList[i].begin(), adjList[i].end());  // The neighbors are sorted for easy viewing.
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << adjList[i][j] + 1 << ", ";  // Each neighbor is printed, adjusted back to 1-based index.
        }
        cout << endl;
    }
}

// The DFS function is executed to explore the graph starting from a given node.
void dfs(int node, int visited[], vector<int> adjList[], int parent[], vector<int>& dfsTree, int& start, int& finish, int dfsNo[], int dfsCompletionNo[]) {
    visited[node] = 1;  // The current node is marked as visited.
    dfsTree.push_back(node);  // The node is added to the DFS tree.
    dfsNo[node] = ++start;  // The start time is recorded for the node.
    
    for (int i = 0; i < adjList[node].size(); i++) {
        if (!visited[adjList[node][i]]) {
            // The DFS is recursively called for unvisited neighbors.
            dfs(adjList[node][i], visited, adjList, parent, dfsTree, start, finish, dfsNo, dfsCompletionNo);
            parent[adjList[node][i]] = node;  // The parent of the neighbor is set.
        }
    }
    
    dfsCompletionNo[node] = ++finish;  // The finish time is recorded for the node.
}

// The DFS tree is displayed along with the discovery and finish times for each node.
void dfsTreeDisplay(int node, vector<int> dfsForest[], int dfsNo[], int dfsCompletionNo[]) {
    cout << node + 1 << "(" << dfsNo[node] << "/" << dfsCompletionNo[node] << ")" << " ";
    for (int i = 1; i < dfsForest[node].size(); i++) {
        int u = dfsForest[node][i];
        cout << "->" << u + 1 << "(" << dfsNo[u] << "/" << dfsCompletionNo[u] << ")" << " ";
    }
    cout << endl;
}

// The edges of the graph are classified into tree edges, forward edges, and back edges.
void classifyEdges(vector<int> adjList[], int V, int dfsNo[], int dfsCompletionNo[], int parent[], vector<pair<int, int>>& Treeedges, vector<pair<int, int>>& Forwardedges, vector<pair<int, int>>& Backedges) {
    for (int node = 0; node < V; node++) {
        for (int j = 0; j < adjList[node].size(); j++) {
            int neighbour = adjList[node][j];
            
            if (parent[neighbour] == node) {
                // Tree edges are classified.
                Treeedges.push_back({node, neighbour});
                Backedges.push_back({neighbour, node});
            }
            else if (dfsNo[neighbour] > dfsNo[node] && dfsCompletionNo[node] > dfsCompletionNo[neighbour]) {
                // Forward edges are classified.
                Forwardedges.push_back({node, neighbour});
                Backedges.push_back({neighbour, node});
            }
        }
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;
    if (V < 0) {
        cout << "A non-zero value for the number of vertices is required" << endl;
        exit(1);
    }
    if (E < 0 || E > (V * (V - 1)) / 2) {
        cout << "The number of edges should be between 0 and " << (V * (V - 1)) / 2 << endl;
        exit(1);
    }
    vector<int> adjList[V];  // The adjacency list is initialized for V vertices.
    int v1, v2;
    int edgeCount = 0;  // The count of edges is initialized.
    int start = 0, finish = 0;  // The start and finish counters for DFS are initialized.
    vector<int> dfsForest[V];  // A separate DFS tree is maintained for each node.
    int dfsNo[V], dfsCompletionNo[V], visited[V], parent[V];

    // Arrays are initialized with default values.
    memset(parent, -1, sizeof(parent));
    memset(visited, 0, sizeof(visited));
    memset(dfsNo, 0, sizeof(dfsNo));
    memset(dfsCompletionNo, 0, sizeof(dfsCompletionNo));

    // Vectors for storing the different types of edges.
    vector<pair<int, int>> Treeedges, Forwardedges, Backedges;

    // Edge input loop.
    while (edgeCount < E) {
        cout << "Enter first vertex of the edge to be added: ";
        cin >> v1;
        cout << "Enter second vertex of the edge to be added: ";
        cin >> v2;

        if (v1 == v2) {
            cout << "Self-loop is not allowed." << endl;  // Self-loops are not allowed.
        } else if (v1 < 1 || v1 > V || v2 < 1 || v2 > V) {
            cout << "Vertices must be between 1 and " << V << endl;  // Vertex range check.
        } else if (search(adjList, v1, v2)) {
            cout << "Edge already exists." << endl;  // Duplicate edge check.
        } else {
            // Edge is added to the graph.
            addEdge(adjList, v1, v2);
            edgeCount++;
        }
    }

    int source;
    displayList(adjList, V);  // Display the adjacency list.

    // The source vertex for DFS is input.
    cout << "Enter the source vertex of DFS traversal. Choose between 1 to " << V << ": ";
    cin >> source;

    // Source vertex validation.
    if (source < 1 || source > V) {
        cout << "Choose a valid source vertex between 1 and " << V << endl;
        exit(1);  // Exit if the source vertex is invalid.
    }

    // DFS traversal is started from the source vertex.
    dfs(source - 1, visited, adjList, parent, dfsForest[source - 1], start, finish, dfsNo, dfsCompletionNo);

    cout << "The corresponding DFS tree is displayed along with the dfsNo and dfsCompletionNo:" << endl;
    dfsTreeDisplay(source - 1, dfsForest, dfsNo, dfsCompletionNo);

    // DFS traversal is performed for all unvisited nodes in the graph.
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, visited, adjList, parent, dfsForest[i], start, finish, dfsNo, dfsCompletionNo);
            dfsTreeDisplay(i, dfsForest, dfsNo, dfsCompletionNo);
        }
    }

    // The edges are classified into tree, forward, and back edges.
    classifyEdges(adjList, V, dfsNo, dfsCompletionNo, parent, Treeedges, Forwardedges, Backedges);

    // The classified edges are displayed.
    cout << "\nTree edges are - {";
    for (int i = 0; i < Treeedges.size(); i++) {
        int u = Treeedges[i].first;
        int v = Treeedges[i].second;
        cout << "{" << u + 1 << ", " << v + 1 << "}, ";
    }
    cout << "}" << endl;

    cout << "\nForward edges are - {";
    for (int i = 0; i < Forwardedges.size(); i++) {
        int u = Forwardedges[i].first;
        int v = Forwardedges[i].second;
        cout << "{" << u + 1 << ", " << v + 1 << "}, ";
    }
    cout << "}" << endl;

    cout << "\nBack edges are - {";
    for (int i = 0; i < Backedges.size(); i++) {
        int u = Backedges[i].first;
        int v = Backedges[i].second;
        cout << "{" << u + 1 << ", " << v + 1 << "}, ";
    }
    cout << "}" << endl;

    return 0;
}
