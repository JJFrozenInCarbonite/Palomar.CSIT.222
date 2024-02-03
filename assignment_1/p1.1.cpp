#include <iostream>
using namespace std;

/**
 * Assignment 1 - P1.1
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
    cout << "What would you like me to do?" << endl;
    string user_input;
    getline(cin, user_input);
    cout << "I am sorry, I cannot do that." << endl;
    return 0;
}
