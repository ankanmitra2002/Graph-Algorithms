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
    // An edge is added between v1 and v2 (undirected edge)
    adjList[v1 - 1].push_back(v2 - 1);
    adjList[v2 - 1].push_back(v1 - 1);
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

void bfs(int node, int visited[], vector<int> adjList[], vector<int>& bfsTree) {
    // The node is marked as visited and added to the queue
    visited[node] = 1;
    queue<int> q;
    q.push(node);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        bfsTree.push_back(curr);
        for (int i = 0; i < adjList[curr].size(); i++) {
            int neighbour = adjList[curr][i];
            if (!visited[neighbour]) {
                // The neighbor is marked as visited and pushed to the queue
                visited[neighbour] = 1;
                q.push(neighbour);
            }
        }
    }
}

void bfsTreeDisplay(int node, vector<int> bfsForest[]) {
    // The BFS tree is displayed
    cout << node + 1;
    for (int i = 1; i < bfsForest[node].size(); i++) {
        int u = bfsForest[node][i];
        cout << "->" << u + 1 << " ";
    }
    cout << endl;
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
    vector<int> bfsForest[V];
    int visited[V];
    memset(visited, 0, sizeof(visited));

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
    cout << "Enter the source vertex for BFS traversal. Choose between 1 and " << V << ": ";
    cin >> source;
    if (source < 1 || source > V) {
        cout << "Please choose a source vertex between 1 and " << V << endl;
    }

    // The BFS traversal is started from the source node
    bfs(source - 1, visited, adjList, bfsForest[source - 1]);
    cout << "The corresponding BFS Tree is displayed:" << endl;
    bfsTreeDisplay(source - 1, bfsForest);

    // The BFS traversal is completed for all other unvisited nodes
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            bfs(i, visited, adjList, bfsForest[i]);
            bfsTreeDisplay(i, bfsForest);
        }
    }

    return 0;
}
