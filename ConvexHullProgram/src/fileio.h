#ifndef FILEIO_H
#define FILEIO_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "convexhull.h"

inline void exportPoints(const std::string& filename, const std::vector<Point>& points, float width, float height) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& p : points) {
            float px = (p.x + 1.f) * (width / 2.0f);
            float py = (1.f - p.y) * (height / 2.0f);
            outFile << px << ',' << py << "\n";
        }
        outFile.close();
        std::cout << "Points exported to " << filename << std::endl;
    }                                                              
    else {
        std::cerr << "Failed to open file for export: " << filename << std::endl;
    }
}

inline void importPoints(const std::string& filename, std::vector<Point>& points, std::vector<Point>& hull, float width, float height) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        points.clear();
        hull.clear();
        std::string line;
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string xStr, yStr;
            if (std::getline(ss, xStr, ',') && std::getline(ss, yStr)) {
                try {
                    float px = std::stof(xStr), py = std::stof(yStr);
                    float nx = px / (width / 2.f) - 1.f;
                    float ny = 1.f - py / (height / 2.f);
                    points.push_back({ nx, ny });
                }
                catch (...) {
                    continue;
                }
            }
        }
        inFile.close();
        std::cout << "Points imported from " << filename << std::endl;
    }
    else {
        std::cerr << "Failed to open file for import: " << filename << std::endl;
    }
}

#endif
