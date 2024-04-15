#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

#define ROAD_LENGTH 10

#define CAR_SPEED 1
#define CAR_MIN_WEIGHT 25
#define CAR_MAX_WEIGHT 45
#define CAR_LENGTH 2

#define TRUCK_SPEED 1
#define TRUCK_MIN_WEIGHT 50
#define TRUCK_MAX_WEIGHT 100
#define TRUCK_TRAILER_MIN_WEIGHT 5
#define TRUCK_TRAILER_MAX_WEIGHT 15
#define TRUCK_LENGTH 5

enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class Color {
    public:
        static vector<string> colors;

        string static getRandomColor() {
            srand(time(0)); 
            int colorIndex = rand() % colors.size();
            return colors[colorIndex];
        }  
};

vector<string> Color::colors = {
    "Red", 
    "Green", 
    "Blue", 
    "Yellow",
    "Black",
    "White",
    "Purple",
    "Orange",
    "Pink",
    "Brown",
    "Gray",
    "Cyan"
};

class Location {
    private:
        int x;
        int y;

    public:
        Location(int x, int y) : x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& os, const Location& location) {
        os << "(" << location.x << ", " << location.y << ")";
        return os;
    }

    friend class Place;
    
};

class Place {
    private:
        Location location;
        Place* north;
        Place* east;
        Place* south;
        Place* west;
        bool blocked;

    public:
        // Constructor to initialize the place with a specific position
        Place(int x, int y) : 
            location(x, y),
            north(nullptr), 
            east(nullptr), 
            south(nullptr), 
            west(nullptr), 
            blocked(false) {}

        bool isBlocked() {
            return blocked;
        }

        // Getters
        Location getLocation() {
            return location;
        }

        const Location* getLocation() const {
            return &location;
        }

        // Setters
        void setBlocked(bool blocked) {
            this->blocked = blocked;
        }

        friend std::ostream& operator<<(std::ostream& os, Place& place) {
            os << place.location;
            return os;
        }

        friend class Road;
};

class Vehicle {
    protected:
        Place* location; // Position of the head of the vehicle
        int speed; // Speed of the vehicle
        int weight; // Weight of the vehicle
        int direction; // Direction of the vehicle
        

    public:
        Vehicle(Place* location, int speed, int weight) :
            location(location),
            speed(speed),
            weight(weight) {}

        int getSpeed() {
            return speed;
        }

        int getWeight() {
            return weight;
        }
};

class Car : public Vehicle {
    private:
        string color;

    public:
        Car(Place* position) : 
            Vehicle(
                position, 
                CAR_SPEED, 
                CAR_MIN_WEIGHT + rand() % (CAR_MAX_WEIGHT - CAR_MIN_WEIGHT + 1) * 100
            ) {
                color = Color::getRandomColor();
            }

        string getColor() {
            return color;
        }            
};

class Truck : public Vehicle {
    private:
        int length;
        int trailerWeight;

    public:
        Truck(Place* position) : 
            Vehicle(
                position, 
                TRUCK_SPEED, 
                TRUCK_MIN_WEIGHT + rand() % (TRUCK_MAX_WEIGHT - TRUCK_MIN_WEIGHT + 1) * 100
            ) {
                length = 2 + rand() % 3;
                trailerWeight = TRUCK_TRAILER_MIN_WEIGHT + rand() % (TRUCK_TRAILER_MAX_WEIGHT - TRUCK_TRAILER_MIN_WEIGHT + 1) * 100;
            }

        int getLength() {
            return length;
        }
};

int main() {
    Location* location = new Location(0,0);
    cout << *location << endl;
    Place* place = new Place(0, 0);
    cout << *place << endl;

    Car c1 = Car(place);
    cout << c1.getColor() << endl;

    Truck t1 = Truck(place);

    return 0;
}