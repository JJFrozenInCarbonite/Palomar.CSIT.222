/**
 * The game starts with a pile of marbles, and players take turns removing marbles from the pile.
 * Each player must take at least one but at most half of the marbles present in the pile on their turn.
 * The player who removes the last marble loses the game.
 * The computer can play in either 'smart' or 'stupid' mode, determined randomly at the start.
 * In 'smart' mode, the computer plays strategically to leave a pile that is one less than a power of two.
 * In 'stupid' mode, the computer removes a random legal number of marbles.
 * 
 * @author JJ Hoffmann
 * @version 2024-02-24
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define NMIN 10
#define NMAX 100

int smartMove(int marbles);

int main() {
    
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    int marbles = NMIN + rand() % (NMAX - NMIN + 1); // Generate the starting pile of marbles
    bool turn = (rand() % 2 == 0); // true == human, false == computer
    bool smart = (rand() % 2 == 0); // true == smart computer opponent

    std::cout << "Welcome to the game of Nim!" << std::endl;
    std::cout << "Computer Mode: ";
    if (smart)
        std::cout << "Smart" << std::endl;
    else
        std::cout << "Stupid" << std::endl;
    std::cout << "Starting pile size: " << marbles << std::endl;
    std::cout << "You will go " << (turn ? "first" : "second") << ".\n" << std::endl;

    while (marbles > 1) {
        int marblesToRemove;

        if (turn) {
            std::cout << "It is your turn. ";
            if (marbles > 3)
                std::cout << "You may take between 1 and " << marbles / 2 << " marbles.\n";
            else 
                std::cout << "You may take 1 marble.\n";
            std::cin >> marblesToRemove;
            while (marblesToRemove < 1 || marblesToRemove > marbles / 2) {
                std::cout << "Invalid move. Please take between 1 and " << marbles / 2 << " marbles: ";
                std::cin >> marblesToRemove;
            }
        }
        else {
            if (smart) 
                marblesToRemove = smartMove(marbles);
            else
                marblesToRemove = 1 + rand() % (marbles / 2);
                std::cout << "Computer removes " << marblesToRemove;
            if (marblesToRemove > 1)
                std::cout << " marbles." << std::endl;
            else
                std::cout << " marble." << std::endl;
        }
        marbles -= marblesToRemove;
        std::cout << "\nPile size: " << marbles << "." << std::endl;    
        turn = !turn;
    }

    if (turn) 
        std::cout << "You took the last marble. You lose! :-(\n";
    else
        std::cout << "The computer took the last marble. You win! :-)\n";

    return 0;
}

/**
 * Calculates the optimal number of marbles to remove to leave the pile
 * size as a power of two minus one, using a bit shift.
 * 
 * @param marbles The number of marbles in the pile.
 * @return Number of marbles to remove. 
 */
int smartMove(int marbles) {
    
    int mask = 1;
    while ((mask << 1) -1 < marbles) {
        mask <<= 1;
    }
    mask -= 1;

    return (marbles - mask) > 0 ? (marbles - mask) : 1;
}