#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using Grid = std::vector<std::vector<char>>;
using Hints = std::vector<std::vector<int>>;

void printGrid(Grid& field) {
    std::cout << "\n   ";
    int m = field[0].size();
    for (int j = 0; j < m; ++j) std::cout << j << " ";
    std::cout << "\n";

    for (int i = 0; i < field.size(); ++i) {
        std::cout << i << ": ";
        for (char c : field[i])
            std::cout << c << " ";
        std::cout << "\n";
    }
}

void printHints(Hints& rowHints, Hints& colHints) {
    std::cout << "\nПодсказки строк:\n";
    for (int i = 0; i < rowHints.size(); ++i) {
        std::cout << i << ": ";
        for (int x : rowHints[i]) std::cout << x << " ";
        std::cout << "\n";
    }

    std::cout << "\nПодсказки столбцов:\n";
    for (int j = 0; j < colHints.size(); ++j) {
        std::cout << j << ": ";
        for (int x : colHints[j]) std::cout << x << " ";
        std::cout << "\n";
    }
}

void printMenu() {
    std::cout << "\n=== НОНОГРАММЫ ===\n"
        << "1. Загрузить задачу из файла\n"
        << "2. Показать поле решения\n"
        << "3. Начать игру\n"
        << "4. Создать свою задачу\n"
        << "0. Выход\n"
        << "Выбор: ";
}

void printInGameMenu() {
    std::cout << "Команды:\n";
    std::cout << " fill x y   - закрасить\n";
    std::cout << " clear x y  - очистить\n";
    std::cout << " solve      - применить решатель\n";
    std::cout << " check      - проверить решение\n";
    std::cout << " show       - показать поле\n";
    std::cout << " commands   - показать команды\n";
    std::cout << " exit       - выход\n";
}

void printGameView(Grid& field, Hints& rowHints, Hints& colHints) {

    int n = field.size();
    int m = field[0].size();

    std::cout << "\n   ";
    for (int j = 0; j < m; ++j) std::cout << j << " ";
    std::cout << "\n";

    for (int i = 0; i < n; ++i) {
        std::cout << i << ": ";
        for (int j = 0; j < m; ++j)
            std::cout << field[i][j] << " ";

        std::cout << "| ";
        for (int x : rowHints[i]) std::cout << x << " ";
        std::cout << "\n";
    }

    std::cout << "----";
    for (int j = 0; j < m; ++j) std::cout << "--";
    std::cout << "\n";

    int maxHints = 0;
    for (auto& h : colHints)
        if (h.size() > maxHints)
            maxHints = h.size();

    for (int k = 0; k < maxHints; ++k) {
        std::cout << "   ";
        for (int j = 0; j < m; ++j) {
            if (k < colHints[j].size())
                std::cout << colHints[j][k] << " ";
            else
                std::cout << "  ";
        }
        std::cout << "\n";
    }

}