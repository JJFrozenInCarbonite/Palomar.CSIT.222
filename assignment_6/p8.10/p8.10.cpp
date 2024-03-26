/**
 * Assignment 6 - P.8.10
 *
 * Employing the Playfair cipher, this program encodes and decodes text files.
 *
 * @author JJ Hoffmann
 * @version 2024-03-25
*/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cctype>

/**
 * Reads the content of a file and returns it as a string.
 * @param inputFile The name of the file to read.
 * @return The content of the file as a string.
 */
std::string read_file(const std::string& inputFile);

/**
 * Generates a Playfair cipher matrix based on a keyword.
 * @param keyword The keyword to use for generating the matrix.
 * @return A pair containing a map of characters to their positions in the matrix and the matrix itself as a string.
 */
std::pair<std::unordered_map<char, size_t>, std::string> generate_matrix(const std::string& keyword);

/**
 * Encodes a text using the Playfair cipher.
 * @param text The text to encode.
 * @param keyword The keyword to use for the cipher.
 * @return The encoded text.
 */
std::string encode(const std::string& text, const std::string& keyword);

/**
 * Decodes a text using the Playfair cipher.
 * @param text The text to decode.
 * @param keyword The keyword to use for the cipher.
 * @return The decoded text.
 */
std::string decode(const std::string& text, const std::string& keyword);


int main() {
    int choice;
    std::string keyword, result, text;
    std::cout << "Playfair Cipher\n";
    std::cout << "  1. Encode\n";
    std::cout << "  2. Decode\n";
    std::cout << "Enter choice:\n";
    std::cin >> choice;
    std::cout << "Enter Cipher Key: ";
    std::cin >> keyword;

    std::string inputFile, outputFile;

    // Set file names based on user choice
    switch (choice) {
        case 1:
            inputFile = "to_encode.txt";
            outputFile = "encoded.txt";
            text = read_file(inputFile);  // Read the input file
            result = encode(text, keyword);
            break;
        case 2:
            inputFile = "to_decode.txt";
            outputFile = "decoded.txt";
            text = read_file(inputFile);  // Read the input file
            result = decode(text, keyword);
            break;
        default:
            std::cerr << "Invalid choice. Exiting program." << std::endl;
            return 1;
    }

    // Write output file
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Failed to open output file. Exiting program." << std::endl;
        return 1;
    }

    outFile << result;
    outFile.close();

    std::cout << "Operation completed successfully." << std::endl;

    return 0;
}

std::string read_file(const std::string& inputFile) {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Failed to open input file. Exiting program." << std::endl;
        exit(1);
    }

    std::string text((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();
    return text;
}

std::pair<std::unordered_map<char, size_t>, std::string> generate_matrix(const std::string& keyword) {
    std::string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    std::unordered_map<char, size_t> charPos;
    std::string matrix;
    for (char c : keyword + alphabet) {
        if (c == 'J') c = 'I'; // Treat 'J' as 'I'
        c = std::toupper(c);
        if (std::isalpha(c) && charPos.count(c) == 0) {
            matrix += c;
            charPos[c] = matrix.size() - 1;
        }
    }
    return {charPos, matrix};
}

std::string encode(const std::string& text, const std::string& keyword) {
    
    auto [charPos, matrix] = generate_matrix(keyword);

    std::string preparedText;
    char previousChar = '\0'; 
    for (char c : text) {
        if (!std::isalpha(c)) continue; // Skip non-alpha characters
        c = std::toupper(c);
        if (c == 'J') c = 'I'; // Treat 'J' as 'I'
        if (c == previousChar) {
            preparedText += 'X'; // Insert 'X' between duplicate letters
        }
        preparedText += c;
        previousChar = c;
    }
    if (preparedText.length() % 2 != 0) {
        preparedText += 'X'; // Append 'X' if the length is odd
    }

    // Encode the prepared text using the Playfair cipher rules
    std::string encoded;
    for (size_t i = 0; i < preparedText.length(); i += 2) {
        char c1 = preparedText[i];
        char c2 = preparedText[i + 1];

        // Find the positions and determine the coordinates in the matrix
        size_t pos1 = charPos[c1];
        size_t pos2 = charPos[c2];
        size_t row1 = pos1 / 5, col1 = pos1 % 5;
        size_t row2 = pos2 / 5, col2 = pos2 % 5;

        // Apply encoding rules
        if (row1 == row2) {
            col1 = (col1 + 1) % 5;
            col2 = (col2 + 1) % 5;
        } else if (col1 == col2) {
            row1 = (row1 + 1) % 5;
            row2 = (row2 + 1) % 5;
        } else {
            std::swap(col1, col2);
        }

        // Lookup characters directly from the matrix and append to the result
        encoded += matrix[row1 * 5 + col1];
        encoded += matrix[row2 * 5 + col2];
    }

    return encoded;
}

std::string decode(const std::string& text, const std::string& keyword) {
    
    auto [charPos, matrix] = generate_matrix(keyword);

    std::string preparedText;
    for (char c : text) {
        if (!std::isalpha(c)) continue; // Skip non-alpha characters
        c = std::toupper(c);
        if (c == 'J') c = 'I'; // Treat 'J' as 'I' (may not be necessary for decoding)
        preparedText += c;
    }

    // Decode the prepared text using the Playfair cipher rules
    std::string decoded;
    for (size_t i = 0; i < preparedText.length(); i += 2) {
        char c1 = preparedText[i];
        char c2 = preparedText[i + 1];

        // Find the positions and determine the coordinates in the matrix
        size_t pos1 = charPos[c1];
        size_t pos2 = charPos[c2];
        size_t row1 = pos1 / 5, col1 = pos1 % 5;
        size_t row2 = pos2 / 5, col2 = pos2 % 5;

        // Apply decoding rules
        if (row1 == row2) {
            col1 = (col1 == 0) ? 4 : col1 - 1;
            col2 = (col2 == 0) ? 4 : col2 - 1;
        } else if (col1 == col2) {
            row1 = (row1 == 0) ? 4 : row1 - 1;
            row2 = (row2 == 0) ? 4 : row2 - 1;
        } else {
            std::swap(col1, col2);
        }

        // Lookup characters directly from the matrix and append to the result
        decoded += matrix[row1 * 5 + col1];
        decoded += matrix[row2 * 5 + col2];
    }

    return decoded;
}