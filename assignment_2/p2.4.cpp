#include <iomanip>
#include <iostream>
using namespace std;

/**
 * Assignment 2 - P2.4 - This program computes the total cost of owning a car for 5 years
 * 
 * @author JJ Hoffmann
 * @version 02/11/2024
 */

/**
 *  Main function.
 * 
 * Takes input from the user and then computes the cost of owning a vehicle over
 * 5 years
 * 
 * @param term - Length of ownership
 * @param newPrice - Price of the vehicle when new
 * @param usedPrice - Price of the vehicle after the term
 * @param vehicleMileage - Vehicle verage miles / gallon
 * @param annualMileage - Estimated annual mileage of the user
 * @param gasPrice - Estimated average price of a gallon of gas over the term
 * @param termCost - Computed estimated cost of the vehicle over the term
 * @return Program exit status.
*/
int main() 
{
    const double term = 5;
    
    double 
        newPrice,
        usedPrice,
        vehicleMileage,
        annualMileage,
        gasPrice,
        termCost
        ;

    cout << fixed;
    cout << setprecision(2);
        
    cout << "Let's calculate the cost of your car after 5 years.\n";
    cout << "First, we'll need to gather some info.\n\n";
    
    cout << "What is the price of the vehicle when new?\n$";
    cin >> newPrice;

    cout << "What will the estimated price of the vehicle be in " << (int)term << " years?\n$";
    cin >> usedPrice;

    cout << "What is the vehicles estimated fuel efficiency in miles per gallon?\n";
    cin >> vehicleMileage;

    cout << "How many miles do you drive in a year?\n";
    cin >> annualMileage;
    
    cout << "What is the average cost of a gallon of gas over the next " << (int)term << " years?\n$";
    cin >> gasPrice;

    termCost = (newPrice - usedPrice) + ((annualMileage / vehicleMileage) * term);
    
    cout << "\nThe estimated cost of your vehicle over " << (int)term << " years is $" << termCost;

    return 0;
}
