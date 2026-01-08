#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using Grid = std::vector<std::vector<char>>;
using Hints = std::vector<std::vector<int>>;

bool readInt(int& value) {
    std::cin >> value;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}

// Решатель

bool Solver(Grid& field, Grid& solution) {
    static int row = 0;
    if (row >= solution.size()) row = 0;
    for (int i = 0; i < solution[0].size(); i++) {
        field[row][i] = solution[row][i];
    }
    row++;
    return true;
}