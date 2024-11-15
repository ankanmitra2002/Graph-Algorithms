#include <iostream>
#include<stdlib.h>
using namespace std;
// Representation of undirected weighted graph using adjacency matrix
//Function to add edge
void addEdge(int** adjMat, int v1, int v2,int weight) {
    adjMat[v1 - 1][v2 - 1] = weight;
    adjMat[v2 - 1][v1 - 1] = weight;
    cout << "Edge added between " << v1 << " and " << v2 << endl;
}
//Function to remove edge
void removeEdge(int** adjMat, int v1, int v2) {
    adjMat[v1 - 1][v2 - 1] = 0;
    adjMat[v2 - 1][v1 - 1] = 0;
    cout << "Edge removed between " << v1 << " and " << v2 << endl;
}
//Function to display adjacency matrix
void displayMatrix(int** adjMat, int V) {
    cout << "The adjacency matrix is:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << adjMat[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;
    if(V<0){
        cout<<"Give non-zero value of number of vertices"<<endl;
        exit(1);
    }
    int** adjMat = (int**)calloc(V,sizeof(int*));
    for(int i=0;i<V;i++){
        adjMat[i] = (int*)calloc(V,sizeof(int));
    }
    //switch case of choices
    int choice;
    do {
        cout << "\n**********Menu:***********\n\n\n";
        cout << "Enter 1. Add Edge\n";
        cout << "Enter 2. Remove Edge\n";
        cout << "Enter 3. Display Adjacency Matrix\n";
        cout << "Enter 4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        int v1, v2,weight;
        switch (choice) {
            // conditions for adding edge
            case 1:
                cout << "Enter first vertex of the edge to be added: ";
                cin >> v1;  
                cout << "Enter second vertex of the edge to be added: ";
                cin >> v2;  
                cout << "Enter the non-zero weight of the edge: ";
                cin >> weight;  
                if(weight == 0){
                    cout << "The weight should be non-zero"<<endl;
                }
                else if(v1 == v2){
                    cout<<"Give different vertices as self loop is not considered"<<endl;
                }else if( v1 < 1 || v1 > V || v2 < 1 || v2 > V){
                    cout<<"Choose vertex between 1 to "<<V<<endl;
                }else if(adjMat[v1-1][v2-1] != 0){
                    cout<<"Edge already exists"<<endl;
                }else{
                    addEdge(adjMat, v1, v2,weight);
                }
                break;
            case 2:
            // conditions for removing edge
                cout << "Enter first vertex of the edge to be removed: ";
                cin >> v1;  
                cout << "Enter second vertex of the edge to be removed: ";
                cin >> v2;  
                if( v1 < 1 || v1 > V || v2 < 1 || v2 > V){
                    cout<<"Choose vertex between 1 to "<<V<<endl;
                }else if(adjMat[v1-1][v2-1] == 0){
                    cout<<"Edge does'nt exist"<<endl;
                }else{
                    removeEdge(adjMat, v1, v2);
                }
                break;
            case 3:
            //display
                displayMatrix(adjMat, V);
                break;
            case 4:
            //exit
                cout << "The program has finished" << endl;
                displayMatrix(adjMat,V);
                break;
            default:
                cout << "Invalid choice. Please choose between (1-4)." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
