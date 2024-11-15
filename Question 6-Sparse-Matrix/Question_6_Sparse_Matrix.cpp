#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>  
using namespace std;

// Class to represent a sparse matrix element (row, column, and value)
class sparse {
public:
    int row;
    int col;
    int value;

    // Constructor to initialize a sparse matrix element
    sparse(int row, int col, int value) {
        this->row = row;
        this->col = col;
        this->value = value;
    }

    // Overloading the < operator for sorting sparse matrix elements
    // First compares by row, then by column, and finally by value
    bool operator<(const sparse& other) const {
        if (row != other.row) return row < other.row;
        if (col != other.col) return col < other.col;
        return value < other.value;
    }
};

// Function to print the matrix from a text file
void printMatrix(const string& filename) {
    // Opening the file for reading
    fstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Unable to open file!" << endl; // Error handling
        exit(1);
    }

    string line;
    // Reading each line of the file and print it
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close(); // Closing the file after reading
}

// Function to convert a matrix from a text file into a sparse matrix representation
vector<sparse> convertToSparseMatrix(const string& filename) {
    fstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Unable to open file!" << endl; // Error handling
        exit(1);
    }

    int rows = 0, cols = 0, value, nonzero = 0;
    vector<sparse> sparseMatrix; // Vector to store non-zero elements of the matrix

    string line;
    // Reading the matrix from the file
    while (getline(file, line)) {
        int col = 0;
        stringstream s(line);
        // Processing each value in the line
        while (s >> value) {
            // If the value is non-zero, storing it as a sparse matrix element
            if (value != 0) {
                sparse instance(rows, col, value);
                sparseMatrix.push_back(instance); // Adding to the sparse matrix
                nonzero++;
            }
            col++;
        }
        rows++;
        cols = max(cols, col); // Updating the number of columns
    }

    // Adding the header for the sparse matrix (number of rows, columns, and non-zero elements)
    sparseMatrix.insert(sparseMatrix.begin(), sparse(rows, cols, nonzero));

    file.close(); // Closing the file after reading
    return sparseMatrix; 
}

// Function to transpose a sparse matrix
vector<sparse> transposeSparseMatrix(const vector<sparse>& matrix) {
    vector<sparse> transposed; // Vector to store the transposed matrix

    // Looping through the original sparse matrix and create the transposed matrix
    for (int i = 0; i < matrix.size(); i++) {
        // Swap the row and column for the transposed matrix
        transposed.push_back(sparse(matrix[i].col, matrix[i].row, matrix[i].value));
    }

    // Sorting the transposed matrix lexicographically (by row, then column)
    sort(transposed.begin(), transposed.end());

    return transposed; 
}

// Function to print the sparse matrix in a readable format
void printSparseMatrix(const vector<sparse>& matrix) {
    // Printing header
    cout << "Row\tCol\tValue" << endl;
    // Looping through and print each element in the sparse matrix
    for (int i = 0; i < matrix.size(); i++) {
        cout << matrix[i].row << "\t" << matrix[i].col << "\t" << matrix[i].value << endl;
    }
    cout << endl; 
}

int main() {
    // File containing the matrix data
    string filename = "matrix.txt";

    // Converting the matrix in the file to a sparse matrix format
    vector<sparse> sparseMatrix = convertToSparseMatrix(filename);
    
    // Printing the original matrix from the file
    cout << "Original Matrix:-" << endl;
    printMatrix(filename);
    
    // Printing the sparse matrix representation of the original matrix
    cout << "Original Sparse Matrix:" << endl;
    printSparseMatrix(sparseMatrix);

    // Transposing the sparse matrix and print it
    auto transposedMatrix = transposeSparseMatrix(sparseMatrix);
    cout << "Transposed Sparse Matrix (Lexicographically Sorted):" << endl;
    printSparseMatrix(transposedMatrix);

    return 0;
}
