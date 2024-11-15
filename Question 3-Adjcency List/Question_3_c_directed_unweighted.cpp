#include <iostream>
#include <vector>
using namespace std;
// Representation of directed unweighted graph using adjacency list
// Function to search for an edge between two vertices
bool search(vector<int> adjList[], int v1, int v2) {
    // The adjacency list of vertex v1 is searched to check if v2 is an adjacent vertex
    for (int i = 0; i < adjList[v1 - 1].size(); i++) {
        if (adjList[v1 - 1][i] == v2 - 1) {
            return true; // If the edge is found, true is returned
        }
    }
    return false; // If no edge exists, false is returned
}

// Function to add an edge between two vertices in the graph
void addEdge(vector<int> adjList[], int v1, int v2) {
    // The edge from vertex v1 to v2 is added to the adjacency list of v1
    adjList[v1 - 1].push_back(v2 - 1);
    cout << "Edge added between " << v1 << " and " << v2 << endl;
}

// Function to remove an edge between two vertices in the graph
void removeEdge(vector<int> adjList[], int v1, int v2) {
    // The edge from v1 to v2 is removed from the adjacency list of vertex v1
    for (int i = 0; i < adjList[v1 - 1].size(); i++) {
        if (adjList[v1 - 1][i] == v2 - 1) {
            adjList[v1 - 1].erase(adjList[v1 - 1].begin() + i);
            break; // The edge is removed and the loop is exited
        }
    }
    cout << "Edge removed between " << v1 << " and " << v2 << endl;
}

// Function to display the adjacency list of the graph
void displayList(vector<int> adjList[], int V) {
    // The adjacency list for each vertex is printed
    cout << "The adjacency List is:" << endl;
    for (int i = 0; i < V; i++) {
        cout << i + 1 << ": "; // Vertex number is printed (1-based index)
        // Each adjacent vertex is printed for the current vertex
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << "->" << adjList[i][j] + 1 << " "; // Adjacency is printed as 1-based index
        }
        cout << endl;
    }
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V; // The number of vertices is taken as input from the user

    // The number of vertices is validated to ensure it's a valid value
    if (V < 0) {
        cout << "Give non-zero value of number of vertices" << endl;
        exit(1); // The program terminates if the number of vertices is invalid
    }

    vector<int> adjList[V]; // The adjacency list for the graph is created

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

        int v1, v2;
        switch (choice) {
            case 1:
                // Edge addition process
                cout << "Enter first vertex of the edge to be added: ";
                cin >> v1;
                cout << "Enter second vertex of the edge to be added: ";
                cin >> v2;

                // Validations for input vertices
                if (v1 == v2) {
                    cout << "Give different vertices as self-loop is not considered" << endl;
                } else if (v1 < 1 || v1 > V || v2 < 1 || v2 > V) {
                    cout << "Choose vertex between 1 to " << V << endl;
                } else if (search(adjList, v1, v2)) {
                    cout << "Edge already exists" << endl; // Edge already exists, no addition
                } else {
                    addEdge(adjList, v1, v2); // The edge is added if all checks pass
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
                    removeEdge(adjList, v1, v2); // The edge is removed if it exists
                }
                break;

            case 3:
                // Display the adjacency list
                displayList(adjList, V);
                break;

            case 4:
                // Exit message
                cout << "The program has finished" << endl;
                displayList(adjList, V); // The final adjacency list is displayed before exiting
                break;

            default:
                // Invalid choice handling
                cout << "Invalid choice. Please choose between (1-4)." << endl;
                break;
        }
    } while (choice != 4); // The loop continues until the user chooses to exit

    return 0;
}
