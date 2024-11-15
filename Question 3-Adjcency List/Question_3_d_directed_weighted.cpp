#include <iostream>
#include <vector>
using namespace std;
// Representation of directed weighted graph using adjacency list
// Function to search if an edge exists between v1 and v2
bool search(vector<pair<int,int>> adjList[], int v1, int v2) {
    // The adjacency list of vertex v1 is searched to check if v2 exists as a neighbor
    for (int i = 0; i < adjList[v1 - 1].size(); i++) {
        if (adjList[v1 - 1][i].first == v2 - 1) {
            return true; // If v2 is found as a neighbor, true is returned
        }
    }
    return false; // If no edge exists, false is returned
}

// Function to add an edge with a given weight between v1 and v2
void addEdge(vector<pair<int,int>> adjList[], int v1, int v2, int weight) {
    // The edge is added from v1 to v2 with the given weight 
    adjList[v1 - 1].push_back({v2 - 1, weight});
    cout << "Edge added between " << v1 << " and " << v2 << endl;
}

// Function to remove the edge between v1 and v2
void removeEdge(vector<pair<int,int>> adjList[], int v1, int v2) {
    // The edge from v1 to v2 is removed from v1's adjacency list
    for (int i = 0; i < adjList[v1 - 1].size(); i++) {
        if (adjList[v1 - 1][i].first == v2 - 1) {
            adjList[v1 - 1].erase(adjList[v1 - 1].begin() + i);
            break; // The edge is removed, and the loop is exited
        }
    }
    cout << "Edge removed between " << v1 << " and " << v2 << endl;
}

// Function to display the adjacency list of the graph
void displayList(vector<pair<int,int>> adjList[], int V) {
    // The adjacency list is displayed for each vertex
    cout << "The adjacency List is:" << endl;
    for (int i = 0; i < V; i++) {
        cout << i + 1 << ": "; // The vertex is displayed with its neighbors and weights
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << "->" << adjList[i][j].first + 1 << " weight-" << adjList[i][j].second << " ";
        }
        cout << endl;
    }
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    // The number of vertices is validated to ensure it is valid
    if (V < 0) {
        cout << "Give non-zero value of number of vertices" << endl;
        exit(1); // The program is terminated if the number of vertices is invalid
    }

    vector<pair<int,int>> adjList[V]; // The adjacency list for the graph is created
    int choice;
    do {
        // The menu for user interaction is displayed
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
                // The process for adding an edge is initiated
                cout << "Enter first vertex of the edge to be added: ";
                cin >> v1;  
                cout << "Enter second vertex of the edge to be added: ";
                cin >> v2; 
                cout << "Enter the non-zero weight of the edge: ";
                cin >> weight;

                // The validity of the input is checked
                if (weight == 0) {
                    cout << "The weight should be non-zero" << endl;
                } else if (v1 == v2) {
                    cout << "Give different vertices as self-loop is not considered" << endl;
                } else if (v1 < 1 || v1 > V || v2 < 1 || v2 > V) {
                    cout << "Choose vertex between 1 to " << V << endl;
                } else if (search(adjList, v1, v2)) {
                    cout << "Edge already exists" << endl; // A check is performed to ensure the edge doesn't already exist
                } else {
                    addEdge(adjList, v1, v2, weight); // The edge is added if all checks pass
                }
                break;

            case 2:
                // The process for removing an edge is initiated
                cout << "Enter first vertex of the edge to be removed: ";
                cin >> v1;  
                cout << "Enter second vertex of the edge to be removed: ";
                cin >> v2;  

                // The validity of the input is checked
                if (v1 < 1 || v1 > V || v2 < 1 || v2 > V) {
                    cout << "Choose vertex between 1 to " << V << endl;
                } else if (!search(adjList, v1, v2)) {
                    cout << "Edge doesn't exist" << endl; // The edge must exist for removal
                } else {
                    removeEdge(adjList, v1, v2); // The edge is removed if it exists
                }
                break;

            case 3:
                displayList(adjList, V); // The adjacency list is displayed
                break;

            case 4:
                cout << "The program has finished" << endl;
                displayList(adjList, V); // The final adjacency list is displayed before exiting
                break;

            default:
                cout << "Invalid choice. Please choose between (1-4)." << endl; // Invalid input handling
                break;
        }
    } while (choice != 4); // The loop continues until the user chooses to exit

    return 0;
}
