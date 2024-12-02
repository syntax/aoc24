#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

bool is_safe_no_dampener(const std::vector<int>& report) {
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
        } else {
            return false;
        }
    }

    return increasing || decreasing;
}

bool is_safe_with_dampener(const std::vector<int>& report) {
    for (int remove_pos = -1; remove_pos < (int)report.size(); ++remove_pos) {
        std::vector<int> modified_report;
        if (remove_pos == -1) {
            modified_report = report;
        } else {
            modified_report = report;
            modified_report.erase(modified_report.begin() + remove_pos);
        }
        if (is_safe_no_dampener(modified_report)) {
            return true;
        }
    }
    return false;
}

long long safe_reports(const std::vector<std::vector<int> >& reports) {
    long long legit = 0;
    for (const auto& report : reports) {
        if (is_safe_with_dampener(report)) {
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
