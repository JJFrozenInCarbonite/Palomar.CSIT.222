/**
 * Assignment 7 - 14.7
 *
 * This program implements a "flood fill" algorithm using a stack.
 *
 * @author JJ Hoffmann
 * @version 2024-05-08
*/

#include <iostream>
#include <stack>

#define NSIZE 10

// Pair class to store row and column coordinates
class Pair {
public:
    int row;
    int col;

    Pair(int r, int c) : row(r), col(c) {}
};

int main() {
    int array[NSIZE][NSIZE] = {0}; // Initialize the array with zeros

    std::stack<Pair> stack, neighborStack;

    int startRow, startCol;
    std::cout << "Enter the starting row: ";
    std::cin >> startRow;
    std::cout << "Enter the starting column: ";
    std::cin >> startCol;

    stack.push(Pair(startRow, startCol));

    int count = 1;

    while (!stack.empty()) {

        Pair current = stack.top();
        stack.pop();

        int row = current.row;
        int col = current.col;

        if (array[row][col] == 0) {
            array[row][col] = count;
            if (row > 0 && array[row - 1][col] == 0) {
                neighborStack.push(Pair(row - 1, col)); // Push north neighbor
            }
            if (col < NSIZE - 1 && array[row][col + 1] == 0) {
                neighborStack.push(Pair(row, col + 1)); // Push east neighbor
            }
            if (row < NSIZE - 1 && array[row + 1][col] == 0) {
                neighborStack.push(Pair(row + 1, col)); // Push south neighbor
            }
            if (col > 0 && array[row][col - 1] == 0) {
                neighborStack.push(Pair(row, col - 1)); // Push west neighbor
            }
        }
        if (stack.empty()) {
            count++;
            while (!neighborStack.empty()) {
                stack.push(neighborStack.top());
                neighborStack.pop();
            }
        }
    }

    // Print the entire array
    for (int i = 0; i < NSIZE; i++) {
        for (int j = 0; j < NSIZE; j++) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}