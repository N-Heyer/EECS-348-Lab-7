#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Matrix {
private:
    vector<vector<int>> data;
    int size;

public:
    // Initialize the matrix with a given size
    Matrix(int n) : size(n), data(n, vector<int>(n)) {}

    // Read matrix values from an file
    bool readFromFile(ifstream& file) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (!(file >> data[i][j])) // Stop nums dont add up
                    return false;
            }
        }
        return true;
    }

    // Display matrix
    void display() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Overload + to add two matrices
    Matrix operator+(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    // Overload * to multiply two matrices
    Matrix operator*(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < size; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
            }
        return result;
    }

    // Sum of both main and secondary diagonals
    int sumOfDiagonals() const {
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += data[i][i] + data[i][size - i - 1];
        }
        return sum;
    }

    // Swap two rows in the matrix
    void swapRows(int row1, int row2) {
        for (int j = 0; j < size; ++j) {
            swap(data[row1][j], data[row2][j]);
        }
    }
};

// Load matrices from a file
bool loadMatricesFromFile(const string& filename, int matrixSize, vector<Matrix>& matrices) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    // Read matrices
    while (true) {
        Matrix mat(matrixSize);
        if (!mat.readFromFile(file)) break; // Stop if matrix cant be read
        matrices.push_back(mat);
    }
    file.close();
    return true;
}

// Display the menu and the selected operations
void menu(int matrixSize) {
    vector<Matrix> matrices;
    string filename;
    cout << "Enter the filename to load matrices data: ";
    cin >> filename;

    // Load all matrices from file
    if (!loadMatricesFromFile(filename, matrixSize, matrices)) {
        return;
    }

    if (matrices.size() < 2) {
        cout << "Error: The file must contain at least two matrices for addition and multiplication." << endl;
        return;
    }

    cout << "Loaded " << matrices.size() << " matrices from file.\n";

    // Display menu options
    while (true) {
        int choice;
        cout << "\nMenu:\n"
             << "1. Add the first two matrices\n"
             << "2. Multiply the first two matrices\n"
             << "3. Sum of matrix diagonal elements\n"
             << "4. Swap matrix rows\n"
             << "5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        if (choice == 5) break;

        int matIndex, row1, row2;
        switch (choice) {
            case 1: // Matrix Addition
                cout << "\nSum of the first two matrices:" << endl;
                (matrices[0] + matrices[1]).display();
                break;

            case 2: // Matrix Multiplication
                cout << "\nProduct of the first two matrices:" << endl;
                (matrices[0] * matrices[1]).display();
                break;

            case 3: // Sum of Diagonals
                cout << "Enter index of matrix to get diagonal sum (0 to " << matrices.size() - 1 << "): ";
                cin >> matIndex;
                if (matIndex >= 0 && matIndex < matrices.size()) {
                    cout << "Sum of diagonals: " << matrices[matIndex].sumOfDiagonals() << endl;
                } else {
                    cout << "Invalid matrix index!" << endl;
                }
                break;

            case 4: // Swap Rows
                cout << "Enter index of matrix to swap rows (0 to " << matrices.size() - 1 << "): ";
                cin >> matIndex;
                if (matIndex >= 0 && matIndex < matrices.size()) {
                    cout << "Enter two row indices to swap (0 to " << matrixSize - 1 << ")(EX: 0 1, to swap the first and second line): ";
                    cin >> row1 >> row2;
                    if (row1 >= 0 && row1 < matrixSize && row2 >= 0 && row2 < matrixSize) {
                        matrices[matIndex].swapRows(row1, row2);
                        cout << "Matrix after swapping rows:" << endl;
                        matrices[matIndex].display();
                    } else {
                        cout << "Invalid row indices!" << endl;
                    }
                } else {
                    cout << "Invalid matrix index!" << endl;
                }
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
}

int main() {
    int matrixSize;
    cout << "Enter the size of the square matrix: ";
    cin >> matrixSize;
    menu(matrixSize);
    return 0;
}