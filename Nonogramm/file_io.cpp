#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "func.h"

using Grid = std::vector<std::vector<char>>;
using Hints = std::vector<std::vector<int>>;
bool loadPuzzle(std::string& filename, Grid& field) {
    std::ifstream f;
    f.open(filename, std::ios::in);
    if (!f.is_open()) return false;

    int n, m;
    f >> n >> m;
    field.assign(n, std::vector<char>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            f >> field[i][j];

    return true;
}

bool savePuzzle(std::string& filename, Grid& field) {
    std::ofstream f;
    f.open(filename, std::ios::out);
    if (!f.is_open()) return false;

    int n = field.size(), m = field[0].size();
    f << n << " " << m << "\n";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            f << field[i][j];
        f << "\n";
    }
    return true;
}

void createPuzzle(Grid& field) {
    int n, m;
    std::cout << "Размер поля (n m): ";
    while (!readInt(n) || !readInt(m)) {
        std::cout << "Ошибка: координаты должны быть целыми числами.\n";
        std::cout << "Размер поля (n m): ";
    }

    field.assign(n, std::vector<char>(m, '.'));

    std::cout << "Ввод поля (# или .):\n";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> field[i][j];
            if (field[i][j] != '#' && field[i][j] != '.')
                field[i][j] = '.';
        }
    }

    std::string file;
    std::cout << "Имя файла для сохранения: ";
    std::cin >> file;

    savePuzzle(file, field);
    std::cout << "Задача сохранена.\n";
}