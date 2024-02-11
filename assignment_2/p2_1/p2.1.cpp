#include <iostream>
using namespace std;

/**
 * Assignment 2 - P2.1 - This program prompts the user for a year and then 
 * prints out the month and day of Easter Sunday for that year.
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

int* computeEaster(const int& y) 
{
    static int monthDay[2]; // array to hold month and day
    
    int a,b,c,d,e,g,h,j,k,m,r,n,p; // local variables for algorithm processing

    a = y % 19;
    b = y / 100;
    c = y % 100;
    d = b / 4;
    e = b % 4;
    g = ((8 * b) + 13) / 25;
    h = ((19 * a) + b - d - g + 15) % 30;
    j = c / 4;
    k = c % 4;
    m = (a + 11 * h) / 319;
    r = ((2 * e) + (2 * j) - k - h + m + 32) % 7;
    n = (h - m + r + 90) / 25;
    p = (h - m + r + n + 19) % 32;

    monthDay[0] = n;
    monthDay[1] = p;
    return monthDay;
}

/**
 *  Main function.
 * 
 * Initiates the process of computing the month and day of Easter 
 * for a given year based on user input.
 * 
 * @return Program exit status.
*/
int main() 
{
    int year; 
    string months[] = {"January", "February", "March", "April", "May", "June", 
        "July", "August", "September", "October", "November", "December"}; // array of month name strings
        
    cout << "Please enter a year: ";
    cin >> year;

    int* monthDay = computeEaster(year);
    cout << "\nEaster " << year << ": " << 
        months[*monthDay - 1] << " " << *(monthDay + 1) << "." << endl;

    return 0;
}
