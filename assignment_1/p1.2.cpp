#include <iostream>
using namespace std;

/**
 * Assignment 1 - P1.2
 * 
 * @author JJ Hoffmann
 * @version 02/03/2024
 */

/**
 *  Main
 * 
 * @return int Returns 0 to indicate success
*/
int main() 
{
    cout << "Hello, my name is Hal!" << endl;
    cout << "What is your name?" << endl;
    string user_name;
    getline(cin, user_name);
    cout << "Hello, " << user_name << ". I am glad to meet you!" << endl;
    return 0;
}