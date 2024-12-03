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

    std::regex pattern(R"(\bmul\((\d{1,3}),(\d{1,3})\))");
    std::smatch matches;
    int sum = 0;

    auto searchStart = input.cbegin();
    while (std::regex_search(searchStart, input.cend(), matches, pattern)) {
        int x = std::stoi(matches[1]);
        int y = std::stoi(matches[2]);
        sum += x * y;

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
