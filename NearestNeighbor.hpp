// NearestNeighbor.hpp
#ifndef NEAREST_NEIGHBOR_HPP
#define NEAREST_NEIGHBOR_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>

class NODE {
public:
    int id;
    double x, y;

    NODE(int id, double x, double y) : id(id), x(x), y(y) {}

    double distance(const NODE& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

class NearestNeighbor {
public:
    static void nearestNeighbor(std::string filename) {
        std::vector<NODE> nodes = readTSPFile(filename);

        std::vector<int> tour;
        tour.push_back(1); // Start with node 1
        double totalDistance = 0.0;

        auto startTime = std::chrono::high_resolution_clock::now();

        while (tour.size() < nodes.size()) {
            int currentCity = tour.back();
            int nearestNeighbor = findNearestNeighbor(currentCity, nodes, tour);
            tour.push_back(nearestNeighbor);
            totalDistance += nodes[currentCity - 1].distance(nodes[nearestNeighbor - 1]);
        }

        // Add distance from last node back to node 1
        totalDistance += nodes[tour.back() - 1].distance(nodes[0]);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        // Print the tour
        for (int city : tour) {
            std::cout << city << " ";
        }
        std::cout << std::endl;

        // Print total distance and time
        std::cout << "Total Distance: " << totalDistance << std::endl;
        std::cout << "Time in ms: " << duration.count() << std::endl;
    }

private:
    static std::vector<NODE> readTSPFile(const std::string& filename) {
        std::ifstream file(filename);
        int id;
        double x, y;
        std::vector<NODE> nodes;

        while (file >> id >> x >> y) {
            nodes.emplace_back(id, x, y);
        }

        return nodes;
    }

    static int findNearestNeighbor(int currentCity, const std::vector<NODE>& nodes, const std::vector<int>& tour) {
        int nearestNeighbor = -1;
        double minDistance = std::numeric_limits<double>::infinity();

        for (const NODE& node : nodes) {
            if (std::find(tour.begin(), tour.end(), node.id) == tour.end()) {
                double dist = nodes[currentCity - 1].distance(node);
                if (dist < minDistance) {
                    minDistance = dist;
                    nearestNeighbor = node.id;
                }
            }
        }

        return nearestNeighbor;
    }
};

#endif // NEAREST_NEIGHBOR_HPP

