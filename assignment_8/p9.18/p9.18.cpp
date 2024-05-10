/**
 * Assignment 8 - 9.18
 *
 * This program simulates a combination lock.
 *
 * @author JJ Hoffmann
 * @version 2024-05-09
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * A combination lock that can be opened by turning the dial left and right.
 */
class ComboLock {
    private:
    int dial_position;
    bool gate1;
    bool gate2;
    bool gate3;
    int digit1;
    int digit2;
    int digit3;
    int turn_count;

    public:
        /**
         * Constructs a combination lock with a given combination.
         * @param digit1 the first digit of the combination
         * @param digit2 the second digit of the combination
         * @param digit3 the third digit of the combination
         * @param debug whether to print debugging information (default: false)
         */
        ComboLock(int digit1, int digit2, int digit3, bool debug=false) {
            if (digit1 == digit2 || digit2 == digit3) 
                throw std::invalid_argument("Second digit must be unique!"); // This is a true constraint on real life combo locks
            this->digit1 = digit1;
            this->digit2 = digit2;
            this->digit3 = digit3;
            reset();
            if (debug) {
                std::cout << "Debugging mode enabled!" << std::endl;
                std::cout << "1. Right " << digit1 << " = " << (this->dial_position < digit1 ? 40*3 + digit1 - this->dial_position : 40*4 - this->dial_position + digit1) << std::endl;
                std::cout << "2. Left " << digit2 << " = " << (digit1 < digit2 ? 40*2 - digit2 + digit1 : 40 + digit1 - digit2) << std::endl;
                std::cout << "3. Right " << digit3 << " = " << (digit2 < digit3 ? digit3 - digit2 : 40 + digit2 - digit3) << std::endl << std::endl;;
            }
        }

        /**
         * Determines whether the lock is open.
         * @return true if the lock is open, false otherwise
         */
        bool open() {
            return gate1 && gate2 && gate3;
        }

        /**
         * Operates the lock by turning the dial left or right.
         */
        void operate() {
            int ticks;
            if (this->turn_count % 2 == 0) {
                std::cout << "Enter a number to turn the dial right: ";
                std::cin >> ticks;
                turn_right(ticks);
            }
            else {
                std::cout << "Enter a number to turn the dial left: ";
                std::cin >> ticks;
                turn_left(ticks);
            }
        }
        
        /**
         * Resets the lock to its initial state.
         */
        void reset() {
            dial_position = rand() % 40;
            while(dial_position == digit1)
                dial_position = rand() % 40; // set dial to random position that is not the first digit
            turn_count = 0;
        }

        /**
         * Turns the dial left a given number of ticks.
         * @param ticks the number of ticks to turn
         */
        void turn_left(int ticks) {
            this->turn_count++;
            dial_position = ((dial_position - ticks) % 40 + 40) % 40;
            if (this->turn_count == 2) {
                if (ticks >= 40 && ticks < 40*2) {
                    if (dial_position == digit2)
                        this->gate2=true;
                }
            }
        }
        
        /**
         * Turns the dial right a given number of ticks.
         * @param ticks the number of ticks to turn
         */
        void turn_right(int ticks) {
            this->turn_count++;
            dial_position = (dial_position + ticks) % 40;
            if (this->turn_count == 1) {
                if (ticks >= 40*3 && ticks < 40 * 4) {
                    if (dial_position == digit1)
                        this->gate1 = true;
                }
            }
            else if (this->turn_count == 3) {
                if (ticks >= 0 && ticks < 40) {
                    if (dial_position == digit3)
                        this->gate3 = true;
                }
            }
        }

        /**
         * Outputs the current state of the lock.
         * @param os the output stream
         * @param lock the lock to output
         * @return the output stream
         */
        friend std::ostream& operator<<(std::ostream& os, const ComboLock& lock) {
            os << "Turn: " << lock.turn_count << ", Dial position: " << lock.dial_position << std::endl;
            return os;
        }

};

int main() {
    srand(time(0));

    ComboLock lock(10, 20, 30); 

    for(int i = 0; i < 3; i++) {
        std::cout << lock;
        lock.operate();
    }

    std::string status = lock.open() ? "Open" : "Closed";
    std::cout << "\bLock Opened: " << status << std::endl;  
    
    return 0;
}