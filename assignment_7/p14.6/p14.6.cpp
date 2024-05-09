/**
 * Assignment 7 - 14.6
 *
 * This program uses a queue to implement the merge sort algorithm.
 *
 * @author JJ Hoffmann
 * @version 2024-05-08
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * Merges two sorted vectors into a single sorted vector.
 * 
 * @param vector1 The first sorted vector.
 * @param vector2 The second sorted vector.
 * @return The merged vector containing all elements from vector1 and vector2 in sorted order.
 */
vector<int> Merge(const vector<int>& vector1, const vector<int>& vector2) {
    vector<int> mergedVector;
    int i = 0, j = 0;

    while (i < vector1.size() && j < vector2.size()) {
        if (vector1[i] <= vector2[j]) {
            mergedVector.push_back(vector1[i++]);
        } else {
            mergedVector.push_back(vector2[j++]);
        }
    }

    while (i < vector1.size()) {
        mergedVector.push_back(vector1[i++]);
    }

    while (j < vector2.size()) {
        mergedVector.push_back(vector2[j++]);
    }

    return mergedVector;
}

int main() {
    // Sample input
    vector<int> arr = {9, 7, 5, 3, 1, 8, 6, 4, 2};

    // Create a queue of vectors
    queue<vector<int>> queue;

    // Insert vectors of length 1 for each element into the queue
    for (int num : arr) {
        queue.push(vector<int>{num});
    }

    // Merge pairs of vectors until the queue has size 1
    while (queue.size() > 1) {
        vector<int> vector1 = queue.front();
        queue.pop();
        vector<int> vector2 = queue.front();
        queue.pop();
        vector<int> mergedVector = Merge(vector1, vector2);
        queue.push(mergedVector);
    }

    // The sorted array is the only vector left in the queue
    vector<int> sortedArray = queue.front();

    // Print the sorted array
    cout << "Sorted Array:" << endl;
    for (int num : sortedArray) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
