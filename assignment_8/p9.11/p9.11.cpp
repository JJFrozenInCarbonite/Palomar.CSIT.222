/**
 * Assignment 8 - 9.11
 *
 * This program simulates a bank account and a portfolio of bank accounts.
 *
 * @author JJ Hoffmann
 * @version 2024-05-08
*/
#include <iostream>
#include <iomanip>
using namespace std;

/**
 * A bank account whose balance can be changed by deposits and withdrawals.
 */
class BankAccount {
    private:
        double balance;

    public:
        /**
         * Constructs a bank account with zero balance.
         */
        BankAccount() {
            balance = 0;
        }

        /**
         * Constructs a bank account with a given balance.
         * @param initial_balance the initial balance
         */
        BankAccount(double initial_balance) {
            balance = initial_balance;
        }

        /**
         * Makes a deposit into this account.
         * @param amount the amount of the deposit
         */
        void deposit(double amount) {
            balance = balance + amount;
        }

        /**
         * Makes a withdrawal from this account, or charges a penalty if
         * sufficient funds are not available.
         * @param amount the amount of the withdrawal
         */
        void withdraw(double amount) {
            const double PENALTY = 10;
            if (amount > balance)
                balance = balance - PENALTY;
            else
                balance = balance - amount;
        }

        /**
         * Adds interest to this account.
         * @param rate the interest rate in percent
         */
        void add_interest(double rate) {
            double amount = balance * rate / 100;
            deposit(amount);
        }

        /**
         * Gets the current balance of this bank account.
         * @return the current balance
         */
        double get_balance() const {
            return balance;
        }
};

/**
 * A portfolio of bank accounts.
 */
class Portfolio {
    private:
        BankAccount checking;
        BankAccount savings;

    public:
        /**
         * Constructs a portfolio from a checking and a savings account.
         */
        Portfolio(BankAccount checking, BankAccount savings): checking(checking), savings(savings) {}

        /**
         * Deposits money into the specified account.
         * @param amount the amount to deposit
         * @param account the account to deposit into
         */
        void deposit(double amount, string account) {
            if (account == "C")
                checking.deposit(amount);
            else if (account == "S")
                savings.deposit(amount);
            else
                cout << "Invalid account type" << endl;
        }

        /**
         * Withdraws money from the specified account.
         * @param amount the amount to withdraw
         * @param account the account to withdraw from
         */
        void withdraw(double amount, string account) {
            if (account == "C")
                checking.withdraw(amount);
            else if (account == "S")
                savings.withdraw(amount);
            else
                cout << "Invalid account type" << endl;
        }

        /**
         * Transfers money between the specified accounts.
         * @param amount the amount to transfer
         * @param from the account to transfer from
         * @param to the account to transfer to
         */
        void transfer(double amount, string from, string to) {
            if (from == "C" && to == "S") {
                checking.withdraw(amount);
                savings.deposit(amount);
            } else if (from == "S" && to == "C") {
                savings.withdraw(amount);
                checking.deposit(amount);
            } else {
                cout << "Invalid account type(s)" << endl;
            }
        }

        /**
         * Outputs the account balances.
         * @param os the output stream
         * @param portfolio the portfolio to output
         * @return the output stream
         */
        friend ostream& operator<<(ostream& os, const Portfolio& portfolio) {
            os << "Account Balances: \n";
            os << "------------------------\n";
            os << "Checking: $" << fixed << setprecision(2) << portfolio.checking.get_balance() << endl;
            os << "Savings: $" << fixed << setprecision(2) << portfolio.savings.get_balance() << endl;
            return os;
        }
};

int main() {
    Portfolio portfolio(BankAccount(1000), BankAccount(2000));
    cout << portfolio;
    cout << "\nDepositing $500 into checking account\n\n";
    portfolio.deposit(500, "C");
    cout << portfolio;
    cout << "\nWithdrawing $200 from savings account\n\n";
    portfolio.withdraw(200, "S");
    cout << portfolio;
    cout << "\nTransferring $100 from checking to savings account\n\n";
    portfolio.transfer(100, "C", "S");
    cout << portfolio;
    return 0;
}
