#include<bits/stdc++.h>
using namespace std;

// A function is defined to search if an edge exists between two vertices.
bool search(vector<int> adjList[], int v1, int v2) {
    // The adjacency list for vertex v1 is traversed.
    for(int i = 0; i < adjList[v1-1].size(); i++) {
        // If v2 is found in the adjacency list of v1, true is returned.
        if(adjList[v1-1][i] == v2-1) {
            return true;
        }
    }
    // If v2 is not found, false is returned.
    return false;
}

// A function is defined to add an edge between two vertices in the adjacency list.
void addEdge(vector<int> adjList[], int v1, int v2) {
    // Vertex v2 is added to the adjacency list of v1.
    adjList[v1 - 1].push_back(v2 - 1);
    // A message is displayed indicating that the edge has been added.
    cout << "Edge added between " << v1 << " and " << v2 << endl;
}

// A function is defined to display the adjacency list of the graph.
void displayList(vector<int> adjList[], int V) {
    cout << "The adjacency List is:" << endl;
    // Each vertex's adjacency list is displayed.
    for (int i = 0; i < V; i++) {
        cout << i + 1 << ": ";
        // The adjacency list is sorted.
        sort(adjList[i].begin(), adjList[i].end());
        // Each neighbor of the vertex is printed.
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << adjList[i][j] + 1 << ", ";
        }
        cout << endl;
    }
}

// A function is defined for performing BFS traversal starting from a node.
void bfs(int node, int visited[], vector<int> adjList[], vector<int>& bfsTree) {
    visited[node] = 1;  // The node is marked as visited.
    queue<int> q;
    q.push(node);  // The starting node is pushed into the queue.
    // The BFS loop is executed until the queue is empty.
    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        // The current node is added to the BFS tree.
        bfsTree.push_back(curr);
        // All unvisited neighbors of the current node are processed.
        for(int i = 0; i < adjList[curr].size(); i++) {
            int neighbour = adjList[curr][i];
            if(!visited[neighbour]) {
                visited[neighbour] = 1;  // The neighbor is marked as visited.
                q.push(neighbour);  // The neighbor is added to the queue.
            }
        }
    }
}

// A function is defined to display the BFS tree of a node.
void bfsTreeDisplay(int node, vector<int> bfsForest[]) {
    cout << node + 1;  // The current node is printed.
    // The BFS tree for the node is displayed.
    for(int i = 1; i < bfsForest[node].size(); i++) {
        int u = bfsForest[node][i];
        cout << "->" << u + 1 << " ";
    }
    cout << endl;
}

int main() {
    int V, E;
    // The number of vertices is input.
    cout << "Enter the no of vertices: ";
    cin >> V;
    // The number of edges is input.
    cout << "Enter the no of edges: ";
    cin >> E;

    // A check is performed to ensure that the number of vertices is positive.
    if (V < 0) {
        cout << "Give non-zero value of number of vertices" << endl;
        exit(1);
    }
    // A check is performed to ensure that the number of edges is within the valid range.
    if (E < 0 || E > (V * (V - 1)) / 2) {
        cout << "Edge number should be between 0 to " << (V * (V - 1)) / 2 << endl;
        exit(1);
    }

    // An adjacency list array is initialized.
    vector<int> adjList[V];
    int v1, v2;
    int edgeCount = 0;
    // A BFS forest is created for each node.
    vector<int> bfsForest[V];
    // A visited array is initialized to keep track of visited nodes.
    int visited[V];
    memset(visited, 0, sizeof(visited));

    // Edges are added until the specified number of edges is reached.
    while (edgeCount < E) {
        cout << "Enter first vertex of the edge to be added: ";
        cin >> v1;
        cout << "Enter second vertex of the edge to be added: ";
        cin >> v2;

        // Checks are performed to ensure valid vertices and avoid self-loops or duplicate edges.
        if (v1 == v2) {
            cout << "Give different vertices as self loop is not considered" << endl;
        } else if (v1 < 1 || v1 > V || v2 < 1 || v2 > V) {
            cout << "Choose vertex between 1 to " << V << endl;
        } else if (search(adjList, v1, v2)) {
            cout << "Edge already exists" << endl;
        } else {
            addEdge(adjList, v1, v2);  // The edge is added to the graph.
            edgeCount++;
        }
    }

    int source;
    displayList(adjList, V);  // The adjacency list is displayed.

    // The source vertex for BFS traversal is input.
    cout << "Enter the source vertex of bfs traversal. Choose between 1 to " << V << " " << endl;
    cin >> source;

    // A check is performed to ensure the source vertex is valid.
    if (source < 1 || source > V) {
        cout << "Choose source vertex between 1 to " << V << endl;
    }

    // BFS traversal is performed starting from the source vertex.
    bfs(source - 1, visited, adjList, bfsForest[source - 1]);
    cout << "The corresponding bfs Tree is displayed:" << endl;
    bfsTreeDisplay(source - 1, bfsForest);

    // BFS is performed for all unvisited nodes in the graph.
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            bfs(i, visited, adjList, bfsForest[i]);
            bfsTreeDisplay(i, bfsForest);  // The BFS tree is displayed for each unvisited node.
        }
    }

    return 0;
}
