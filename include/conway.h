#pragma once
#include "states.h"
#include <vector>
using namespace std;

bool updateCellStates(vector<vector<cellState>>& cellStates, vector<vector<bool>>& visited, const bool screenWrapping);