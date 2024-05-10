/**
 * Assignment 10 - p13.7
 *
 * This program demonstrates the use of an associative array.
 * @author JJ Hoffmann
 * @version 2024-05-10
*/

#include <iostream>
#include <unordered_map>
#include <string>

/**
 * An associative array that maps strings to doubles.
 */
class AssociativeArray {
    private:
        std::unordered_map<std::string, double> data;

    public:
        /**
         * Overloads the [] operator to access the associative array.
         * @param key the key to access
         * @return the value at the key
         */
        double& operator[](const std::string& key) {
            return data[key];
        }

};

int main() {
    AssociativeArray prices;

    // Adding values to the associative array
    prices["Toaster Oven"] = 19.95;
    prices["Car Vacuum"] = 24.95;

    // Displaying the values
    std::cout << "Toaster Over: " << prices["Toaster Oven"] << std::endl;
    std::cout << "Car Vacuum: " << prices["Car Vacuum"] << std::endl;

    return 0;
}