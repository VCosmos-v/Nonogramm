#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using Grid = std::vector<std::vector<char>>;
using Hints = std::vector<std::vector<int>>;


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

bool checkLine(std::vector<char>& line, std::vector<int>& hints) {
    return getLineHints(line) == hints;
}

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

// Вывод

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


// Работа с файлами

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

// Решатель

bool Solver(Grid& field, Grid& solution) {
    static int row = 0;
    if (row >= solution.size()) return false;
    for (int i = 0; i < solution[0].size(); i++) {
        field[row][i] = solution[row][i];
    }
    row++;
    return true;
}

// Создание своей задачи


void createPuzzle(Grid& field) {
    int n, m;
    std::cout << "Размер поля (n m): ";
    std::cin >> n >> m;

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


// Игра

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
            std::cin >> x >> y;

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