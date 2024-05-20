#include "states.h"
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// update alive and dead cells based on Conroy's  constraints; return bool if there has been a state change
bool updateCellStates(vector<vector<cellState>>& cellStates, const bool screenWrapping) {
    const int width = cellStates.size(), height = cellStates[0].size();
    const vector<vector<cellState>> currStates = cellStates;

    // Define possible movement directions (left, right, up, down, topleft, topright, bottomleft, bottomright)
    constexpr int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    constexpr int dy[] = {0, 0, -1, 1, -1, -1, 1, 1};

    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            int aliveNeighbors = 0;
            for (int i=0; i<8; i++) {
                Vector2i neighbor = {x+dx[i], y+dy[i]};
                if (!screenWrapping) { // out of bounds with no wrapping just ignore
                    if (neighbor.x<0 || neighbor.x>=width || neighbor.y<0 || neighbor.y>=height) continue;
                } else {
                    if (neighbor.x<0) neighbor.x = width-1; // wrap left around to right
                    if (neighbor.x>width-1) neighbor.x = 0; // wrap right around to left
                    if (neighbor.y<0) neighbor.y = height-1; // wrap top around to bottom
                    if (neighbor.y>height-1) neighbor.y = 0; // wrap bottom around to top
                }
                if (currStates[neighbor.x][neighbor.y] == Alive) aliveNeighbors++;
            }

            if (currStates[x][y] == Alive) {
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    cellStates[x][y] = Dead;
                }
            } else {
                if (aliveNeighbors == 3) {
                    cellStates[x][y] = Alive;
                }
            }
        }
    }

    return currStates != cellStates; // if new state != old state, then there has been a state change; else no state change
}