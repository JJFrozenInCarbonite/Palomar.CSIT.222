/**
 * Lab 3
 * 
 * Traffic Simulation Lab
 * 
 * This program simulates traffic on a road network. It includes classes and structures
 * to represent vehicles, spaces on the road, lanes, roads, and traffic lights. The program
 * uses various data structures and algorithms to manage the movement of vehicles and the
 * state of the traffic simulation.
 * 
 * The main components of the program are:
 * - Constants: A struct holding the constants used in the simulation.
 * - Direction: An enum class representing the four cardinal directions.
 * - VehicleState: An enum class representing the state of a vehicle (queued, active, retired).
 * - VehicleType: An enum class representing the type of a vehicle (car, truck, bus, motorcycle, none).
 * - Directions: A class that maps integer values to Direction enum values.
 * - Location: A class representing a location on the road network.
 * - Space: A class representing a space on the road where a vehicle can occupy.
 * - Lane: A class representing a lane on the road.
 * - Road: A class representing a road consisting of multiple lanes.
 * - TrafficLight: A class representing a traffic light that controls the flow of vehicles.
 * - Vehicle: A class representing a vehicle with properties like speed, weight, length, and type.
 * - Car: A class representing a car that inherits from the Vehicle class.
 * - Truck: A class representing a truck that inherits from the Vehicle class.
 * - Bus: A class representing a bus that inherits from the Vehicle class.
 * - Motorcycle: A class representing a motorcycle that inherits from the Vehicle class.
 * 
 * 
 * The program uses various member functions and operators to perform operations like
 * moving vehicles, updating the state of the traffic light, and checking for free spaces
 * on the road.
 * 
 * @author JJ Hoffmann
 * @version 2024-05-05
 */
/**
 * Lab 3
 * 
 * Traffic Simulation Lab
 *
 * @author JJ Hoffmann
 * @version 2024-05-05
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <queue>
#include <chrono>

#define NLENGTH 20
#define NB 0
#define EB 1
#define SB 2
#define WB 3

/**
 * Struct holding the constants used ih the simulation
*/
struct Constants {
    struct TrafficLight {
        static const int green = 20;
        static const int yellow = 6;
    };
    struct Vehicle {
        struct Car {
            static constexpr double chance = .10;
            static const int speed = 1;
            static const int length = 2;
            static const int weight = 4000;
        };
        struct Truck {
            static constexpr double chance = .05;
            static const int speed = 1;
            static const int length = 5;
            static const int weight = 20000;
            static const int cargoWeight = 80000;
        };
        struct Bus {
            static constexpr double chance = .05;
            static const int speed = 1;
            static const int length = 4;
            static const int weight = 30000;
        };
        struct Motorcycle {
            static constexpr double chance = .01;
            static const int speed = 1;
            static const int length = 1;
            static const int weight = 500;
        };
    };
};

/**
 * Represents the possible directions a vehicle can move in.
 */
enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

/**
 * Represents the possible states a vehicle can be in.
 */
enum class VehicleState {
    QUEUED,
    ACTIVE,
    RETIRED
};

/**
 * Represents the possible types a vehicle can be.
 */
enum class VehicleType {
    CAR,
    TRUCK,
    BUS,
    MOTORCYCLE,
    NONE
};

class Directions {
    private:
        std::unordered_map<int, Direction> directions = {
            {NB, Direction::NORTH},
            {EB, Direction::EAST},
            {SB, Direction::SOUTH},
            {WB, Direction::WEST}
        };
    public:
        Directions() {}

        int size() {
            return directions.size();
        }

        Direction operator[](int index) {
            return directions[index];
        }
};

/**
 * Represents the possible types a vehicle can be.
 */
class Location {
    private:
        int x;
        int y;

    public:
        /**
         * Constructs a new Location with the specified coordinates.
         *
         * @param x The x-coordinate of the new Location.
         * @param y The y-coordinate of the new Location.
         */
        Location(int x, int y): x(x), y(y) {}

        /**
         * Overloads the << operator to print the Location in a readable format.
         *
         * @param os The output stream to print to.
         * @param location The Location to print.
         * @return The output stream, for chaining.
         */
        friend std::ostream& operator<<(std::ostream& os, const Location& location) {
            os << "(" << location.x << ", " << location.y << ")";
            return os;
        }
};

class Vehicle;
/** 
 * Represents a space on the road where a vehicle can occupy.
*/
class Space {
    private:
        bool blocked; // Indicates whether the space is blocked.
        Location location; // The location of the space.
        Space* north; // The space to the north.
        Space* east; // The space to the east.
        Space* south; // The space to the south.
        Space* west; // The space to the west.
        Vehicle* vehicle; // The vehicle occupying the space.
    public:
        /**
         * Constructs a new Space with the specified location.
         *
         * @param location The location of the new Space.
         */
        Space(int x, int y): 
            blocked(false),
            location(x, y), 
            north(nullptr), 
            east(nullptr),
            south(nullptr), 
            west(nullptr),
            vehicle(nullptr) {}

        /**
         * Returns whether the space is blocked.
         *
         * @return true if the space is blocked, false otherwise.
         */
        bool isBlocked() {
            return blocked;
        }

        /**
         * Sets whether the space is blocked.
         *
         * @param blocked true to block the space, false to unblock it.
         */ 
        void setBlocked(bool blocked) { 
            this->blocked = blocked;
        }

        /**
         * Returns whether the space is occupied.
         *
         * @return true if the space is occupied, false otherwise.
         */
        bool isOccupied() {
            return vehicle != nullptr;
        }

        /**
         * Returns the space in the specified direction.
         *
         * @param direction The direction to get the next space in.
         * @return The space in the specified direction, or nullptr if there is no space.
         */
        Space* Next(Direction direction) {
            if (direction == Direction::NORTH) {
                return north;
            } else if (direction == Direction::EAST) {
                return east;
            } else if (direction == Direction::SOUTH) {
                return south;
            } else if (direction == Direction::WEST) {
                return west;
            } else
                return nullptr;
        }

        /**
         * Returns whether the next space in the specified direction is free.
         *
         * @param direction The direction to check.
         * @return true if the next space is free, false otherwise.
         */
        bool isNextFree(Direction direction) {
            Space* nextSpace = Next(direction);
            if(nextSpace != nullptr)
                return !nextSpace->isOccupied() && !nextSpace->isBlocked();
            else
                return false;
        }

        /**
         * Sets the vehicle occupying the space.
         *
         * @param vehicle The vehicle to set.
         */
        void setVehicle(Vehicle* vehicle) {
            this->vehicle = vehicle;
        }

        /**
         * Returns the vehicle occupying the space.
         *
         * @return The vehicle occupying the space.
         */
        Vehicle* getVehicle() {
            return vehicle;
        }

        /**
         * Overloads the << operator to print the Space in a readable format.
         *
         * @param os The output stream to print to.
         * @param space The Space to print.
         * @return The output stream, for chaining.
         */
        friend std::ostream& operator<<(std::ostream& os, const Space& space) {
            os << space.location;
            return os;
        }

        friend class Lane;
        friend class Road;
};

/**
 * Represents a lane on the road.
 */
class Lane {
    private:
        Direction direction; // The direction of the lane.
        std::vector<Space*> spaces; // The spaces in the lane.
    public:
        /**
         * Constructs a new Lane with the specified direction and spaces.
         *
         * @param direction The direction of the new Lane.
         * @param spaces The spaces in the new Lane.
         */
        Lane(Direction direction, std::vector<Space*> spaces): direction(direction), spaces(spaces) {}

        /**
         * Returns the number of spaces in the lane.
         *
         * @return The number of spaces in the lane.
         */
        int size() {
            return spaces.size();
        }

        /**
         * Returns the space at the specified index.
         *
         * @param index The index of the space to get.
         * @return The space at the specified index.
         */
        Space* operator[](int index) {
            return spaces[index];
        }

        friend class Road;
};

/**
 * Represents a road consisting of multiple lanes.
 */
class Road {
    private:
        std::vector<Lane> lanes; // The lanes on the road.
    public:
        /**
         * Constructs a new Road with the specified lanes.
         *
         * @param lanes The lanes of the new Road.
         */
        Road() {
            Directions directions = Directions();
            for (int i = 0; i < directions.size(); i++) {
                std::vector<Space*> lane;
                for (int j = 0; j < NLENGTH; j++) {
                    switch (i) {
                        case NB:
                            lane.push_back(new Space(NLENGTH / 2, j));
                            break;
                        case EB:
                            if (j == NLENGTH / 2) 
                                lane.push_back(lanes[NB][(NLENGTH / 2) - 1]);
                            else 
                                lane.push_back(new Space(j, (NLENGTH / 2) - 1));
                            break;
                        case SB:
                            if (j == NLENGTH / 2)
                                lane.push_back(lanes[EB][(NLENGTH / 2) - 1]);
                            else 
                                lane.push_back(new Space((NLENGTH / 2) - 1, NLENGTH - j - 1));
                            break;
                        case WB:
                            if (j == (NLENGTH / 2) - 1)
                                lane.push_back(lanes[NB][NLENGTH / 2]);
                            else if (j == NLENGTH / 2)
                                lane.push_back(lanes[SB][(NLENGTH / 2) - 1]);
                            else
                                lane.push_back(new Space(NLENGTH - j - 1, NLENGTH / 2));
                            break;
                    }
                }
                lanes.push_back({directions[i], lane});
            }

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < lanes[i].size() - 1; j++) {
                    if (i == NB) 
                        lanes[i][j]->north = lanes[i][j + 1];
                    else if (i == EB)
                        lanes[i][j]->east = lanes[i][j + 1];
                    else if (i == SB)
                        lanes[i][j]->south = lanes[i][j + 1];
                    else if (i == WB)
                        lanes[i][j]->west = lanes[i][j + 1];
                }
            }
        }
        
        /**
         * Returns the number of lanes on the road.
         *
         * @return The number of lanes on the road.
         */
        int size() { 
            return lanes.size(); 
        }

        /**
         * Returns the lane at the specified index.
         *
         * @param index The index of the lane to get.
         * @return The lane at the specified index.
         */
        Lane operator[](int index) { 
            return lanes[index];
        }

        /**
         * Returns the lane in the specified direction.
         *
         * @param direction The direction of the lane to get.
         * @return The lane in the specified direction.
         */
        Lane operator[](Direction direction) {
            return lanes[static_cast<int>(direction)];
        }
};

/**
 * Represents a traffic light that controls the flow of vehicles.
 */
class TrafficLight {
    private:
        int timer; // The timer for the traffic light.
        int greenDuration; // The duration of the green light.
        int yellowDuration; // The duration of the yellow light.
        int redDuration; // The duration of the red light.
        std::vector<Space*> corners; // The corners controlled by the traffic light.
    public:
        /**
         * Constructs a new TrafficLight with the specified road.
         *
         * @param road The road the new TrafficLight controls.
         */
        TrafficLight(Road road) {
            timer = 0;
            greenDuration = Constants::TrafficLight::green;
            yellowDuration = Constants::TrafficLight::yellow;
            redDuration = Constants::TrafficLight::green + Constants::TrafficLight::yellow;
            for (int i = 0; i < road.size(); i++)
                corners.push_back(road[i][(road[i].size() / 2) - 2]);
            for (int i = 0; i < corners.size(); i++) {
                if (i % 2 == 0)
                    corners[i]->setBlocked(true);
                else
                    corners[i]->setBlocked(false);
            }
        }

        /**
         * Updates the traffic light.
         */
        void update() {
            timer++;
            if (timer > redDuration) {
                for(auto corner : corners) 
                    corner->setBlocked(corner->isBlocked() ? false : true);
                timer = 0;
            }
        }
};

/**
 * Represents a vehicle with properties like speed, weight, length, and type.
 */
class Vehicle {
    private:
        VehicleState state; // The state of the vehicle.
        VehicleType type; // The type of the vehicle.
        int speed; // The speed of the vehicle.
        int weight; // The weight of the vehicle.
        int length; // The length of the vehicle.
        std::vector<Space*> spaces; // The spaces occupied by the vehicle.
        Direction direction; // The direction the vehicle is moving in.
        
    public:
        /**
         * Constructs a new Vehicle with the specified speed, weight, length, direction, and type.
         *
         * @param speed The speed of the new Vehicle.
         * @param weight The weight of the new Vehicle.
         * @param length The length of the new Vehicle.
         * @param direction The direction of the new Vehicle.
         * @param type The type of the new Vehicle.
         */
        Vehicle(int speed, int weight, int length, Direction direction, VehicleType type) {
            this->speed = speed;
            this->weight = weight;
            this->length = length;
            this->direction = direction;
            state = VehicleState::QUEUED;
            this->type = type;
        }

        /**
         * Returns the state of the vehicle.
         *
         * @return The state of the vehicle.
         */
        VehicleState getState() {
            return state;
        }

        /**
         * Returns the type of the vehicle.
         *
         * @return The type of the vehicle.
         */
        VehicleType getVehicleType() {
            return type;
        }

        /**
         * Moves the vehicle on the specified road.
         *
         * @param road The road to move the vehicle on.
         */
        void move(Road road) {
            if (state == VehicleState::QUEUED) { 
                if (spaces.size() == 0) {
                    if (!road[direction][0]->isOccupied()) {
                        road[direction][0]->setVehicle(this);
                        spaces.push_back(road[direction][0]);
                    }
                } else if (spaces.size() < this->length) {
                    Space* nextSpace = spaces[0]->Next(direction);
                    if(nextSpace != nullptr) {
                        if (nextSpace->isNextFree(direction)) {
                            spaces.push_back(spaces[0]->Next(direction));
                            spaces.back()->setVehicle(this);
                            if (spaces.size() == length)
                                state = VehicleState::ACTIVE;
                        }
                    }
                }
            } else if (state == VehicleState::ACTIVE) {

                if (spaces.back()->Next(direction) != nullptr) {
                    if (spaces.back()->isNextFree(direction)) {
                        spaces.push_back(spaces.back()->Next(direction));
                        spaces.back()->setVehicle(this);
                        spaces.front()->setVehicle(nullptr);
                        spaces.erase(spaces.begin());
                    }
                } else {
                    spaces.front()->setVehicle(nullptr);
                    spaces.erase(spaces.begin());
                    if(spaces.size() == 0)
                        state = VehicleState::RETIRED;
                }
            }
        }
};

/**
 * Represents a car that inherits from the Vehicle class.
 */
class Car: public Vehicle {
    private:
        std::string color; // The color of the car.

        /**
         * Sets the color of the car to a random color.
         */
        void randomColor() {
            std::vector<std::string> colors = {"Red", "Orange", "Yellow", "Green", "Blue", "Indigo", "Violet", "Purple", "Black", "White", "Silver", "Gold"};
            this->color =  colors[rand() % colors.size()];
        }
    public:
        /**
         * Constructs a new Car with the specified direction.
         *
         * @param direction The direction of the new Car.
         */
        Car(Direction direction): Vehicle(
                Constants::Vehicle::Car::speed, 
                Constants::Vehicle::Car::weight, 
                Constants::Vehicle::Car::length,
                direction,
                VehicleType::CAR) {
                    randomColor();
                }

        /**
         * Returns the color of the car.
        */
        std::string getColor() {
            return color;
        }
};

/**
 * Represents a truck that inherits from the Vehicle class.
 */
class Truck: public Vehicle {
    private:
        std::string color; // The color of the truck.
        
        /**
         * Sets the color of the truck to a random color.
         */
        void randomColor() {
            std::vector<std::string> colors = {"Red", "Orange", "Yellow", "Green", "Blue", "Indigo", "Violet", "Purple", "Black", "White", "Silver", "Gold"};
            this->color =  colors[rand() % colors.size()];
        }
        int cargoWeight; // The weight of the cargo.
    public:
        /**
         * Constructs a new Truck with the specified direction.
         *
         * @param direction The direction of the new Truck.
         */
        Truck(Direction direction): cargoWeight(Constants::Vehicle::Truck::cargoWeight), Vehicle(
                Constants::Vehicle::Truck::speed, 
                Constants::Vehicle::Truck::weight, 
                Constants::Vehicle::Truck::length,
                direction,
                VehicleType::TRUCK) {
                    randomColor();
                }

        /**
         * Returns the color of the truck.
         */
        std::string getColor() {
            return color;
        }
}; 

/**
 * Represents a bus that inherits from the Vehicle class.
 */
class Bus: public Vehicle {
    private:
        std::string name; // The name of the bus.

        /**
         * Sets the name of the bus to a random name.
         */
        void randomName() {
            std::vector<std::string> colors = {"MBTA", "CSUSM", "Palomar"};
            this->name =  colors[rand() % colors.size()];
        }
    public:
        Bus(Direction direction): Vehicle(
                Constants::Vehicle::Bus::speed, 
                Constants::Vehicle::Bus::weight, 
                Constants::Vehicle::Bus::length,
                direction,
                VehicleType::BUS) {
                    randomName();
                }

        /**
         *   Returns the name of the bus.
         **/
        std::string getName() {
            return name;
        }
};

/**
 * Represents a motorcycle that inherits from the Vehicle class.
 */
class Motorcycle: public Vehicle {
    private:
        std::string make; // The make of the motorcycle.

        /**
         * Sets the make of the motorcycle to a random make.
         */
        void randomMake() {
            std::vector<std::string> makes = {"Harley-Davidson", "Honda", "Yamaha", "Kawasaki", "Suzuki", "BMW", "Ducati", "Triumph", "Victory", "Indian", "Aprilia", "Moto Guzzi"};
            this->make = makes[rand() % makes.size()];
        }   
    public:
        /**
         * Constructs a new Motorcycle with the specified direction.
         *
         * @param direction The direction of the new Motorcycle.
         */
        Motorcycle(Direction direction): Vehicle(
                Constants::Vehicle::Motorcycle::speed, 
                Constants::Vehicle::Motorcycle::weight, 
                Constants::Vehicle::Motorcycle::length,
                direction,
                VehicleType::MOTORCYCLE) {
                    randomMake();
                }
        
        /**
         * Returns the make of the motorcycle.
         */
        std::string getMake() {
            return make;
        }
};

/**
 * Represents a queue of vehicles waiting to enter the road.
 */
class VehicleQueue {
    private:
        std::vector<std::queue<Vehicle*>> queue; // The queue of vehicles.
    public:
        /**
         * Constructs a new VehicleQueue.
         */
        VehicleQueue() : queue(4) {}

        /**
         * Enqueues the specified vehicle in the specified direction.
         *
         * @param direction The direction to enqueue the vehicle in.
         * @param vehicle The vehicle to enqueue.
         */
        void enqueue(int direction, Vehicle* vehicle) {
            queue[direction].push(vehicle);
        }

        /**
         * Enqueues the specified vehicle in the specified direction.
         *
         * @param direction The direction to enqueue the vehicle in.
         * @param vehicle The vehicle to enqueue.
         */
        void enqueue(Direction direction, Vehicle* vehicle) {
            queue[static_cast<int>(direction)].push(vehicle);
        }

        /**
         * Returns whether the queue in the specified direction is empty.
         *
         * @param direction The direction to check.
         * @return true if the queue is empty, false otherwise.
         */
        bool isEmpty(int direction) {
            return queue[direction].empty();
        }

        /**
         * Returns whether the queue in the specified direction is empty.
         *
         * @param direction The direction to check.
         * @return true if the queue is empty, false otherwise.
         */
        bool isEmpty(Direction direction) {
            return queue[static_cast<int>(direction)].empty();
        }

        /**
         * Dequeues the vehicle in the specified direction.
         *
         * @param direction The direction to dequeue the vehicle from.
         * @return The dequeued vehicle.
         */
        Vehicle* dequeue(int direction) {
            Vehicle* vehicle = queue[direction].front();
            queue[direction].pop();
            return vehicle;
        }

        /**
         * Dequeues the vehicle in the specified direction.
         *
         * @param direction The direction to dequeue the vehicle from.
         * @return The dequeued vehicle.
         */
        Vehicle* dequeue(Direction direction) {
            Vehicle* vehicle = queue[static_cast<int>(direction)].front();
            queue[static_cast<int>(direction)].pop();
            return vehicle;
        }

        /**
         * Updates the vehicles in the queue.
         *
         * @param road The road to update the vehicles on.
         */
        void update(Road road) {
            for (int i = 0; i < queue.size(); i++) {
                std::queue<Vehicle*> tempQueue;
                while (!queue[i].empty()) {
                    auto vehicle = queue[i].front();
                    vehicle->move(road);            
                    if (vehicle->getState() != VehicleState::RETIRED) {
                        tempQueue.push(vehicle);
                    }
                    queue[i].pop();
                }
                queue[i] = tempQueue;
            }
        }
};

void printDisplay(Road, TrafficLight, std::ofstream& outFile); 
std::string getVehicleTypeStr(Space* space);
void initRand();
Direction generateRandomDirection();
VehicleType generateRandomVehicle();


int main() {
    initRand();
    Road road; 
    TrafficLight light(road); 
    VehicleQueue queue;
    std::ofstream outFile("lab_4.txt");
    if (!outFile) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }
    for (int i = 0; i < 100; i++) {
        std::cout << "Iteration: " << i << std::endl;
        outFile << "Iteration: " << i << std::endl;
        light.update();
        queue.update(road);
        VehicleType vehicle = generateRandomVehicle();
        Direction direction = generateRandomDirection();
        if (vehicle == VehicleType::CAR) {
            queue.enqueue(direction, new Car(direction));
        } else if (vehicle == VehicleType::TRUCK) {
            queue.enqueue(direction, new Truck(direction));
        } else if (vehicle == VehicleType::BUS) {
            queue.enqueue(direction, new Bus(direction));
        } else if (vehicle == VehicleType::MOTORCYCLE) {
            queue.enqueue(direction, new Motorcycle(direction));
        } 
        printDisplay(road, light, outFile);

    }
    return 0;
}

/**
 * Prints the display of the road network to console and to file
*/
void printDisplay(Road road, TrafficLight light, std::ofstream& outFile) {
    /*      SN
        ....  ....
        ....  ....
        ....  ....
        ....  ....
       W          W
       E          E 
        ....  ....
        ....  ....
        ....  ....
        ....  ....
            SN       */
    for (int i = 0; i < NLENGTH + 2; i++) {
        for (int j = 0; j < NLENGTH + 2; j++) {
            if (i == 0 || j == 0 || i == NLENGTH + 1 || j == NLENGTH + 1) {
                if (j == NLENGTH / 2) {
                    std::cout << "S";
                    outFile << "S";
                }
                else if (j == (NLENGTH / 2) + 1) {
                    std::cout << "N";
                    outFile << "N";
                }
                else if (i == NLENGTH / 2) {
                    std::cout << "W";
                    outFile << "W";
                }
                else if (i == (NLENGTH / 2) + 1) {
                    std::cout << "E";
                    outFile << "E";
                }
                else {
                    std::cout << " ";
                    outFile << " ";
                }
            } else if (
                i != NLENGTH / 2 && 
                i != (NLENGTH / 2) + 1 && 
                j != NLENGTH / 2 && 
                j != (NLENGTH / 2) + 1
            ) {
                std::cout << "□";
                outFile << "□";
            }
            else {
                if (j == NLENGTH / 2 && i != NLENGTH / 2 && i != (NLENGTH / 2) + 1) {
                    if (road[Direction::SOUTH][i - 1]->isOccupied()) {
                        std::cout << getVehicleTypeStr(road[Direction::SOUTH][i - 1]);
                        outFile << getVehicleTypeStr(road[Direction::SOUTH][i - 1]);
                    }
                    else if(road[Direction::SOUTH][i - 1]->isBlocked()) {
                        std::cout << "■";
                        outFile << "■";
                    }
                    else {
                        std::cout << " ";
                        outFile << " ";
                    }
                }
                else if (j == (NLENGTH / 2) + 1 && i != NLENGTH / 2 && i != (NLENGTH / 2) + 1)
                    if (road[Direction::NORTH][NLENGTH - i]->isOccupied()) {
                        std::cout << getVehicleTypeStr(road[Direction::NORTH][NLENGTH - i]);
                        outFile << getVehicleTypeStr(road[Direction::NORTH][NLENGTH - i]);
                    }
                    else if(road[Direction::NORTH][NLENGTH - i]->isBlocked()) {
                        std::cout << "■";
                        outFile << "■";
                    }
                    else {
                        std::cout << " ";
                        outFile << " ";
                    }
                else if (i == NLENGTH / 2)
                    if (road[Direction::WEST][NLENGTH - j]->isOccupied()) {
                        std::cout << getVehicleTypeStr(road[Direction::WEST][NLENGTH - j]);
                        outFile << getVehicleTypeStr(road[Direction::WEST][NLENGTH - j]);
                    }
                    else if(road[Direction::WEST][NLENGTH - j]->isBlocked()) {
                        std::cout << "■";
                        outFile << "■";
                    }
                    else {
                        std::cout << " ";
                        outFile << " ";
                    }
                else if (i == (NLENGTH / 2) + 1)
                    if (road[Direction::EAST][j - 1]->isOccupied()) {
                        std::cout << getVehicleTypeStr(road[Direction::EAST][j - 1]);
                        outFile << getVehicleTypeStr(road[Direction::EAST][j - 1]);
                    }
                    else if(road[Direction::EAST][j - 1]->isBlocked()) {
                        std::cout << "■";
                        outFile << "■";
                    }
                    else {
                        std::cout << " ";
                        outFile << " ";
                    }
                else {
                    std::cout << " ";
                    outFile << " ";
                }
            }
        } 
        std::cout << std::endl;
        outFile << std::endl;
    } 
    std::cout << std:: endl;
    outFile << std::endl;
};

/**
 * Returns the string representation of the vehicle type in the specified space.
 *
 * @param space The space to get the vehicle type from.
 * @return The string representation of the vehicle type.
 */
std::string getVehicleTypeStr(Space* space) {
    Vehicle* vehicle = space->getVehicle();
    if (vehicle != nullptr) {
        if (vehicle->getVehicleType() == VehicleType::CAR)
            return "C";
        else if (vehicle->getVehicleType() == VehicleType::TRUCK)
            return "T";
        else if (vehicle->getVehicleType() == VehicleType::BUS)
            return "B";
        else if (vehicle->getVehicleType() == VehicleType::MOTORCYCLE)
            return "M";
        else
            return "!";
    } else {
        return " ";
    }
}

/**
 * Initializes the random number generator.
 */
void initRand() {
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
}

/**
 * Generates a random direction.
 *
 * @return The random direction.
 */
Direction generateRandomDirection() {
    int randomNum = rand() % 4;
    switch (randomNum) {
        case 0:
            return Direction::NORTH;
        case 1:
            return Direction::EAST;
        case 2:
            return Direction::SOUTH;
        case 3:
            return Direction::WEST;
        default:
            return Direction::NORTH;
    }
}

/**
 * Generates a random vehicle type.
 *
 * @return The random vehicle type.
 */
VehicleType generateRandomVehicle() {
    int randomNum = rand() % 100 + 1;
   
    if (randomNum <= Constants::Vehicle::Car::chance * 100)
        return VehicleType::CAR;
    else if (randomNum <= Constants::Vehicle::Car::chance * 100 + Constants::Vehicle::Truck::chance * 100)
        return VehicleType::TRUCK;
    else if (randomNum <= Constants::Vehicle::Car::chance * 100 + Constants::Vehicle::Truck::chance * 100 + Constants::Vehicle::Bus::chance * 100)
        return VehicleType::BUS;
    else if (randomNum <= Constants::Vehicle::Car::chance * 100 + Constants::Vehicle::Truck::chance * 100 + Constants::Vehicle::Bus::chance * 100 + Constants::Vehicle::Motorcycle::chance * 100)
        return VehicleType::MOTORCYCLE;
    else
        return VehicleType::NONE;
}