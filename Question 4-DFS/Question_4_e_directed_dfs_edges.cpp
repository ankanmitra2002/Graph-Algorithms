#include<bits/stdc++.h>
using namespace std;

bool search(vector<int> adjList[], int v1, int v2) {
    // The adjacency list is searched to check if an edge exists between v1 and v2
    for (int i = 0; i < adjList[v1 - 1].size(); i++) {
        if (adjList[v1 - 1][i] == v2 - 1) {
            return true;
        }
    }
    return false;
}

void addEdge(vector<int> adjList[], int v1, int v2) {
    // An edge is added between v1 and v2 in the adjacency list
    adjList[v1 - 1].push_back(v2 - 1);
    cout << "Edge added between " << v1 << " and " << v2 << endl;
}

void displayList(vector<int> adjList[], int V) {
    // The adjacency list is displayed
    cout << "The adjacency List is:" << endl;
    for (int i = 0; i < V; i++) {
        cout << i + 1 << ": ";
        sort(adjList[i].begin(), adjList[i].end());
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << adjList[i][j] + 1 << ", ";
        }
        cout << endl;
    }
}

void dfs(int node, int visited[], vector<int> adjList[], int parent[], vector<int>& dfsTree, int& start, int& finish, int dfsNo[], int dfsCompletionNo[]) {
    // The node is marked as visited and added to the DFS tree
    visited[node] = 1;
    dfsTree.push_back(node);
    dfsNo[node] = ++start;
    for (int i = 0; i < adjList[node].size(); i++) {
        if (!visited[adjList[node][i]]) {
            // The DFS function is recursively called for unvisited neighbors
            parent[adjList[node][i]] = node;
            dfs(adjList[node][i], visited, adjList, parent, dfsTree, start, finish, dfsNo, dfsCompletionNo);
        }
    }
    dfsCompletionNo[node] = ++finish;
}

void dfsTreeDisplay(int node, vector<int> dfsForest[], int dfsNo[], int dfsCompletionNo[]) {
    // The DFS tree is displayed with dfsNo and dfsCompletionNo
    cout << node + 1 << "(" << dfsNo[node] << "/" << dfsCompletionNo[node] << ")" << " ";
    for (int i = 1; i < dfsForest[node].size(); i++) {
        int u = dfsForest[node][i];
        cout << "->" << u + 1 << "(" << dfsNo[u] << "/" << dfsCompletionNo[u] << ")" << " ";
    }
    cout << endl;
}

void classifyEdges(vector<int> adjList[], int V, int dfsNo[], int dfsCompletionNo[], int parent[], vector<pair<int, int>>& Treeedges, vector<pair<int, int>>& Forwardedges, vector<pair<int, int>>& Backedges, vector<pair<int, int>>& Crossedges) {
    // The edges are classified into Tree, Forward, Back, and Cross edges based on DFS numbers
    for (int node = 0; node < V; node++) {
        for (int j = 0; j < adjList[node].size(); j++) {
            int neighbour = adjList[node][j];
            if (parent[neighbour] == node) {
                // Tree edges are added to Treeedges
                Treeedges.push_back({node, neighbour});
            } else {
                if (dfsNo[neighbour] > dfsNo[node]) {
                    // Forward edges are added to Forwardedges
                    Forwardedges.push_back({node, neighbour});
                } else if (dfsNo[neighbour] < dfsNo[node] && dfsCompletionNo[neighbour] > dfsCompletionNo[node]) {
                    // Back edges are added to Backedges
                    Backedges.push_back({node, neighbour});
                } else {
                    // Cross edges are added to Crossedges
                    Crossedges.push_back({node, neighbour});
                }
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

    vector<int> adjList[V];
    int v1, v2;
    int edgeCount = 0;
    int start = 0;
    int finish = 0;
    vector<int> dfsForest[V];
    int dfsNo[V];
    int dfsCompletionNo[V];
    int visited[V];
    int parent[V];
    memset(parent, -1, sizeof(parent));
    memset(visited, 0, sizeof(visited));
    memset(dfsNo, 0, sizeof(dfsNo));
    memset(dfsCompletionNo, 0, sizeof(dfsCompletionNo));

    vector<pair<int, int>> Treeedges, Backedges, Forwardedges, Crossedges;

    while (edgeCount < E) {
        cout << "Enter the first vertex of the edge to be added: ";
        cin >> v1;
        cout << "Enter the second vertex of the edge to be added: ";
        cin >> v2;
        if (v1 == v2) {
            cout<<"Give different vertices as self loop is not considered"<<endl;
        } else if (v1 < 1 || v1 > V || v2 < 1 || v2 > V) {
            cout << "Vertices should be chosen between 1 and " << V << endl;
        } else if (search(adjList, v1, v2)) {
            cout << "The edge already exists." << endl;
        } else {
            // An edge is added between v1 and v2
            addEdge(adjList, v1, v2);
            edgeCount++;
        }
    }

    int source;
    displayList(adjList, V);
    cout << "Enter the source vertex for DFS traversal. Choose between 1 and " << V << ": ";
    cin >> source;
    if (source < 1 || source > V) {
        cout << "Please choose a source vertex between 1 and " << V << endl;
        exit(1);
    }

    // The DFS traversal is started from the source node
    dfs(source - 1, visited, adjList, parent, dfsForest[source - 1], start, finish, dfsNo, dfsCompletionNo);
    cout << "The corresponding DFS tree is displayed along with the dfsNo and dfsCompletionNo" << endl;
    dfsTreeDisplay(source - 1, dfsForest, dfsNo, dfsCompletionNo);

    // The DFS is completed for all other unvisited nodes
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, visited, adjList, parent, dfsForest[i], start, finish, dfsNo, dfsCompletionNo);
            dfsTreeDisplay(i, dfsForest, dfsNo, dfsCompletionNo);
        }
    }

    classifyEdges(adjList, V, dfsNo, dfsCompletionNo, parent, Treeedges, Forwardedges, Backedges, Crossedges);

    // The classified edges are displayed
    cout << "\nTree edges are - {";
    for (int i = 0; i < Treeedges.size(); i++) {
        int u = Treeedges[i].first;
        int v = Treeedges[i].second;
        cout << "(" << u + 1 << "," << v + 1 << ") ";
    }
    cout << "}";

    cout << "\nForward edges are {";
    for (int i = 0; i < Forwardedges.size(); i++) {
        int u = Forwardedges[i].first;
        int v = Forwardedges[i].second;
        cout << "(" << u + 1 << "," << v + 1 << "), ";
    }
    cout << "}";

    cout << "\nBack edges are - {";
    for (int i = 0; i < Backedges.size(); i++) {
        int u = Backedges[i].first;
        int v = Backedges[i].second;
        cout << "(" << u + 1 << "," << v + 1 << "), ";
    }
    cout << "}";

    cout << "\nCross edges are - {";
    for (int i = 0; i < Crossedges.size(); i++) {
        int u = Crossedges[i].first;
        int v = Crossedges[i].second;
        cout << "(" << u + 1 << "," << v + 1 << "), ";
    }
    cout << "}";

    return 0;
}
