#include <iostream>
#include <regex>
#include <string>
#include <fstream>

int calc(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return -1;
    }

    std::string input;
    std::getline(file, input, '\0');
    file.close();

    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
    std::smatch matches;

    int sum = 0;
    bool mul_enabled = true; 
    auto searchStart = input.cbegin();
    while (std::regex_search(searchStart, input.cend(), matches, pattern)) {
        std::string match = matches[0].str();

        if (match == "do()") {
            mul_enabled = true;
        } else if (match == "don't()") {
            mul_enabled = false;
        } else if (mul_enabled) {
            int x = std::stoi(matches[1].str());
            int y = std::stoi(matches[2].str());
            sum += x * y;
        }

        searchStart = matches.suffix().first;
    }

    return sum;
}

int main() {
    const std::string filename = "in/input3.txt";
    int result = calc(filename);

    if (result != -1) {
        std::cout << "Sum of all results: " << result << std::endl;
    }

    return 0;
}
