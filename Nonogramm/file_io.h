#pragma once
#include <iostream>
#include <vector>
using Grid = std::vector<std::vector<char>>;
using Hints = std::vector<std::vector<int>>;
bool loadPuzzle(std::string& filename, Grid& field);
bool savePuzzle(std::string& filename, Grid& field);
void createPuzzle(Grid& field);