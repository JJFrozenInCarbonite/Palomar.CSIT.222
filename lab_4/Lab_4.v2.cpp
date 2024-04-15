#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#define NSPACES 10
#define NB 0
#define EB 1
#define SB 2
#define WB 3

class Location {
    
    private:
        int x;
        int y;

    public:
        Location(int x, int y) : x(x), y(y) {}

    friend class Space;
    friend ostream& operator<<(ostream& os, const Location& loc) {
        os << "(" << loc.x << ", " << loc.y << ")";
        return os;
    }
};

class Space {
    
    private:
        Space* north;
        Space* east;
        Space* south;
        Space* west;
    public:
        Location location;       

        Space(int x, int y) : 
            location(x, y), 
            north(nullptr), 
            east(nullptr), 
            south(nullptr), 
            west(nullptr) {}

        Location getLocation() const {
            return location;
        }

    friend class Road;
};

class Road {
    
    private:
        vector<vector<Space*>> lanes;
    
    public:
        Road() {
            for(int i = 0; i < 4; i++) {
                vector<Space*> lane;
                int x, y;
                switch (i) {
                    case NB:        
                        x = NSPACES / 2 + 1;
                        y = 1;
                        break;
                    case EB:
                        x = 1;
                        y = NSPACES / 2;
                        break;
                    case SB:
                        x = NSPACES / 2;
                        y = 1;
                        break;
                    case WB:
                        x = 1;
                        y = NSPACES / 2 + 1;
                        break;
                    default:
                        x = -1;
                        y = -1;
                }
                Space* current = new Space(x, y);
                
                for(int j = 0; j < NSPACES; j++) {
                    Space* next;
                    switch(i) {
                        case NB:
                            next = new Space(NSPACES / 2 + 1, j + 1);
                            current->north = next;
                            break;
                        case EB: 
                            if (j == NSPACES / 2)
                                next = lanes[NB][NSPACES / 2 - 1];
                            else
                                next = new Space(j + 1, NSPACES / 2);
                            current->east = next;\
                            break;
                        case SB:
                            if (j == NSPACES / 2)
                                next = lanes[EB][NSPACES / 2 - 1];
                            else
                                next = new Space(NSPACES / 2, NSPACES - j % NSPACES);
                            current->south = next;
                            break;
                        case WB:
                            if (j == NSPACES / 2)
                                next = lanes[SB][NSPACES / 2 - 1];
                            else if (j == NSPACES / 2 - 1)
                                next = lanes[NB][NSPACES / 2];
                            else
                                next = new Space(NSPACES - j % NSPACES, NSPACES / 2 + 1);
                            current->west = next;
                            break;
                    }
                    current = next;
                    lane.push_back(current);
                    
                }
                lanes.push_back(lane);
            }
        }

    vector<vector<Space*>> getLanes() {
        return lanes;
    }

};

class Vehicle {
    private:
        Space* location;
        int speed;
        int weight;

    public:
        Vehicle(Space* location, int speed, int weight) : 
            location(location), 
            speed(speed), 
            weight(weight) {}
};

class Car : public Vehicle {
    private:
        string color;
    public:
        Car(Space* location, int speed, int weight):
            Vehicle(location, speed, weight) {
                vector<string> colors = {
                    "Black", 
                    "Red", 
                    "Green", 
                    "Yellow", 
                    "Blue", 
                    "Magenta", 
                    "Cyan",
                    "White", 
                    "Orange", 
                    "Purple", 
                    "Brown", 
                    "Pink"};
            }
};

int main() {
    Road* road = new Road();
    

    return 0;
}