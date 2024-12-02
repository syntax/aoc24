#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

bool is_safe(const std::vector<int>& report) {
    if (report.size() < 2) {
        return true;
    }

    bool increasing = true;
    bool decreasing = true;

    for (size_t i = 1; i < report.size(); ++i) {
        int diff = report[i] - report[i - 1];
        if (std::abs(diff) < 1 || std::abs(diff) > 3) {
            return false;
        }
        if (diff > 0) {
            decreasing = false;
        } else if (diff < 0) {
            increasing = false;
        }
    }

    return increasing || decreasing;
}

long long safe_reports(const std::vector<std::vector<int> >& reports) {
    long long legit = 0;
    for (const auto& report : reports) {
        if (is_safe(report)) {
            ++legit;
        }
    }
    return legit;
}

int main() {
    std::ifstream inputFile("in/input2.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    std::vector<std::vector<int> > reports;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<int> report;
        int number;
        while (iss >> number) {
            report.push_back(number);
        }
        if (!report.empty()) {
            reports.push_back(report);
        }
    }

    inputFile.close();

    long long legit = safe_reports(reports);
    std::cout << "Number of safe reports: " << legit << std::endl;

    return 0;
}
