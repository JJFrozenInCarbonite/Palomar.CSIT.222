/**
 * Assignment 7 - 14.5
 *
 * This program implements a Term and Polynomial class to perform operations on terms and polynomials.
 *
 * @author JJ Hoffmann
 * @version 2024-05-08
*/
#include <iostream>
#include <vector>

/**
 * The Term class represents a term in a polynomial equation.
 * Each term has a coefficient and an exponent.
 */
class Term {
    private:
        double coefficient; // The coefficient of the term
        double exponent; // The exponent of the term

    public:
        /**
         * Constructs a new Term with the specified coefficient and exponent.
         * @param coefficient The coefficient of the term.
         * @param exponent The exponent of the term.
         */
        Term(double coefficient, double exponent): 
            coefficient(coefficient), 
            exponent(exponent) {}

        /**
         * Returns the coefficient of the term.
         * @return The coefficient of the term.
         */
        double getCoefficient() const {
            return coefficient;
        }

        /**
         * Returns the exponent of the term.
         * @return The exponent of the term.
         */
        double getExponent() const {
            return exponent;
        }

        /**
         * Adds this term to another term.
         * The exponents of the two terms must be equal.
         * @param rhs The term to add to this term.
         * @return A new term that is the sum of this term and the rhs term.
         * @throws std::invalid_argument If the exponents of the two terms are not equal.
         */
        Term operator+ (Term& rhs) {
            if (exponent == rhs.exponent) {
                return Term(coefficient + rhs.coefficient, exponent);
            } else {
                throw std::invalid_argument("Exponents must be equal to add terms");
            }
        }

        /**
         * Subtracts another term from this term.
         * The exponents of the two terms must be equal.
         * @param rhs The term to subtract from this term.
         * @return A new term that is the difference of this term and the rhs term.
         * @throws std::invalid_argument If the exponents of the two terms are not equal.
         */
        Term operator- (Term& rhs) {
            if (exponent == rhs.exponent) {
                return Term(coefficient - rhs.coefficient, exponent);
            } else {
                throw std::invalid_argument("Exponents must be equal to subtract terms");
            }
        }

        /**
         * Overloads the multiplication operator (*) to multiply a Term object by an integer.
         * 
         * @param rhs The integer value to multiply the Term object by.
         * @return A new Term object with the coefficient multiplied by the integer value, and the same exponent.
         */
        Term operator* (int rhs) {
            return Term(coefficient * rhs, exponent);
        }

        /**
         * Multiplies the current term by a given scalar value.
         * 
         * @param rhs The scalar value to multiply the term by.
         * @return A new Term object representing the result of the multiplication.
         */
        Term operator* (double rhs) {
            return Term(coefficient * rhs, exponent);
        }

        /**
         * Multiplies two terms and returns the result as a new term.
         * @param rhs The term to multiply with.
         * @return The product of the two terms.
         */
        Term operator* (Term& rhs) {
            double coefficient = this->coefficient * rhs.coefficient;
            double exponent = this->exponent + rhs.exponent;
            return Term(coefficient, exponent);
        }

        /**
         * Overloads the << operator to print the Term object in a readable format.
         * 
         * @param os The output stream to print the Term object to.
         * @param t The Term object to print.
         * @return The output stream with the Term object printed to it.
         */
        friend std::ostream &operator<< (std::ostream &os, const Term &t) {
            if (t.exponent == 0) {
                os << t.coefficient;
            } else if (t.exponent == 1 || t.coefficient == -1) {
                os << t.coefficient << "x";
            } else {
                os << t.coefficient << "x^" << t.exponent;
            }   
            return os;
        }
};

/**
 * The Polynomial class represents a polynomial equation.
 * A polynomial is a sum of terms.
 */
class Polynomial {
    private:
        std::vector<Term> terms; // The terms of the polynomial

        /**
         * Combines like terms in the polynomial.
         */
        void combineLikeTerms() {
            std::vector<Term> resultTerms;
            for (int i = 0; i < terms.size(); i++) {
                for (int j = i + 1; j < terms.size(); j++) {
                    if (terms[i].getExponent() == terms[j].getExponent()) {
                        terms[i] = terms[i] + terms[j];
                        terms.erase(terms.begin() + j);
                    }
                }
            }
        };
    public:

        /**
         * Constructs a Polynomial object with a single term.
         *
         * @param term The term to be added to the polynomial.
         */
        Polynomial(Term term) {
            terms.push_back(term);
        }

        /**
         * Constructs a Polynomial object with a vector of terms.
         *
         * @param terms The vector of terms to be added to the polynomial.
         */
        Polynomial(std::vector<Term> terms) {
            if (terms.size() < 2) {
                this->terms = terms;
                return;
            } else {
                int i = 0;
                do {
                    if (terms[i].getExponent() < terms[i + 1].getExponent()) {
                        std::swap(terms[i], terms[i + 1]);
                        i = 0;
                    } else {
                        i++;
                    }
                } while (i < terms.size() - 2); 
                this->terms = terms;
                combineLikeTerms();
            }
        }

        /**
         * Adds a term to the polynomial.
         * @param rhs The term to add to the polynomial.
         * @return A new polynomial that is the sum of this polynomial and the rhs term.
         */
        Polynomial operator+ (Term& rhs) {
            std::vector<Term> resultTerms;
            for (int i = 0; i < terms.size(); i++) {
                resultTerms.push_back(terms[i]);
            }
            resultTerms.push_back(rhs);
            return Polynomial(resultTerms);
        }

        /**
         * Adds a polynomial to the polynomial.
         * @param rhs The polynomial to add to the polynomial.
         * @return A new polynomial that is the sum of this polynomial and the rhs polynomial.
         */
        Polynomial operator+ (Polynomial& rhs) {
            std::vector<Term> resultTerms;
            for (int i = 0; i < terms.size(); i++) {
                resultTerms.push_back(terms[i]);
            }
            for (int i = 0; i < rhs.terms.size(); i++) {
                resultTerms.push_back(rhs.terms[i]);
            }
            return Polynomial(resultTerms);
        }

        /**
         * Multiplies a term with the polynomial.
         * @param rhs The term to multiply with the polynomial.
         * @return A new polynomial that is the product of this polynomial and the rhs term.
         */
        Polynomial operator* (Term& rhs) {
            std::vector<Term> resultTerms;
            for (int i = 0; i < terms.size(); i++) {
                double coefficient = terms[i].getCoefficient() * rhs.getCoefficient();
                double exponent = terms[i].getExponent() + rhs.getExponent();
                resultTerms.push_back(Term(coefficient, exponent));
            }
            return Polynomial(resultTerms);
        }

        /**
         * Multiplies a polynomial with the polynomial.
         * @param rhs The polynomial to multiply with the polynomial.
         * @return A new polynomial that is the product of this polynomial and the rhs polynomial.
         */
        Polynomial operator* (Polynomial& rhs) {
            std::vector<Term> resultTerms;
            for (int i = 0; i < this->terms.size(); i++) {
                for (int j = 0; j < rhs.terms.size(); j++) {
                    double coefficient = this->terms[i].getCoefficient() * rhs.terms[j].getCoefficient();
                    double exponent = this->terms[i].getExponent() + rhs.terms[j].getExponent();
                    resultTerms.push_back(Term(coefficient, exponent));
                }    
            }
            return Polynomial(resultTerms);
        }

        /**
         * Overloads the << operator to print the Polynomial object in a readable format.
         * 
         * @param os The output stream to print the Polynomial object to.
         * @param p The Polynomial object to print.
         * @return The output stream with the Polynomial object printed to it.
         */
        friend std::ostream& operator<< (std::ostream& os, const Polynomial p) {
            for (int i = 0; i < p.terms.size(); i++) {
                if (i == 0) {
                    os << p.terms[i];
                } else if (p.terms[i].getCoefficient() < 0) {
                    auto temp = p.terms[i];
                    os << " - " << temp * -1;
                } else {
                    os << " + " << p.terms[i];
                }
            }
            return os;
        }

};

int main() {
    Term t1(5, 7);
    Term t2(4, 7);
    Term t3 = t1 + t2;
    Polynomial p1({t3, Term(5, 10), Term(1, 1), Term(10, 0)});
    Polynomial p2 ({Term(3, 2), Term(2, 1), Term(1, 0)});

    std::cout << "Assignment 7 - Problem 14.5\n\n";
    std::cout << "Term 1: " << t1 << std::endl;
    std::cout << "Term 2: " << t2 << std::endl << std::endl;
    std::cout << "Term 1 + Term 2: " << t1 + t2 << std::endl;
    std::cout << "Term 1 - Term 2: " << t1 - t2 << std::endl << std::endl;
    std::cout << "Polynomial 1: " << p1 << std::endl; 
    std::cout << "Polynomial 2: " << p2 << std::endl << std::endl;
    std::cout << "Polynomial 1 + Polynomial 2: " << p1 + p2 << std::endl;
    std::cout << "Polynomial 1 * Term 1: " << p1 * t1 << std::endl; 
    std::cout << "Polynomial 1 * Polynomial 2: " << p1 * p2 << std::endl;
    return 0;
}