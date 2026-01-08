#include <locale.h>
#include "func.h"

int main() {
    setlocale(LC_ALL, "ru");
    Grid solution;
    Hints rowHints, colHints;
    int a;
    std::string file;
    bool hasPuzzle = false;
    int choice = 1;

    while (choice != 0) {
        printMenu();
        std::cin >> choice;
        switch (choice) {
        case 0: break;

        case 1:
            std::cout << "Имя файла: ";
            std::cin >> file;

            if (!loadPuzzle(file, solution)) {
                std::cout << "Ошибка загрузки!\n";
                continue;
            }

            generateHints(solution, rowHints, colHints);
            hasPuzzle = true;
            std::cout << "Задача загружена.\n";
            break;

        case 2:
            if (!hasPuzzle) {
                std::cout << "Сначала загрузите задачу!\n";
                break;
            }
            std::cout << "\nПоле:\n";
            printGrid(solution);
            break;

        case 3:
            if (!hasPuzzle) {
                std::cout << "Сначала загрузите задачу!\n";
                break;
            }
            playGame(solution);
            break;

        default:
            std::cout << "Неверный пункт меню!\n";
            break;
        }
    }

    return 0;
}