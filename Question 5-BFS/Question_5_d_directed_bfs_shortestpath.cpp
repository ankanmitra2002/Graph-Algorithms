#include<bits/stdc++.h>
using namespace std;

// A function is defined to search for the existence of an edge between two vertices.
bool search(vector<int> adjList[], int v1, int v2) {
    // The adjacency list for vertex v1 is traversed.
    for (int i = 0; i < adjList[v1 - 1].size(); i++) {
        // If v2 is found in the adjacency list of v1, true is returned.
        if (adjList[v1 - 1][i] == v2 - 1) {
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

// A function is defined for performing BFS traversal and finding the path between the source and destination.
int bfs(int node, int destination, int visited[], vector<int> adjList[], int parent[]) {
    int distance = 0;
    visited[node] = 1;  // The source node is marked as visited.
    queue<int> q;
    q.push(node);  // The starting node is pushed into the queue.

    // The BFS loop is executed until the queue is empty.
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        // All unvisited neighbors of the current node are processed.
        for (int i = 0; i < adjList[curr].size(); i++) {
            int neighbour = adjList[curr][i];
            if (!visited[neighbour]) {
                visited[neighbour] = 1;  // The neighbor is marked as visited.
                q.push(neighbour);  // The neighbor is added to the queue.
                parent[neighbour] = curr;  // The current node is set as the parent of the neighbor.
                // If the destination node is reached, true is returned.
                if (neighbour == destination) {
                    return true;
                }
            }
        }
    }
    // If no path is found, false is returned.
    return false;
}

// A function is defined to display the shortest path from source to destination using the parent array.
int bfsTreePathDisplay(int source, int destination, int parent[]) {
    stack<int> st;
    int u = destination;
    st.push(u);  // The destination node is pushed onto the stack.

    // The parent chain is followed until the source node is reached.
    while (u != source) {
        u = parent[u];
        st.push(u);  // Each parent node is pushed onto the stack.
    }

    int distance = st.size() - 1;  // The distance is the size of the stack minus 1.
    
    // The path is displayed by popping nodes from the stack.
    while (!st.empty()) {
        cout << st.top() + 1 << "->";  // The node is printed (1-based index).
        st.pop();
    }
    return distance;  // The distance is returned.
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
    int parent[V];
    int visited[V];
    memset(visited, 0, sizeof(visited));  // The visited array is initialized to 0.
    parent[0] = -1;  // The source node has no parent.
    memset(parent, 0, sizeof(parent));  // The parent array is initialized to 0.

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

    int source, destination;
    displayList(adjList, V);  // The adjacency list is displayed.

    // The source and destination vertices for BFS traversal are input.
    cout << "Enter the distinct source vertex of bfs traversal. Choose between 1 to " << V << " " << endl;
    cin >> source;
    cout << "Enter the distinct destination vertex of bfs traversal. Choose between 1 to " << V << " " << endl;
    cin >> destination;

    // A check is performed to ensure the source and destination vertices are valid.
    if (source < 1 || source > V) {
        cout << "Choose source vertex between 1 to " << V << endl;
        exit(1);
    }
    if (destination < 1 || destination > V) {
        cout << "Choose destination vertex between 1 to " << V << endl;
        exit(1);
    }
    if (source == destination) {
        cout << "Choose distinct vertices" << endl;
        exit(1);
    }

    // The path between the source and destination is found using BFS.
    int isPath = bfs(source - 1, destination - 1, visited, adjList, parent);
    if (!isPath) {
        cout << "There is no path between " << source << " and " << destination << endl;
    } else {
        cout << "The corresponding path is: ";
        int distance = bfsTreePathDisplay(source - 1, destination - 1, parent);  // The shortest path is displayed.
        cout << "\nThe shortest distance between " << source << " and " << destination << ": " << distance << endl;
    }
    return 0;
}
