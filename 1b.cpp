#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

long long calculateSimilarityScore(const std::vector<int>& leftList, const std::vector<int>& rightList) {
    // create a frequency map for the right list
    std::unordered_map<int, int> frequencyMap;
    for (int num : rightList) {
        frequencyMap[num]++;
    }

    // calc the similarity score
    long long similarityScore = 0;
    for (int num : leftList) {
        similarityScore += num * frequencyMap[num];
    }

    return similarityScore;
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

    // calc and output the similarity score
    long long similarityScore = calculateSimilarityScore(leftList, rightList);
    std::cout << "Similarity score between the lists: " << similarityScore << std::endl;

    return 0;
}
