// NearestNeighbor.hpp
#ifndef NEAREST_NEIGHBOR_HPP
#define NEAREST_NEIGHBOR_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cmath>
#include <limits>
#include <algorithm>
#include <sstream>


class NODE {
public:
    NODE(int id, double x, double y) : id_(id), x_(x), y_(y) {}

    int getId(){ 
            return id_; 
        }
    double getX(){ 
            return x_; 
        }
    double getY(){ 
            return y_; 
        }

    static double distance(const NODE& a, const NODE& b) {
        return sqrt((a.x_ - b.x_) * (a.x_ - b.x_) + (a.y_ - b.y_)  * (a.y_ - b.y_));
    }

private:
    int id_;
    double x_;
    double y_;
};


std::vector<NODE> read(const std::string &filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << std::endl;
        return {};
    }

    std::vector<NODE> nodes;
    std::string line;
    int id;
    double x, y;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (!(iss >> id >> x >> y)) {
            continue; 
        }
        nodes.emplace_back(id, x, y);
    }

    return nodes;
}

void nearestNeighbor(const std::string &filename) {
    auto nodes = read(filename);
    std::vector<bool> seen(nodes.size(), false);
    std::vector<int> path;
    double tot = 0.0;
    auto current = nodes.begin();
    path.push_back(current->getId());
    seen[current - nodes.begin()] = true;

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 1; i < nodes.size(); ++i) {
        auto nearest = nodes.end();
        double min = std::numeric_limits<double>::max();

        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            if (!seen[it - nodes.begin()]) {
                double distance = NODE::distance(*current, *it);
                if (distance < min) {
                    nearest = it;
                    min = distance;
                }
            }
        }

        seen[nearest - nodes.begin()] = true;
        tot += min;
        path.push_back(nearest->getId());
        current = nearest;
    }

    tot += NODE::distance(*current, nodes.front()); 
    path.push_back(nodes.front().getId());

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    for (int id : path) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
    std::cout << "Total Distance: " << tot << std::endl;
    std::cout << "Time in ms: " << duration.count() << std::endl;
}

//Total Distance: 1.03496e+06
//Time in ms: 5912


#endif // NEAREST_NEIGHBOR_HPP
