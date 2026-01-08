#include <iostream>
#include <vector>
#include <string>
#include "func.h"
#include "out.h"
#include "file_io.h"

using Grid = std::vector<std::vector<char>>;
using Hints = std::vector<std::vector<int>>;

// Подсказки в линии
std::vector<int> getLineHints(std::vector<char>& line) {
    std::vector<int> hints;
    int cnt = 0;
    for (char c : line) {
        if (c == '#') cnt++;
        else if (cnt) {
            hints.push_back(cnt);
            cnt = 0;
        }
    }
    if (cnt) hints.push_back(cnt);
    if (hints.empty()) hints.push_back(0);
    return hints;
}

// Подсказки на поле
void generateHints(Grid& field, Hints& rowHints, Hints& colHints) {
    int n = field.size(), m = field[0].size();
    rowHints.clear(); colHints.clear();

    for (int i = 0; i < n; ++i)
        rowHints.push_back(getLineHints(field[i]));

    for (int j = 0; j < m; ++j) {
        std::vector<char> col(n);
        for (int i = 0; i < n; ++i) col[i] = field[i][j];
        colHints.push_back(getLineHints(col));
    }
}

// Проверка на ошибки
bool checkSolution(Grid& field, Grid& solution) {
    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field[0].size(); j++) {
            if (solution[i][j] == '.' && field[i][j] == '#') {
                return false;
            }
        }
    }
    return true;
}

// Проверка на победу
bool checkWin(Grid& field, Grid& solution) {
    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field[0].size(); j++) {
            if (field[i][j] != solution[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Геймплей
void playGame(Grid& solution) {
    int n = solution.size();
    int m = solution[0].size();

    Hints rowHints, colHints;
    generateHints(solution, rowHints, colHints);

    Grid player(n, std::vector<char>(m, '.'));

    std::string cmd;

    std::cout << "\n=== ИГРА ===\n";
    printInGameMenu();

    printGameView(player, rowHints, colHints);
    bool win = false;
    while (true) {
        std::cout << "\n> ";
        std::cin >> cmd;

        if (cmd == "exit") break;

        else if (cmd == "commands") {
            printInGameMenu();
        }

        else if (cmd == "show") {
            printGameView(player, rowHints, colHints);
        }

        else if (cmd == "solve") {
            if (Solver(player, solution))
                std::cout << "Решена следующая строка.\n";
            else
                std::cout << "Нет строки для решения.\n";

            printGameView(player, rowHints, colHints);
            win = checkWin(player, solution);
            if (win) {
                std::cout << "Задача решена!";
                break;
            }
        }

        else if (cmd == "check") {
            if (checkSolution(player, solution))
                std::cout << "Решение верное!\n";
            else
                std::cout << "Есть ошибки.\n";
        }

        else if (cmd == "fill" || cmd == "clear") {
            int x, y;

            if (!readInt(x) || !readInt(y)) {
                std::cout << "Ошибка: координаты должны быть целыми числами.\n";
                continue;
            }

            if (x < 0 || x >= m || y < 0 || y >= n) {
                std::cout << "Неверные координаты!\n";
                continue;
            }

            if (cmd == "fill") player[y][x] = '#';
            else player[y][x] = '.';

            printGameView(player, rowHints, colHints);
            win = checkWin(player, solution);
            if (win) {
                std::cout << "Задача решена!";
                break;
            }
        }

        else {
            std::cout << "Неизвестная команда.\n";
        }
    }
}