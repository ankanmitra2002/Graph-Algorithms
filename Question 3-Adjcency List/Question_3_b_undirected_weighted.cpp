#include <iostream>
#include <vector>
using namespace std;
// Representation of undirected weighted graph using adjacency list
// Function to check if an edge exists between two vertices
bool search(vector<pair<int,int>> adjList[], int v1, int v2) {
    // The adjacency list of vertex v1 is searched to see if vertex v2 is present
    for (int i = 0; i < adjList[v1 - 1].size(); i++) {
        if (adjList[v1 - 1][i].first == v2 - 1) {
            return true; // If the edge is found, true is returned
        }
    }
    return false; // If no edge exists, false is returned
}

// Function to add an edge between two vertices in the graph with a specified weight
void addEdge(vector<pair<int,int>> adjList[], int v1, int v2, int weight) {
    // An edge is added between vertex v1 and vertex v2 with the specified weight
    adjList[v1 - 1].push_back({v2 - 1, weight});
    adjList[v2 - 1].push_back({v1 - 1, weight});
    cout << "Edge added between " << v1 << " and " << v2 << " with weight " << weight << endl;
}

// Function to remove an edge between two vertices in the graph
void removeEdge(vector<pair<int,int>> adjList[], int v1, int v2) {
    // The edge from v1 to v2 is removed from the adjacency list of vertex v1
    for (int i = 0; i < adjList[v1 - 1].size(); i++) {
        if (adjList[v1 - 1][i].first == v2 - 1) {
            adjList[v1 - 1].erase(adjList[v1 - 1].begin() + i);
            break; // The loop is exited after the edge is removed
        }
    }
    // The edge from v2 to v1 is removed from the adjacency list of vertex v2
    for (int i = 0; i < adjList[v2 - 1].size(); i++) {
        if (adjList[v2 - 1][i].first == v1 - 1) {
            adjList[v2 - 1].erase(adjList[v2 - 1].begin() + i);
            break; // The loop is exited after the edge is removed
        }
    }
    cout << "Edge removed between " << v1 << " and " << v2 << endl;
}

// Function to display the adjacency list of the graph
void displayList(vector<pair<int,int>> adjList[], int V) {
    // The adjacency list for each vertex is printed
    cout << "The adjacency List is:" << endl;
    for (int i = 0; i < V; i++) {
        cout << i + 1 << ": "; // Vertex number is printed (1-based index)
        // Each adjacent vertex and its corresponding edge weight is printed
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << "->{" << adjList[i][j].first + 1 << " weight-" << adjList[i][j].second << "} ";
        }
        cout << endl;
    }
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V; // The number of vertices is taken as input from the user

    // The number of vertices is validated to ensure it's greater than 0
    if (V < 0) {
        cout << "Give non-zero value of number of vertices" << endl;
        exit(1); // The program terminates if the number of vertices is invalid
    }

    vector<pair<int,int>> adjList[V]; // The adjacency list for the graph is created

    int choice;
    do {
        // Menu for user interaction
        cout << "\n**********Menu:***********\n\n\n";
        cout << "Enter 1. Add Edge\n";
        cout << "Enter 2. Remove Edge\n";
        cout << "Enter 3. Display Adjacency List\n";
        cout << "Enter 4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        int v1, v2, weight;
        switch (choice) {
            case 1:
                // Edge addition process
                cout << "Enter first vertex of the edge to be added: ";
                cin >> v1;
                cout << "Enter second vertex of the edge to be added: ";
                cin >> v2;
                cout << "Enter the non-zero weight of the edge: ";
                cin >> weight;

                // Validations for input weight and vertices
                if (weight == 0) {
                    cout << "The weight should be non-zero" << endl;
                } else if (v1 == v2) {
                    cout << "Give different vertices as self-loop is not considered" << endl;
                } else if (v1 < 1 || v1 > V || v2 < 1 || v2 > V) {
                    cout << "Choose vertex between 1 to " << V << endl;
                } else if (search(adjList, v1, v2)) {
                    cout << "Edge already exists" << endl; // Edge exists, no addition
                } else {
                    addEdge(adjList, v1, v2, weight); // Edge is added if all checks are passed
                }
                break;
            case 2:
                // Edge removal process
                cout << "Enter first vertex of the edge to be removed: ";
                cin >> v1;
                cout << "Enter second vertex of the edge to be removed: ";
                cin >> v2;

                // Validations for input vertices
                if (v1 < 1 || v1 > V || v2 < 1 || v2 > V) {
                    cout << "Choose vertex between 1 to " << V << endl;
                } else if (!search(adjList, v1, v2)) {
                    cout << "Edge doesn't exist" << endl; // If the edge doesn't exist
                } else {
                    removeEdge(adjList, v1, v2); // Edge is removed if it exists
                }
                break;
            case 3:
                // Display the adjacency list
                displayList(adjList, V);
                break;
            case 4:
                // Exit message
                cout << "The program has finished" << endl;
                displayList(adjList, V); // Display the adjacency list before finishing
                break;
            default:
                // Invalid choice handling
                cout << "Invalid choice. Please choose between (1-4)." << endl;
                break;
        }
    } while (choice != 4); // Loop continues until the user chooses to exit

    return 0;
}
