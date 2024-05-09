/**
 * Assignment 7 - 14.8
 *
 * This program implements a "flood fill" algorithm using a queue.
 * It fills the connected components in a 2D array.
 * The starting point is provided by the user.
 *
 * @author JJ Hoffmann
 * @version 2024-05-08
*/

#include <iostream>
#include <queue>

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

    std::queue<Pair> queue, neighborQueue;

    int startRow, startCol;
    std::cout << "Enter the starting row: ";
    std::cin >> startRow;
    std::cout << "Enter the starting column: ";
    std::cin >> startCol;

    queue.push(Pair(startRow, startCol));

    int count = 1;

    while (!queue.empty()) {

        Pair current = queue.front();
        queue.pop();

        int row = current.row;
        int col = current.col;

        if (array[row][col] == 0) {
            array[row][col] = count;
            if (row > 0 && array[row - 1][col] == 0) {
                neighborQueue.push(Pair(row - 1, col)); // Push north neighbor
            }
            if (col < NSIZE - 1 && array[row][col + 1] == 0) {
                neighborQueue.push(Pair(row, col + 1)); // Push east neighbor
            }
            if (row < NSIZE - 1 && array[row + 1][col] == 0) {
                neighborQueue.push(Pair(row + 1, col)); // Push south neighbor
            }
            if (col > 0 && array[row][col - 1] == 0) {
                neighborQueue.push(Pair(row, col - 1)); // Push west neighbor
            }
        }
        if (queue.empty()) {
            count++;
            while (!neighborQueue.empty()) {
                queue.push(neighborQueue.front());
                neighborQueue.pop();
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