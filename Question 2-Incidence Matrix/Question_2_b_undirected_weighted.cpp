#include<iostream>
#include <string.h>
using namespace std;
// Representation of undirected weighted graph using incidence matrix
//Function to add edge
void addEdge(int** incidenceMat, int v1, int v2,int edge,int weight) {
    incidenceMat[v1 - 1][edge] = weight;
    incidenceMat[v2 - 1][edge] = weight;
    cout << "Edge added between " << v1 << " and " << v2 << endl;
}
//Function to display incidence matrix
void displayMatrix(int** incidenceMat, int V,int E) {
    cout << "The incidence matrix is:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < E; j++) {
            cout << incidenceMat[i][j] << " ";
        }
        cout << endl;
    }
}
// searching if edge exists
bool search(int** incidenceMat,int v1,int v2,int E){
    for(int i=0;i<E;i++){
        if(incidenceMat[v1-1][i] == incidenceMat[v2-1][i] && incidenceMat[v1-1][i] != 0){
            return true;
        }
    }
    return false;
}

int main(){
	int V,E;
	cout<<"Enter the no of vertices: ";
	cin>>V;
    cout<<"Enter the no of edges: ";
	cin>>E;
    // conditions for adding edge
    if(V<0){
        cout<<"Give non-zero value of number of vertices"<<endl;
        exit(1);
    }
    if(E < 0 || E > (V*(V-1))/2){
        cout<<"Edge number should be between 0 to "<<(V*(V-1))/2<<endl;
        exit(1);
    }
	int** incidenceMat = (int**)calloc(V,sizeof(int*));
    for(int i=0;i<V;i++){
        incidenceMat[i] = (int*)calloc(V,sizeof(int));
    }
	int v1,v2,weight;
    int edgeCount = 0;
	while(edgeCount < E){
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
        }else if(search(incidenceMat,v1,v2,E)){
            cout<<"Edge already exists"<<endl;
        }else{
            addEdge(incidenceMat, v1, v2,edgeCount,weight);
            edgeCount++;
        }
	}
    //display
	displayMatrix(incidenceMat,V,E);
	return 0;
}