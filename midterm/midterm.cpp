/**
 * Midterm Exam
 *
 * Polynomial Calculator
 *
 * @author JJ Hoffmann
 * @version 2024-03-26
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

/**
 * A struct to represent a term in a polynomial
 */
struct Term {
    int exponent; // The exponent of the term 
    float coefficient; // The coefficient of the term
};

/**
 * A class to represent a polynomial
 */
class Polynomial {
private:
    std::vector<Term> polyterm; // Terms of the polynomial

public:

    // Default constructor
    Polynomial() : polyterm(1) {
        polyterm[0].exponent = -1;
        polyterm[0].coefficient = 0;
    }

    /**
     * Constructor that initializes a polynomial from a vector of Term
     * @param terms The terms of the polynomial
     */
    Polynomial(const std::vector<Term>& terms) : polyterm(terms) {}

    /**
     * Copy constructor that initializes a new polynomial with the terms of an existing one
     * @param p The polynomial to copy
     */
    Polynomial(const Polynomial& p) : polyterm(p.polyterm) {}

    // Destructor
    ~Polynomial() {}

    /**
     * Prompts the user to input the degree and coefficients of the polynomial.
     * The polynomial is then constructed from these inputs.
     */
    void inputPolynomial() {
        std::cout << "  Degree: ";
        int degree;
        std::cin >> degree;

        for (int i = degree; i >= 0; --i) {
            std::cout << "    x^" << i << ": ";
            float coef;
            std::cin >> coef;
            if (polyterm.size() == 1 && polyterm[0].exponent == -1 && polyterm[0].coefficient == 0) {
                polyterm[0].exponent = i;
                polyterm[0].coefficient = coef;
            } else {
                addTerm({i, coef});
            }
        }
    }

    // Modification member functions

    /**
     * Sets the coefficient of the term with the given exponent in the polynomial.
     * If the term does not exist, a new term with the given exponent and coefficient is added.
     * @param k The exponent of the term
     * @param value The new coefficient for the term
     */
    void setCoef(int k, float value) {
        // Find the term with the given exponent
        auto it = std::find_if(polyterm.begin(), polyterm.end(), [k](const Term& term) {
            return term.exponent == k;
        });

        // If the term is found, update its coefficient
        if (it != polyterm.end()) {
            it->coefficient = value;
        }
        // If the term is not found, add a new term with the given exponent and coefficient
        else {
            Term newTerm = {k, value};
            polyterm.push_back(newTerm);
        }
    }
    /**
    * Clears all terms from the polynomial and adds a default term with an exponent of -1 and a coefficient of 0.
    */
    void clear() {
        polyterm.clear();
        polyterm.push_back({-1, 0});
    }

    // Accessor member functions

    /**
     * Returns the coefficient of the term with the given exponent in the polynomial.
     * If the term is not found, returns 0.
     * @param k The exponent of the term
     * @return The coefficient of the term with the given exponent, or 0 if the term is not found
     */
    double getCoef(int k) const {
        // Find the term with the given exponent
        auto it = std::find_if(polyterm.begin(), polyterm.end(), [k](const Term& term) {
            return term.exponent == k;
        });

        // If the term is found, return its coefficient
        if (it != polyterm.end()) {
            return it->coefficient;
        }
        // If the term is not found, return 0
        else {
            return 0;
        }
    }

    /**
     * Returns the degree of the polynomial, which is the highest exponent among all terms.
     * If the polynomial has no terms, returns -1.
     * @return The degree of the polynomial, or -1 if the polynomial has no terms
     */
    int getDegree() const {
        int degree = -1;
        for (const Term& term : polyterm) {
            if (term.exponent > degree) {
                degree = term.exponent;
            }
        }
        return degree;
    }

    /**
     * Evaluates the polynomial at the given value.
     * @param value The value at which to evaluate the polynomial
     * @return The result of evaluating the polynomial at the given value
     */
    double evaluate(double value) const {
        double result = 0;
        for (const Term& term : polyterm) {
            result += term.coefficient * std::pow(value, term.exponent);
        }
        return result;
    }

    // Operator overloads

    /**
     * Overloads the + operator to add two Polynomial objects together.
     * @param rightPoly The other Polynomial to add to this one
     * @return A new Polynomial that is the result of adding this Polynomial and the other one
     */
    Polynomial operator+(const Polynomial& rightPoly) const { 
        std::map<int, float> termMap; 

        // Terms from the first polynomial
        for (const auto& term : polyterm) {
            termMap[term.exponent] += term.coefficient;
        }

        // Terms from the second polynomial
        for (const auto& term : rightPoly.polyterm) {
            termMap[term.exponent] += term.coefficient;
        }

        // Convert the map back to a vector of Terms
        std::vector<Term> resultTerms;
        for (auto it = termMap.rbegin(); it != termMap.rend(); ++it) { 
            if (it->second != 0) { // Exclude 0 terms
                resultTerms.push_back({it->first, it->second});
            }
        }

        return Polynomial(resultTerms); 
    }

    /**
     * Overloads the - operator to subtract one Polynomial object from another
     * @param rightPoly The other Polynomial to add to this one
     * @return A new Polynomial that is the result of subtracting the other Polynomial from this one
     */
    Polynomial operator-(const Polynomial& rightPoly) const { 
        std::map<int, float> termMap; 

        // Terms from the first polynomial
        for (const auto& term : polyterm) {
            termMap[term.exponent] -= term.coefficient;
        }

        // Terms from the second polynomial
        for (const auto& term : rightPoly.polyterm) {
            termMap[term.exponent] -= term.coefficient;
        }

        // Convert the map back to a vector of Terms
        std::vector<Term> resultTerms;
        for (auto it = termMap.rbegin(); it != termMap.rend(); ++it) { 
            if (it->second != 0) { // Exclude 0 terms
                resultTerms.push_back({it->first, it->second});
            }
        }

        return Polynomial(resultTerms); 
    }

    /**
     * Overloads the = operator to assign the value of one Polynomial object to another.
     * @param rightPoly The Polynomial to assign to this one
     * @return A reference to this Polynomial after the assignment
     */
    Polynomial& operator=(const Polynomial& rightPoly) {
        if (this == &rightPoly) {
            return *this;
        }

        polyterm = rightPoly.polyterm;
        return *this;
    }

    /**
     * Overloads the == operator to determine if the the value of one Polynomial object is equal to another.
     * @param rightPoly The Polynomial to assign to this one
     * @return true if the two Polynomial objects are equal, false otherwise
     */
    bool operator==(const Polynomial& rightPoly) const {
        if (polyterm.size() != rightPoly.polyterm.size()) {
            return false;
        }

        for (size_t i = 0; i < polyterm.size(); i++) {
            if (polyterm[i].exponent != rightPoly.polyterm[i].exponent || polyterm[i].coefficient != rightPoly.polyterm[i].coefficient) {
                return false;
            }
        }

        return true;
    }

    /**
     * Overloads the * operator to multiply two Polynomial objects together.
     * @param rightPoly The Polynomial to multiply with this one
     * @return A new Polynomial that is the result of multiplying this Polynomial and the other one
     */
    Polynomial operator*(const Polynomial& rightPoly) const {
        std::map<int, float> resultMap;

        // Multiply each term from the left polynomial with each term from the right polynomial
        for (const Term& leftTerm : polyterm) {
            for (const Term& rightTerm : rightPoly.polyterm) {
                int combinedExponent = leftTerm.exponent + rightTerm.exponent;
                float combinedCoefficient = leftTerm.coefficient * rightTerm.coefficient;

                // Accumulate the product in the map, combining like terms automatically
                resultMap[combinedExponent] += combinedCoefficient;
            }
        }

        // Convert the map back to a vector of Terms
        std::vector<Term> resultTerms;
        for (const auto& term : resultMap) {
            // We can skip adding terms with a coefficient of 0 to the result
            if (term.second != 0) {
                resultTerms.push_back(Term{term.first, term.second});
            }
        }

        return Polynomial(resultTerms);
    }

    /**
     * Adds a new term to the polynomial.
     * @param term The term to add to the polynomial
     */
    void addTerm(const Term& term) {
        polyterm.push_back(term);
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);

    /**
     * Displays all the terms in the polynomial to the user, lets the user pick a term,
     * asks the user for a new value, and then updates that value within the polynomial.
     */
    void updateTerm() {
        // Display all terms
        std::cout << "\nCurrent terms:\n";
        for (int i = 0; i < polyterm.size(); i++) {
            std::cout << i + 1 << ". " << polyterm[i].coefficient << "x^" << polyterm[i].exponent << "\n";
        }

        // Let the user pick a term
        int termIndex;
        std::cout << "Enter the number of the term you want to update: ";
        std::cin >> termIndex;
        termIndex--;  

        // Check if the input is valid
        if (termIndex < 0 || termIndex >= polyterm.size()) {
            std::cout << "Invalid term number\n";
            return;
        }

        // Ask the user for a new value
        float newValue;
        std::cout << "Enter the new coefficient for this term: ";
        std::cin >> newValue;

        // Update the value within the polynomial
        polyterm[termIndex].coefficient = newValue;
    }

};

/**
 * Overloads the << operator to output a Polynomial object to a stream.
 * This is a friend function, so it has access to the private members of the Polynomial class.
 * @param os The output stream to write to
 * @param p The Polynomial to output
 * @return The output stream after the Polynomial has been written to it
 */
std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    if (p.getDegree() == -1) {
        os << "{Not Set}";
        return os;
    } else {
        bool firstTerm = true;
        for (int i = p.getDegree(); i >= 0; --i) {
            double coef = p.getCoef(i);
            if (coef != 0) {
                if (coef < 0) {
                    if (!firstTerm) {
                        os << " - ";
                    }
                    coef = -coef; 
                } else if (!firstTerm) {
                    os << " + ";
                }
                os << coef;
                if (i == 1)
                    os << "x";
                else if (i > 1)
                    os << "x^" << i;
                firstTerm = false;
            }
        }
        return os;
    }
}

/**
 * Prints the menu of operations that the user can perform.
 */
void print_menu() {
    std::cout << std::endl;
    std::cout << "====================================\n";\
    std::cout << "Polynomial Calculator\n";
    std::cout << "------------------------------------\n";\
    std::cout << "The following operations are available:\n";
    std::cout << " 1. Clear polynomials\n";
    std::cout << " 2. Evaluate polynomials\n";
    std::cout << " 3. Print polynomials\n";
    std::cout << " 4. Update a polynomial\n";
    std::cout << " 5. Add two polynomials\n";
    std::cout << " 6. Subtract two polynomials\n";
    std::cout << " 7. Test polynomial equality\n";
    std::cout << " 8. Multiply two polynomials\n";
    std::cout << " 9. Swap polynomials\n";
    std::cout << "---------------------\n";
    std::cout << " 0. Quit\n";
    std::cout << "====================================\n";\
}

/**
 * Prompts the user for a command and returns the entered command.
 * @return The command entered by the user
 */
char get_user_command() {
    char command;
    std::cout << "Enter your choice: ";
    std::cin >> command;
    return command;
}

int main() {
    char choice = '\0';
    Polynomial p1, p2;
    std::cout << "====================================\n";\
    std::cout << "Polynomial Calculator\n";
    std::cout << "------------------------------------\n";\
    std::cout << "Polynomial 1:\n";
    p1.inputPolynomial();
    std::cout << "Polynomial 2:\n";
    p2.inputPolynomial();
    std::cout << "------------------------------------\n";\

    do {
        print_menu();
        choice = get_user_command();
        int selection = 0;
        Polynomial temp;
        switch (choice) {
            case '1':
                p1.clear();
                p2.clear();
                std::cout << "\nPolynomials cleared!\n";
                break;
            case '2':   
                std::cout << "\nEnter the value of x: ";
                double value;
                std::cin >> value;
                std::cout << "  Polynomial 1: (" << p1 << ") = " << p1.evaluate(value) << std::endl;
                std::cout << "  Polynomial 2: (" << p2 << ") = " << p2.evaluate(value) << std::endl;
                break;
            case '3':
                std::cout << "\nPolynomial 1: ";
                std::cout << p1 << std::endl;
                std::cout << "Polynomial 2: ";
                std::cout << p2 << std::endl;
                break;
            case '4':
                {
                    bool sentinel = true;
                    do {
                        std::cout << "\nUpdate a polynomial:\n";
                        std::cout << "1. Polynomial 1: " << p1 << "\n";
                        std::cout << "2. Polynomial 2: " << p2 << "\n";
                        std::cout << "0. Cancel\n";
                        std::cout << "Enter your choice: ";
                        std::cin >> selection;
                        switch (selection) {
                            case 1:
                                p1.updateTerm();
                                sentinel = false;
                                break;
                            case 2:
                                p2.updateTerm();
                                sentinel = false;
                                break;
                            case 0:
                                sentinel = false;
                                break;
                            default:
                                std::cout << "Invalid selection\n";
                                break;
                            }
                    } while (sentinel);
                }
                break;
            case '5':
                std::cout << "\n(" << p1 << ")" << " + (" << p2 << ") == " << p1 + p2 << std::endl;
                break;
            case '6':
                std::cout << "\n(" << p1 << ")" << " - (" << p2 << ") == " << p1 - p2 << std::endl;
                break;
            case '7':
                std::cout << "\n" << p1;
                if (p1 == p2)
                    std::cout << " == ";
                 else 
                    std::cout << " != ";
                std::cout << p2 << std::endl;
                break;
            case '8':
                std::cout << "\n(" << p1 << ")" << " * (" << p2 << ") == " << p1 * p2 << std::endl;
                break;
            case '9':
                std::cout << "\nOriginal polynomials:\n";
                std::cout << "  Polynomial 1: " << p1 << std::endl;
                std::cout << "  Polynomial 2: " << p2 << std::endl;
                temp = p1;
                p1 = p2;
                p2 = temp;
                std::cout << "\nSwapped polynomials:\n";
                std::cout << "  Polynomial 1: " << p1 << std::endl;
                std::cout << "  Polynomial 2: " << p2 << std::endl;
                break;
            case '0':
                std::cout << "\nGoodbye!\n";
                break;
            default:
                std::cout << "Invalid choice\n";
                break;
            }
    } while (choice != '0');

    return 0;
}