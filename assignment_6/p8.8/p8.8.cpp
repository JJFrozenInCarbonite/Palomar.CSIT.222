/**
 * Assignment 5 - P.8
 *
 * This program reads a text file and calculates the frequency of each letter.
 *
 * @author JJ Hoffmann
 * @version 2024-03-25
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cmath>
using namespace std;

/**
 * Calculates the percentage of a specific letter in the total number of letters.
 * @param letter The count of the specific letter.
 * @param totalLetters The total count of all letters.
 * @return A string representing the percentage of the specific letter.
 */
string percentage(int letter, int totalLetters);

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    int totalLetters = 0;
    vector<int> letters(26, 0);

    char ch;
    while (inputFile >> ch) {
        ch = toupper(ch); // Convert character to uppercase
        if (isalpha(ch)) {
            letters[ch - 65]++;
            totalLetters++;
        }
    }
    
    cout << "+---+-----+---+-----+---+-----+---+-----+\n";
    for(int i = 0; i <= 7; i++) {
        if (i + 65 < 71) {
            cout << "| " << (char)(i + 65)  << " | " << percentage(letters[i], totalLetters);
            cout << "| " << (char)(i + 65 + 7) << " | " << percentage(letters[i + 7], totalLetters);
            cout << "| " << (char)(i + 65 + 14) << " | " << percentage(letters[i + 14], totalLetters);
            cout << "| " << (char)(i + 65 + 20) << " | " << percentage(letters[i + 20], totalLetters);
            cout << "|";
        } else {
            cout << "| " << (char)(i + 65) << " | " << percentage(letters[i], totalLetters);
            cout << "| " << (char)(i + 72) << " | " << percentage(letters[i + 6], totalLetters);
            cout << "|   |     |   |     |";
        }
        cout << endl;
    }
    cout << "+---+-----+---+-----+---+-----+---+-----+\n";

    return 0;
}

string percentage(int letter, int totalLetters) {
    double p = ((double)letter / (double)totalLetters) * 100.0;
    int roundedP = round(p);
    string result = "";
    if (roundedP == 0)
        result = " 0% ";
    else if (roundedP > 0 && roundedP < 1)
        result = "<" + to_string(roundedP) + "% ";
    else if (roundedP >= 1 && roundedP < 10)
        result = " " + to_string(roundedP) + "% ";
    else
        result = to_string(roundedP) + "% ";
    return result;
}