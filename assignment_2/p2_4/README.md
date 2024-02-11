# Assignment 2

## P2.4

### Problem Statement
Write a program that helps a person decide whether to buy a hybrid car. Your program’s
inputs should be:

* The cost of a new car
* The estimated miles driven per year
* The estimated gas price
* The estimated resale value after 5 years.

Compute the total cost of owning the car for 5 years. (For simplicity, we will not take the
cost of financing into account.) Obtain realistic prices for a new and used hybrid and
a comparable car from the Web. Run your program twice, using today’s gas price and
15,000 miles per year. Include pseudocode and the program runs with your assignment

### Psuedo Code

##### Variables
###### Constants
* term = the length of ownership

###### Doubles
* newPrice - The price of the vehicle when new
* usedPrice - The price of the vehicle after the term
* vehicleMileage - Average Miles / Gallon of the vehicle
* annualMileage - The user's estimated annual mileage
* gasPrice - The user's estimated average cost of a gallon of gas over the term 
* termCost - The estimated cost of the vehicle over the term

##### Math
* termCost = (newPrice - usedPrice) + (annualMileage / vehicleMileage * gasPrice * term)

Obtain the variables from the user, perform the math, and display the result to the user