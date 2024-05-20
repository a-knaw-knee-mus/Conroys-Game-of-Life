#include "states.h"
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// update alive and dead cells based on Conroy's  constraints
vector<vector<cellState>> updateCellStates(vector<vector<cellState>> cellStates) {
    const int width = cellStates.size(), height = cellStates[0].size();
    vector<vector<cellState>> updatedStates = cellStates;

    // Define possible movement directions (left, right, up, down, topleft, topright, bottomleft, bottomright)
    constexpr int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    constexpr int dy[] = {0, 0, -1, 1, -1, -1, 1, 1};

    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            int aliveNeighbors = 0;
            for (int i=0; i<8; i++) {
                const Vector2i neighbor = {x+dx[i], y+dy[i]};
                if (neighbor.x<0 || neighbor.x>=width || neighbor.y<0 || neighbor.y>=height) continue;
                if (cellStates[neighbor.x][neighbor.y] == Alive) aliveNeighbors++;
            }

            if (cellStates[x][y] == Alive) {
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    updatedStates[x][y] = Dead;
                }
            } else {
                if (aliveNeighbors == 3) {
                    updatedStates[x][y] = Alive;
                }
            }
        }
    }

    return updatedStates;
}