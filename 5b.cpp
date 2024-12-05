#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

// this could well be overengineered !!


std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    return result;
}

std::unordered_map<int, std::unordered_set<int>> buildDependencyGraph(const std::vector<std::pair<int, int>> &rules) {
    std::unordered_map<int, std::unordered_set<int>> graph;
    for (const auto &rule : rules) {
        graph[rule.first].insert(rule.second);
    }
    return graph;
}

bool isInvalidUpdate(const std::vector<int> &update, const std::unordered_map<int, std::unordered_set<int>> &graph) {
    std::unordered_map<int, int> position;
    for (size_t i = 0; i < update.size(); ++i) {
        position[update[i]] = i;
    }
    for (const auto &[key, dependencies] : graph) {
        if (position.find(key) != position.end()) {
            for (int dependent : dependencies) {
                if (position.find(dependent) != position.end() && position[key] > position[dependent]) {
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<int> fixUpdate(const std::vector<int> &update, const std::unordered_map<int, std::unordered_set<int>> &graph) {
    std::unordered_map<int, int> position;
    for (size_t i = 0; i < update.size(); ++i) {
        position[update[i]] = i;
    }

    // perform a topological sort based on the dependency graph
    std::unordered_map<int, int> indegree;
    std::unordered_map<int, std::unordered_set<int>> subGraph;

    for (const auto &page : update) {
        indegree[page] = 0;
        subGraph[page] = {};
    }

    // buiding up a subgraph for only the nodes in the current update
    for (const auto &[key, dependencies] : graph) {
        if (position.find(key) != position.end()) {
            for (int dependent : dependencies) {
                if (position.find(dependent) != position.end()) {
                    subGraph[key].insert(dependent);
                    indegree[dependent]++;
                }
            }
        }
    }

    // topology sort using Kahns algorithm
    std::vector<int> result;
    std::vector<int> queue;

    for (const auto &[node, degree] : indegree) {
        if (degree == 0) {
            queue.push_back(node);
        }
    }

    while (!queue.empty()) {
        int current = queue.back();
        queue.pop_back();
        result.push_back(current);

        for (int neighbor : subGraph[current]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                queue.push_back(neighbor);
            }
        }
    }

    return result;
}


int main() {
    std::ifstream inputFile("in/input5.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the input file." << std::endl;
        return 1;
    }

    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;

    std::string line;

    while (std::getline(inputFile, line)) {
        if (line.empty())
            break;
        auto parts = split(line, '|');
        rules.emplace_back(std::stoi(parts[0]), std::stoi(parts[1]));
    }

    while (std::getline(inputFile, line)) {
        if (line.empty())
            continue;
        auto parts = split(line, ',');
        std::vector<int> update;
        for (const auto &p : parts) {
            update.push_back(std::stoi(p));
        }
        updates.push_back(update);
    }

    inputFile.close();

    auto graph = buildDependencyGraph(rules);

    int middleSum = 0;

    for (const auto &update : updates) {
        if (isInvalidUpdate(update, graph)) {
            std::vector<int> ammendedUpdate = fixUpdate(update, graph);
            middleSum += ammendedUpdate[ammendedUpdate.size() / 2];
        }
    }

    std::cout << "Sum of middle page numbers: " << middleSum << std::endl;

    return 0;
}
