/**
 * Assignment 4 - P6.10
 *
 * This program reads an initial configuration for the Game of Life from a file,
 * where each line represents a row of the board and each character in the line
 * represents a cell (alive or dead). The user is asked to specify the number of
 * rounds to compute, and the board is printed to the console after each round.
 *
 * @author JJ Hoffmann
 * @version 2024-03-02
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Prints the current state of the game board to the console.
 * 
 * @param board A constant reference to a 2D vector of ints representing the game board,
 * where 1 indicates an alive cell and 0 indicates a dead cell.
 */
void printBoard(const vector<vector<int>>& board);

/**
 * Computes the next generation of the game board based on the current state.
 * 
 * @param currentBoard A constant reference to a 2D vector of ints representing the current state of the game board.
 * @return A 2D vector of ints representing the next state of the game board.
 */
vector<vector<int>> nextGeneration(const vector<vector<int>>& currentBoard);

/**
 * Counts the number of alive neighbors for a given cell on the game board.
 * 
 * @param currentBoard A constant reference to a 2D vector of ints representing the current state of the game board.
 * @param x The x-coordinate (row) of the cell.
 * @param y The y-coordinate (column) of the cell.
 * @return The number of alive neighbors surrounding the specified cell.
 */
int countNeighbors(const vector<vector<int>>& currentBoard, int x, int y);


int main() {
    int rounds;
    int size = -1;
    string line;
    ifstream file("c:\\dev\\repos\\Palomar.CSIT.222\\assignment_4\\p6.10\\input.txt");
    vector<vector<int>> board;

    if(file.is_open()) {
        while (getline(file, line)) {
            if (size == -1 )
                size = line.size();
            else {
                if (size != line.size()) {
                    cout << "Row size is not consistent in source file. Exiting program." << endl;
                    exit(1);
                }
            }
            vector<int> row;
            for(auto& ch : line) 
                row.push_back(ch == 'o' ? 1 : 0);
            board.push_back(row);
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file." << std::endl;
    }

    cout << "How many rounds should be computed?\n";
    cin >> rounds;

    for(int i = 1; i <= rounds; i++) {
        
        cout << "\nRound " << i << ".\n";
        printBoard(board);
        board = nextGeneration(board);
    }

    return 0;
}

void printBoard(const vector<vector<int>>& board) {
    // Iterate over each row of the board
    for (auto& row : board) {
        // Iterate over each cell in the row
        for( int cell : row) {
            // Print 'o' for alive cells, space for dead cells
            cout << (cell ? 'o' : ' ');
        }
        // Move to the next line after printing each row
        cout << endl;
    }
}

vector<vector<int>> nextGeneration(const vector<vector<int>>& currentBoard) {
    vector<vector<int>> nextBoard = currentBoard; // Copy current board to next

    // Iterate over every cell of the board
    for (int i = 0; i < currentBoard.size(); i++) {
        for (int j = 0; j < currentBoard[i].size(); j++) {
            int neighbors = countNeighbors(currentBoard, i, j); // Count alive neighbors

            // Apply the Game of Life rules to determine if cell should be alive or dead
            if (currentBoard[i][j] == 1 && (neighbors < 2 || neighbors > 3))
                nextBoard[i][j] = 0; // Cell dies
            else if (currentBoard[i][j] == 0 && neighbors == 3) 
                nextBoard[i][j] = 1; // Cell becomes alive
        }
    }
    return nextBoard; // Return the next generation board
}

int countNeighbors(const vector<vector<int>>& currentBoard, int x, int y) {
    int count = 0; // Initialize alive neighbors count

    // Check all eight directions around the cell (x, y)
    for (int dX = -1; dX <= 1; dX++) {
        for (int dY = -1; dY <= 1; dY++) {
            if (dX == 0 && dY ==0) 
                continue; // skip cell (x, y)
            int eX = x + dX, eY = y + dY; // Calculate neighbor's coordinates

            // Check if neighbor is within the bounds of the board and alive
            if (
                eX >= 0 
                && eY >= 0 
                && eX < currentBoard.size() 
                && eY < currentBoard[x].size()
            ) 
                count += currentBoard[eX][eY]; // Increment count if neighbor is alive
        }
    }
    return count; // Return the count of alive neighbors
}