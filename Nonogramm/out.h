#pragma once
#include <iostream>
#include <vector>
using Grid = std::vector<std::vector<char>>;
using Hints = std::vector<std::vector<int>>;
void printGrid(Grid& field);
void printHints(Hints& rowHints, Hints& colHints);
void printMenu();
void printGameView(Grid& field, Hints& rowHints, Hints& colHints);
void printInGameMenu();