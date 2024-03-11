/**
 * Lab 3
 *
 * Overload operators so that they will function on a new class intended to
 * hold a matrix of numbers.
 *
 * @author JJ Hoffmann
 * @version 2024-03-10
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

/**
 * A class representing a mathematical matrix with basic arithmetic operations, 
 * increment/decrement operations, and a transpose operation.
 */
class Matrix {
    public:
        vector<vector<int>> data;
    
    Matrix() {}

    /**
     * Overloads the addition operator to add two matrices.
     * 
     * @param right The matrix to add to the current matrix.
     * @return A new matrix representing the sum of the current matrix and the 
     * input matrix.
     */
    Matrix operator+(const Matrix& right) const {
        Matrix result;
        for(size_t i = 0; i < data.size(); i++) {
            vector<int> row;
            for(size_t j = 0; j < data[i].size(); j++)
                row.push_back(data[i][j] + right.data[i][j]);
            result.data.push_back(row);
        }
        return result;
    }

    /**
     * Overloads the subtraction operator to subtract a matrix from the current matrix.
     * 
     * @param right The matrix to subtract from the current matrix.
     * @return A new matrix representing the difference between the current matrix 
     * and the input matrix.
     */
    Matrix operator-(const Matrix& right) const {
        Matrix result;
        for(size_t i = 0; i < data.size(); i++) {
            vector<int> row;
            for(size_t j = 0; j < data[i].size(); j++)
                row.push_back(data[i][j] - right.data[i][j]);
            result.data.push_back(row);
        }
        return result;
    }

    /**
     * Overloads the multiplication operator to element-wise multiply two matrices.
     * 
     * @param right The matrix to multiply with the current matrix.
     * @return A new matrix representing the element-wise product of the current 
     * matrix and the input matrix.
     */
    Matrix operator*(const Matrix& right) const {
        Matrix result;
        for(size_t i = 0; i < data.size(); i++) {
            vector<int> row;
            for(size_t j = 0; j < data[i].size(); j++)
                row.push_back(data[i][j] * right.data[i][j]);
            result.data.push_back(row);
        }
        return result;
    }

    /**
     * Overloads the pre-increment operator. Increments each element of the matrix 
     * by 1.
     * 
     * @return A reference to the current matrix after incrementation.
     */
    Matrix& operator++() {
        for(auto& row : data)
            for(auto& cell : row)
                ++cell;
        return *this;
    }

    /**
     * Overloads the post-increment operator. Increments each element of the matrix 
     * by 1.
     * 
     * @return A new matrix representing the state of the current matrix before 
     * incrementation.
     */
    Matrix operator++(int) {
        Matrix temp = *this;
        for(auto& row : data)
            for(auto& cell : row)
                ++cell;
        return temp;
    }

    /**
     * Overloads the pre-decrement operator. Decrements each element of the matrix 
     * by 1.
     * 
     * @return A reference to the current matrix after decrementation.
     */
    Matrix& operator--() {
        for(auto& row : data)
            for(auto& cell : row)
                --cell;
        return *this;
    }

    /**
     * Overloads the post-decrement operator. Decrements each element of the matrix 
     * by 1.
     * 
     * @return A new matrix representing the state of the current matrix before 
     * decrementation.
     */
    Matrix operator--(int) {
        Matrix temp = *this;
        for(auto& row : data)
            for(auto& cell : row)
                --cell;
        return temp;
    }

    /**
     * Overloads the bitwise NOT operator to transpose the matrix.
     * 
     * @return A new matrix representing the transpose of the current matrix.
     */
    Matrix operator~() {
        Matrix result;
        for(auto& row : data) {
            vector<int> temp;
            for(auto& cell : row) 
                temp.push_back(0);
            result.data.push_back(temp);
        }

        for(size_t i = 0; i < data.size(); i++) {
            vector<int>row(data[i].size(), 0);
            for(size_t j = 0; j < data[i].size(); j++)
                result.data[j][i] = data[i][j];
        }
        return result;
    }

    /**
     * Overloads the bitwise XOR operator to raise each element of the matrix to 
     * the power of the corresponding element in another matrix.
     * 
     * @param right The matrix whose elements are used as exponents.
     * @return A new matrix with each element raised to the power of the corresponding 
     * element in the input matrix.
     */
    Matrix operator^(const Matrix& right) const {
        Matrix result;
        for(size_t i = 0; i < data.size(); i++) {
            vector<int> row;
            for(size_t j = 0; j < data[i].size(); j++)
                row.push_back(pow(data[i][j], right.data[i][j]));
            result.data.push_back(row);
        }
        return result;
    }

    friend ostream& operator<<(ostream& os, const Matrix& matrix);
};


    /**
     * Friend function to overload the insertion operator for outputting the matrix 
     * to an output stream.
     * 
     * @param os The output stream.
     * @param matrix The matrix to output.
     * @return The output stream.
     */
    ostream& operator<<(ostream& os, const Matrix& matrix) {
        os << "[";
        for(size_t i = 0; i < matrix.data.size(); i++) {
                for(size_t j = 0; j < matrix.data[i].size(); j++) {
                    if (j == 0)
                        os << "[" << matrix.data[i][j] << ", ";
                    else if (j == matrix.data[i].size() - 1)
                        os << matrix.data[i][j] << "]";
                    else
                        os << matrix.data[i][j] << ", ";
                }
            if (i < matrix.data.size() - 1)
                os << ", ";
        }    
        os << "]" ;
        return os;
    };


vector<string> readFile(const string& filename);
void parseContents(const vector<string>& contents, string& op, vector<vector<int>>& m1,  vector<vector<int>>& m2);

int main(int argc, char* argv[]) {;
    string filename, op;
    vector<string> contents;
    Matrix m1, m2;

    if (argc == 1)
        filename = "input1.txt";
        // filename = "C:\\dev\\repos\\Palomar.CSIT.222\\lab_3\\input1.txt";
    else 
        filename = argv[1];

    contents = readFile(filename);
    parseContents(contents, op, m1.data, m2.data);
    
    
    if (op == "op 1") {
        cout << "Matrix 1:\n" << m1 << endl << endl;
        cout << "Matrix 2:\n" << m2 << endl << endl;
        cout << "Sum of Matrix 1 and Matrix 2:\n" << m1 + m2;
    }
    else if (op == "op 2") {
        cout << "Matrix 1:\n" << m1 << endl << endl;
        cout << "Matrix 2:\n" << m2 << endl << endl;
        cout << "Difference of Matrix 1 and Matrix 2:\n" << m1 - m2;
    }
    else if (op == "op 3") {
        cout << "Matrix 1:\n" << m1 << endl << endl;
        cout << "Matrix 2:\n" << m2 << endl << endl;
        cout << "Product of Matrix 1 and Matrix 2:\n" << m1 * m2;
    }
    else if (op == "op 4") {
        cout << "Matrix (Original):\n" << m1 << endl << endl;
        cout << "Matrix (Incremented):\n" << m1++ << endl << endl;
        cout << "Matrix (Post-Incrementation):\n" << m1 << endl << endl;
    }
    else if (op == "op 5") {
        cout << "Matrix (Original):\n" << m1 << endl << endl;
        cout << "Matrix (Incremented):\n" << ++m1 << endl << endl;
        cout << "Matrix (Post-Incrementation):\n" << m1 << endl << endl;
    }
    else if (op == "op 6") {
        cout << "Matrix (Original):\n" << m1 << endl << endl;
        cout << "Matrix (Decremented):\n" << m1-- << endl << endl;
        cout << "Matrix (Post-Decrementation):\n" << m1 << endl << endl;
    }
    else if (op == "op 7") {
        cout << "Matrix (Original):\n" << m1 << endl << endl;
        cout << "Matrix (Decremented):\n" << --m1 << endl << endl;
        cout << "Matrix (Post-Decrementation):\n" << m1 << endl << endl;
    }
    else if (op == "op 8") {
        cout << "Matrix (Original):\n" << m1 << endl << endl;
        cout << "Matrix (Transposed):\n" << ~m1 << endl << endl;
    }
    else if (op == "op 9") {
        cout << "Matrix 1:\n" << m1 << endl << endl;
        cout << "Matrix 2:\n" << m2 << endl << endl;
        cout << "Matrix 1 ^ Matrix 2:\n" << (m1^m2) << endl << endl;
    }
    else {
        cout << "Unsupported Operation!\nExiting...\n";
        exit(1);
    }
}

/**
 * Reads the contents of a file into a vector of strings.
 * 
 * @param filename The name of the file to read.
 * @return A vector containing the lines of the file.
 */
vector<string> readFile(const string& filename) {
    string line;
    vector<string> contents;
    ifstream file(filename);
    
    if (file.is_open()) {
        while (getline(file, line))
            contents.push_back(line);
    } 
    else {
        cout << "Unable to open " << filename << ".\nExiting..." << endl;
        exit(1);
    }
    file.close();

    return contents;
}

/**
 * Parses the contents of a file to extract operation type and matrix data.
 * 
 * @param contents A vector containing the lines of the file.
 * @param op A string to store the operation type.
 * @param m1 A reference to a vector of vectors of ints to store the first matrix.
 * @param m2 A reference to a vector of vectors of ints to store the second matrix.
 */
void parseContents(const vector<string>& contents, string& op, vector<vector<int>>& m1, vector<vector<int>>& m2) {
    int number;

    for(int i = 1; i < stoi(contents[0]) + 1; i++) {
        vector<int> row;
        istringstream iss(contents[i]);
        while(iss >> number)
            row.push_back(number);
        m1.push_back(row);
    }

    op = contents[1 + stoi(contents[0])];

    if(op != "op 4" && op != "op 5" && op != "op 6" && op != "op 7" && op != "op 8")
        for(int i = 2 + stoi(contents[0]); i < 2 + stoi(contents[0]) * 2; i++) {
            vector<int> row;
            istringstream iss(contents[i]);
            while(iss >> number)
                row.push_back(number);
            m2.push_back(row);
        }
}                                                                                                                                                                                                         