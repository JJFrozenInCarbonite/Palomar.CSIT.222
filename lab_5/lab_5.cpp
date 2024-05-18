/**
 * Lab 5 - Graphs
 * 
 * The program reads vertices from a file and calculates the distance between them. 
 * It then uses Dijkstra's algorithm to find the shortest path between two locations.
 * 
 * @author JJ Hoffmann
 * @version 2024-05-18
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <map>

/**
 * A struct representing a vertex in a graph.
*/
struct Vertex {
    std::string name;
    double x;
    double y;
    std::vector<std::pair<Vertex*, double>> adjacent;
};

/**
 * Calculates the distance between two vertices.
 * 
 * @param v1 The first vertex.
 * @param v2 The second vertex.
 * @return The distance between the two vertices.
*/
double calculateDistance(const Vertex& v1, const Vertex& v2) {
    double dx = v2.x - v1.x;
    double dy = v2.y - v1.y;
    return std::sqrt(dx * dx + dy * dy);
}

/**
 * Reads vertices from a file.
 * 
 * @param filename The name of the file to read from.
 * @return A vector of vertices read from the file.
*/
std::vector<Vertex> readVerticesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Unable to open file " << filename << std::endl;
        exit(1);
    }

    std::vector<Vertex> vertices;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        std::getline(ss, name, ',');

        std::string x_str, y_str;
        std::getline(ss, x_str, ',');
        std::getline(ss, y_str, ',');

        double x = std::stod(x_str);
        double y = std::stod(y_str);

        vertices.push_back({name, x, y, {}});
    }

    file.clear();
    file.seekg(0, std::ios::beg);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        std::getline(ss, name, ',');

        Vertex* current = nullptr;
        for (Vertex& v : vertices) {
            if (v.name == name) {
                current = &v;
                break;
            }
        }

        std::string adjName;
        while (std::getline(ss, adjName, ',')) {
            for (Vertex& v : vertices) {
                if (v.name == adjName) {
                    double distance = calculateDistance(*current, v);
                    current->adjacent.push_back({&v, distance});
                    break;
                }
            }
        }
    }

    return vertices;
}

int main() {
    
    std::vector<Vertex> vertices = readVerticesFromFile("palomarMapEdge.txt");

    std::string startName, endName;
    std::cout << "\nEnter the starting location: ";
    std::getline(std::cin, startName);
    std::cout << "\nEnter the final location: ";
    std::getline(std::cin, endName);

    Vertex* start = nullptr;
    Vertex* end = nullptr;
    for (Vertex& v : vertices) {
        if (v.name == startName) start = &v;
        if (v.name == endName) end = &v;
    }

    if (!start || !end) {
        std::cerr << "Invalid start or end location." << std::endl;
        return 1;
    }

    std::priority_queue<std::pair<double, Vertex*>, std::vector<std::pair<double, Vertex*>>, std::greater<>> queue;
    std::map<Vertex*, double> distances;
    std::map<Vertex*, Vertex*> path;
    distances[start] = 0.0;
    queue.push({0.0, start});

    while (!queue.empty()) {
        Vertex* current = queue.top().second;
        queue.pop();

        for (const auto& adj : current->adjacent) {
            double newDistance = distances[current] + adj.second;
            if (!distances.count(adj.first) || newDistance < distances[adj.first]) {
                distances[adj.first] = newDistance;
                path[adj.first] = current;
                queue.push({newDistance, adj.first});
            }
        }
    }

    if (!distances.count(end)) {
        std::cout << "\nNo path found." << std::endl;
        return 1;
    }

    std::vector<std::string> route;
    for (Vertex* v = end; v != start; v = path[v]) {
        route.push_back(v->name);
    }
    route.push_back(start->name);

    std::cout << "\nRoute: ";
    for (auto it = route.rbegin(); it != route.rend(); ++it) {
        std::cout << *it;
        if (it + 1 != route.rend()) std::cout << " -> ";
    }
    std::cout << std::endl;

    std::cout << "\nTotal distance: " << distances[end] << std::endl << std::endl;

    return 0;
}