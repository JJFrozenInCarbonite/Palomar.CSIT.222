/**
 * Assignment 5 - P7.7
 *
 * Write a program that reads a line of text and then reads a list of words. The program should
 * then display the words that occur in the line of text, along with the number of times each word
 * occurs. The words should be displayed in the order in which they appear in the input. For each
 * word, the program should display the word and the number of times it occurs in the line of text.
 * The program should use a vector to hold the words and a vector to hold the counts.
 *
 * @author JJ Hoffmann
 * @version 2024-03-16
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>

int main() {
    std::vector<char*> words;
    std::vector<char*> pointers;
    std::string line, word; 

    std::cout << "Enter a line of text: ";
    std::getline(std::cin, line);

    std::istringstream iss(line);

    // Iterate over each word in the input
    while (iss >> word) {
        char* existingWord = nullptr;
        // Check if word is already in vector words
        for (auto& w : words) {
            if (strcmp(w, word.c_str()) == 0) {
                existingWord = w;
                break;
            }
        }

        // If word is already in vector words, add pointer to word to vector pointers
        if (existingWord) {
            pointers.push_back(existingWord);
        } 
        // If word is not already in vector words, add word to vector words and add pointer to word to vector pointers
        else {
            char* newWord = new char[word.length() + 1];
            strcpy(newWord, word.c_str());
            words.push_back(newWord);
            pointers.push_back(newWord);
        }
    }

    // Print the words and their pointers
    for (auto& p : pointers) {
        std::cout << "Word: " << p << ", Pointer: " << static_cast<void*>(p) << std::endl;
    }

    // Print count of words and pointers
    std::cout << "Count of words: " << words.size() << std::endl;
    std::cout << "Count of pointers: " << pointers.size() << std::endl;

    // Deallocate memory
    for (auto& w : words) {
        delete[] w;
    }

    return 0;
}