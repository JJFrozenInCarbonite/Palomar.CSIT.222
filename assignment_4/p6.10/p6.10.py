import copy
import sys
            
def printBoard(board):
    for row in board:
        for cell in row:
            print('o' if cell == 1 else ' ', end='')
        print()

def nextGeneration(board):
    nextBoard = copy.deepcopy(board)
    for i,row in enumerate(board):
        for j, cell in enumerate(row):
            neighbors = countNeighbors(board, i, j)
            if cell == 1 and (neighbors < 2 or neighbors > 3):
                nextBoard[i][j] = 0
            elif cell == 0 and neighbors == 3:
                nextBoard[i][j] = 1
    return nextBoard

def countNeighbors(board, x, y):
    count = 0
    for dX in range(-1, 2):
        for dY in range(-1, 2):
            if dX == 0 and dY == 0:
                continue
            eX = x + dX
            eY = y + dY
            if eX >=0 and eY >= 0 and eX < len(board) and eY < len(board[x]):
                count += board[eX][eY]
    return count

def main():
    size = -1
    board = []
    with open('assignment_4\\p6.10\\input.txt', 'r') as file:
        lines = [line.replace('\n', '')for line in file.readlines()]
        for line in lines:
            if size == -1:
                size = len(line)
            else:
                if size != len(line):
                    print("Row size is not consistent in source file. Exiting program.")
                    exit(1)
            board.append([1 if ch == 'o' else 0 for ch in line])
    rounds = input("How many rounds should be computed?\n")
    for i in range(1, int(rounds) + 1):
        print("\nRound {}:".format(i))
        printBoard(board)
        board = nextGeneration(board)

if __name__ == '__main__':
    sys.exit(main())