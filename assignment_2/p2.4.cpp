#include <iostream>
using namespace std;

/**
 * Assignment 2 - P2.4 - This program computes the total cost of owning a car for 5 years
 * 
 * @author JJ Hoffmann
 * @version 02/10/2024
 */

/** 
 * Computes numerical month and day of Easter for the provided year.
 * 
 * @param y the target year to be used in for computing the date of Easter
 * @return the address of a two-element array holding the month and day of Easter
*/

int* computeCost(const int& y) 
{
    static int monthDay[2]; // array to hold month and day
    
    int a,b,c,d,e,g,h,j,k,m,r,n,p; // local variables for algorithm processing

    a = y % 19;
    b = y / 100;
    c = y % 100;
    d = b / 4;
    e = b % 4;
    g = (8 * b + 13) / 25;
    h = (19 * a + b - d - g + 15) % 30;
    j = c / 4;
    k = c % 4;
    m = (a + 11 * h) / 319;
    r = (2 * e + 2 * j - k - h + m + 32) % 7;
    n = (h - m + r + 90) / 25;
    p = (h - m + r + n + 19) % 32;

    monthDay[0] = n;
    monthDay[1] = p;
    return monthDay;
} 

/**
 *  Main function.
 * 
 * 
 * Takes input from the user and then computes the cost of owning a vehicle over
 * 5 years
 * 
 * @return Program exit status.
*/
int main() 
{
    double 
        purchasePrice, // vehicle purchase price
        annualMileage, // estimated annual miles driven
        gasPrice, // price of gas
        resaleValue; // estimated resale value
    
    cout << "Let's calculate the cost of your car after 5 years." << endl;
    cout << "First, we'll need to gather some info." << endl;
    
    cout << "What is the purchase price of the car? ";
    cin >> purchasePrice;
    
    cout << "About how many miles do you drive annually? ";
    cin >> annualMileage;
    
    cout << "How much does gas cost? ";
    cin >> gasPrice;

    cout << "What is the resale value of the car? ";
    cin >> resaleValue;

    



    return 0;
}
