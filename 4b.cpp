#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

int wordXMASOccurrences(const vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // proceed if the central letter correct
            if (grid[i][j] == 'A') {
                if (isValid(i - 1, j - 1, rows, cols) && isValid(i + 1, j + 1, rows, cols) &&
                    isValid(i - 1, j + 1, rows, cols) && isValid(i + 1, j - 1, rows, cols)) {

                    char diag1_char1 = grid[i - 1][j - 1];
                    char diag1_char2 = grid[i + 1][j + 1];
                    char diag2_char1 = grid[i - 1][j + 1];
                    char diag2_char2 = grid[i + 1][j - 1];

                    // check if the outer letters of diag1 are 'M' and 'S' in any order
                    bool diag1_match = ((diag1_char1 == 'M' && diag1_char2 == 'S') ||
                                        (diag1_char1 == 'S' && diag1_char2 == 'M'));

                    // check if the outer letters of diag2 are 'M' and 'S' in any order
                    bool diag2_match = ((diag2_char1 == 'M' && diag2_char2 == 'S') ||
                                        (diag2_char1 == 'S' && diag2_char2 == 'M'));

                    if (diag1_match && diag2_match) {
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

    int occurrences = wordXMASOccurrences(grid);

    cout << "The pattern occurs " << occurrences << " times in the grid." << endl;

    return 0;
}
