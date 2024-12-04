#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

int wordOccurances(const vector<string>& grid, const string& word) {
    int rows = grid.size();
    int cols = grid[0].size();
    int wordLen = word.length();
    int count = 0;

    vector<pair<int, int>> directions = {
        {0, 1}, {0, -1}, // Horizontal
        {1, 0}, {-1, 0}, // Vertical
        {1, 1}, {1, -1}, // Diagonal down
        {-1, 1}, {-1, -1} // Diagonal up
    };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // only proceed if the first letter of the word is found
            if (grid[i][j] == word[0]) {
                for (auto& dir : directions) {
                    int x = i;
                    int y = j;
                    int k = 0;

                    while (k < wordLen) {
                        if (!isValid(x, y, rows, cols) || grid[x][y] != word[k]) {
                            break;
                        }

                        x += dir.first;
                        y += dir.second;
                        k++;
                    }

                    if (k == wordLen) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    ifstream inputFile("in/input4.txt");
    if (!inputFile) {
        cerr << "Error: Could not open the file in/input4.txt" << endl;
        return 1;
    }

    vector<string> grid;
    string line;

    while (getline(inputFile, line)) {
        grid.push_back(line);
    }
    inputFile.close();

    string word = "XMAS";
    int occurrences = wordOccurances(grid, word);

    cout << "The word '" << word << "' occurs " << occurrences << " times in the grid." << endl;

    return 0;
}
