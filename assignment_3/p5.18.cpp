/** 
 * Generate the appropriate barcode for a 5 digit zip code per USPS requirements.
 * 
 * @author JJ Hoffmann
 * @version 2024-02-26
 */

#include <iostream>
#include <string>
#include <vector>

std::string convertToString(const int &zipInt);
std::string encodeDigit(char digit);
int computeCheckDigit(const std::string &zipStr);
std::string generateBarCode(const std::string &zipStr, int checkDigit);

/**
 * Main function to demonstrate the conversion of an integer ZIP code to a barcode.
 * 
 * Prompts the user for a ZIP code, validates it, then computes and displays its barcode.
 * @return int Returns 0 to indicate success
 */
int main() {
    int checkDigit, zipInt;
    std::string barCode, zipStr;

    std::cout << "Enter Zip Code (00000 - 99999): ";
    std::cin >> zipInt;

    while (zipInt < 0 || zipInt > 99999 ) {
        std::cout << "Invalid Zip Code.\nEnter Zip Code (00000 - 99999): ";
        std::cin >> zipInt;
    }

    zipStr = convertToString(zipInt);
    checkDigit = computeCheckDigit(zipStr);
    barCode = generateBarCode(zipStr, checkDigit);

    std::cout << "Barcode:\n" << barCode << std::endl;
    
    return 0;
}

/**
 * Converts an integer ZIP code to a zero-padded string.
 * 
 * @param zipInt The integer ZIP code to convert. Must be between 0 and 99999 inclusive.
 * @return A string representation of the ZIP code, padded with zeros to ensure a length of 5 characters.
 */
std::string convertToString(const int &zipInt) {
    std::string zipStr = std::to_string(zipInt);
    return std::string(5 - zipStr.length(), '0') + zipStr;
}


/**
 * Encodes a single digit into its corresponding barcode representation.
 * 
 * @param digit The digit character to encode. Must be between '0' and '9' inclusive.
 * @return The string representation of the barcode encoding for the given digit.
 */
std::string encodeDigit(char digit) {
    std::vector<std::string> encoding = {
        "||:::", // 0
        ":::||", // 1
        "::|:|", // 2
        "::||:", // 3
        ":|::|", // 4
        ":|:|:", // 5
        ":||::", // 6
        "|:::|", // 7
        "|::|:", // 8
        "|:|::"  // 9
    };

    return encoding[digit - '0']; 
}

/**
 * Computes the check digit for a given ZIP code string based on the sum of its digits.
 * 
 * @param zipStr The string representation of the ZIP code to compute the check digit for.
 * @return The computed check digit as an integer.
 */
int computeCheckDigit(const std::string &zipStr) {
    int sum = 0;
    for (char digit : zipStr) 
        sum += digit - '0';
    return (10 - (sum % 10)) % 10;
}

/**
 * Generates a barcode string from a ZIP code string and its check digit.
 * 
 * Outputs intermediate encoding steps to the console for each digit of the ZIP code.
 * 
 * @param zipStr The string representation of the ZIP code.
 * @param checkDigit The check digit for the given ZIP code.
 * @return The complete barcode as a string, including start and end delimiter bars.
 */
std::string generateBarCode(const std::string &zipStr, int checkDigit) {
    std::string barCode = "|";
    for (char digit : zipStr) {
        std::cout << "digit: " << digit << ", barcode: " << encodeDigit(digit) << std::endl;
        barCode += encodeDigit(digit);
    }
    barCode += encodeDigit('0' + checkDigit);
    barCode += "|";
    return barCode;
}