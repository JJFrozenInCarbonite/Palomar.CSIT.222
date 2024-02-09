/**
 * Lab 1
 *
 * This program reads a CSV file containing country names, processes each name
 * according to specific linguistic rules (e.g., prefixing with "le", "les", "l'"),
 * and prints the processed names to the standard output.
 *
 * @author JJ Hoffmann
 * @version 2024-02-08
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

/**
 * Processes country names from a given CSV file.
 *
 * Reads each line from the CSV file, extracting the fourth column as the
 * country name, and applyt specific rules to appropriately gender each
 * country's leading attribute
 *
 * @param filePath Path to the CSV file containing country names.
 * @return A vector of processed country names.
 */
std::vector<std::string> processCountries(const std::string& filePath) {
    std::vector<std::string> countries;
    std::ifstream file(filePath);
    std::string line;

    // Skip the header line
    std::getline(file, line);

    // Read each subsequent line
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string country, temp;
        int column = 0;

        // Extract the fourth column
        while (std::getline(ss, temp, ',')) {
            if (column == 3) {
                country = temp;
                break;
            }
            ++column;
        }

        // Remove quotes and trailing spaces
        country.erase(0, country.find_first_not_of('"')); // Remove leading quotes
        country.erase(country.find_last_not_of('"') + 1); // Remove trailing quotes
        country.erase(0, country.find_first_not_of(' ')); // Remove leading spaces
        country.erase(country.find_last_not_of(' ') + 1); // Remove trailing spaces

        // Add processed country to the list
        countries.push_back(country);
    }

    // Process country names according to the specified rules
    for (std::string& country : countries) {
        if (country == "Beliz" || country == "Cambodge" || country == "Mexique" || 
            country == "Mozambique" || country == "Zaïre" || country == "Zimbabwe") {
            country = "le " + country;
        } else if (country.back() == 's') {
            country = "les " + country;
        } else if (std::string("AÉEÎIOUY").find(country[0]) != std::string::npos) {
            country = "l'" + country;
        } else {
            country = "le " + country;
        }
    }

    return countries;
}

/**
 * Main function.
 *
 * Initiates the processing of country names from a CSV file and prints
 * the processed names.
 *
 * @return Program exit status.
 */
int main() {
    std::string filePath = "countries.csv";
    std::vector<std::string> countries = processCountries(filePath);

    std::cout << "Result:" << std::endl;
    for (const auto& country : countries) {
        std::cout << country << std::endl;
    }

    return 0;
}
