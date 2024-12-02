#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

int calculateTotalDistance(std::vector<int>& leftList, std::vector<int>& rightList) {
    // sort both lists
    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    // calc the total distance
    int totalDistance = 0;
    for (size_t i = 0; i < leftList.size(); ++i) {
        totalDistance += std::abs(leftList[i] - rightList[i]);
    }
    return totalDistance;
}

int main() {
    std::ifstream inputFile("input1.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    std::vector<int> leftList, rightList;
    std::string line;

    // parse the input file
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int left, right;
        if (iss >> left >> right) {
            leftList.push_back(left);
            rightList.push_back(right);
        }
    }

    inputFile.close();

    // calc and output the total distance
    int totalDistance = calculateTotalDistance(leftList, rightList);
    std::cout << "Total distance between the lists: " << totalDistance << std::endl;

    return 0;
}
