#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "states.h"
using namespace std;
using namespace sf;

void refreshScreen(vector<vector<cellState>>& cellStates, vector<vector<bool>>& visited, RectangleShape& cell, const int cellSize, const Vector2i gridSize, RenderWindow& window, const bool showBorders, const bool showVisited);