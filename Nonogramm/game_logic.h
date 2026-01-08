#pragma once
#include <iostream>
#include <vector>
using Grid = std::vector<std::vector<char>>;
using Hints = std::vector<std::vector<int>>;
std::vector<int> getLineHints(std::vector<char>& line);
void generateHints(Grid& field, Hints& rowHints, Hints& colHints);
bool checkLine(std::vector<char>& line, std::vector<int>& hints);
bool checkSolution(Grid& field, Grid& solution);
bool checkWin(Grid& field, Grid& solution);
void playGame(Grid& solution);