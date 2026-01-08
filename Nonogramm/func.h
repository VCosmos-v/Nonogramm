#pragma once
#include <iostream>
#include <vector>
using Grid = std::vector<std::vector<char>>;
using Hints = std::vector<std::vector<int>>;
std::vector<int> getLineHints(std::vector<char>& line);
void generateHints(Grid& field, Hints& rowHints, Hints& colHints);
bool checkLine(std::vector<char>& line, std::vector<int>& hints);
bool checkSolution(Grid& field, Grid& solution);
void printGrid(Grid& field);
void printHints(Hints& rowHints, Hints& colHints);
void printMenu();
bool loadPuzzle(std::string& filename, Grid& field);
bool savePuzzle(std::string& filename, Grid& field);
void playGame(Grid& solution);
void printGameView(Grid& field, Hints& rowHints, Hints& colHints);
void printInGameMenu();
void createPuzzle(Grid& field);
bool Solver(Grid& field, Grid& solution);
bool readInt(int& value);