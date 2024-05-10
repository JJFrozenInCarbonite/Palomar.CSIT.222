/**
 * Assignment 9 - 10.9
 *
 * This program calculates the values of a parallel and series resonant circuit.
 *
 * @author JJ Hoffmann
 * @version 2024-05-10
*/

#include <iostream>
#include <cmath>

/**
 * A resonant circuit with a resonant frequency, bandwidth, and gain.
 */
class ResonantCircuit {
    private:
        double resonantFrequency; // W₀
        double bandwidth; // B
        double gain; // k
    public:
        /**
         * Constructs a resonant circuit with a given resonant frequency, bandwidth, and gain.
         * @param resonantFrequency the resonant frequency
         * @param bandwidth the bandwidth
         * @param gain the gain
         */
        ResonantCircuit(double resonantFrequency, double bandwidth, double gain) 
            : resonantFrequency(resonantFrequency), bandwidth(bandwidth), gain(gain) {}
        
        /**
         * virtual function to design the circuit
        */
        virtual void designCircuit() = 0;

        /**
         * Displays the resonant frequency, bandwidth, and gain.
         */
        double getResonantFrequency() {
            return resonantFrequency;
        }

        /**
         * Displays the resonant frequency, bandwidth, and gain.
         */
        double getBandwidth() {
            return bandwidth;
        }

        /**
         * Displays the resonant frequency, bandwidth, and gain.
         */
        double getGain() {
            return gain;
        }

        /**
         * Sets the resonant frequency.
         * @param resonantFrequency the new resonant frequency
         */
        void setResonantFrequency(double resonantFrequency) {
            this->resonantFrequency = resonantFrequency;
        }

        /**
         * Sets the bandwidth.
         * @param bandwidth the new bandwidth
         */
        void setBandwidth(double bandwidth) {
            this->bandwidth = bandwidth;
        }

        /**
         * Sets the gain.
         * @param gain the new gain
         */
        void setGain(double gain) {
            this->gain = gain;
        }

        /**
         * Displays the resonant frequency, bandwidth, and gain.
         */
        virtual void display() const {
            std::cout << "Resonant Frequency: " << resonantFrequency << ", Bandwidth: " << bandwidth << ", Gain: " << gain << std::endl;
        }
        
};

/**
 * A parallel resonant circuit with a resonant frequency, bandwidth, and gain.
 */
class ParallelResonantCircuit : public ResonantCircuit {
    private:
        double r, c, l;

    public:
        /**
         * Constructs a parallel resonant circuit with a given resonant frequency, bandwidth, and gain.
         * @param resonantFrequency the resonant frequency
         * @param bandwidth the bandwidth
         * @param gain the gain
         */
        ParallelResonantCircuit(double resonantFrequency, double bandwidth, double gain) 
            : ResonantCircuit(resonantFrequency, bandwidth, gain) {
                designCircuit();
            }

        /**
         * Designs the parallel resonant circuit.
         */
        void designCircuit() {
            this->r = ResonantCircuit::getResonantFrequency();
            this->c = 1/ResonantCircuit::getBandwidth();
            this->l = 1 / (std::pow(ResonantCircuit::getGain(), 2.0) * this->c);
        }

        /**
         * Displays the resonant frequency, bandwidth, and gain.
         */
        void display() const override {
            ResonantCircuit::display();
            std::cout << "R: " << r << ", C: " << c << ", L: " << l << std::endl;
        }
};

/**
 * A series resonant circuit with a resonant frequency, bandwidth, and gain.
 */
class SeriesResonantCircuit : public ResonantCircuit {
    private:
        double r, c, l;

    public:

        /**
         * Constructs a series resonant circuit with a given resonant frequency, bandwidth, and gain.
         * @param resonantFrequency the resonant frequency
         * @param bandwidth the bandwidth
         * @param gain the gain
         */
        SeriesResonantCircuit(double resonantFrequency, double bandwidth, double gain) 
            : ResonantCircuit(resonantFrequency, bandwidth, gain) {
                designCircuit();
            }

        /**
         * Designs the series resonant circuit.
         */
        void designCircuit() {
            this->r = 1 / ResonantCircuit::getResonantFrequency();
            this->l = this->r / ResonantCircuit::getBandwidth();
            this->c = 1 / (std::pow(ResonantCircuit::getGain(), 2.0) * this->l);
        }

        /**
         * Displays the resonant frequency, bandwidth, and gain.
         */
        void display() const override {
            ResonantCircuit::display();
            std::cout << "R: " << r << ", C: " << c << ", L: " << l << std::endl;
        }
};

int main() {
    ParallelResonantCircuit prc(1.0, 2.0, 3.0);
    prc.display();

    SeriesResonantCircuit src(4.0, 5.0, 6.0);
    src.display();

    return 0;
}