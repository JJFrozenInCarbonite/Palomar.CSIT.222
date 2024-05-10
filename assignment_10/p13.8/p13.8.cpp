/**
 * Assignment 10 - p13.8
 *
 * This program the use of templates to create an associative array.
 * @author JJ Hoffmann
 * @version 2024-05-10
*/

#include <iostream>
#include <vector>
#include <string>
#include <utility>

/**
 * An associative array that maps strings to doubles.
 */
template <typename K, typename V>
class AssociativeArray {
    private:
        std::vector<std::pair<K, V>> data;

    public:
        /**
         * Retrieves the value associated with a given key.
         * @param key the key to access
         * @return the value at the key
         */
        V get(const K& key) {
            for (auto& pair : data) {
                if (pair.first == key) {
                    return pair.second;
                }
            }
            throw std::invalid_argument("Key not found");
        }

        /**
         * Inserts or updates a key-value pair in the associative array.
         * @param key the key to insert or update
         * @param value the value to associate with the key
         */
        void put(const K& key, const V& value) {
            for (auto& pair : data) {
                if (pair.first == key) {
                    pair.second = value;
                    return;
                }
            }
            data.push_back(std::make_pair(key, value));
        }
};

int main() {
    AssociativeArray<std::string, double> prices;

    // Adding values to the associative array
    prices.put("Toaster Oven", 19.95);
    prices.put("Car Vacuum", 24.95);

    // Displaying the values
    std::cout << "Toaster Oven: " << prices.get("Toaster Oven") << std::endl;
    std::cout << "Car Vacuum: " << prices.get("Car Vacuum") << std::endl;

    return 0;
}