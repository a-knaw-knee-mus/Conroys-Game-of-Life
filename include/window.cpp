#include <SFML/Graphics.hpp>
#include <vector>
#include "states.h"
using namespace std;
using namespace sf;

void refreshScreen(vector<vector<cellState>>& cellStates, RectangleShape& cell, const int cellSize, const Vector2i gridSize, RenderWindow& window) {
    window.clear(Color::White);
    for (int x=0; x<gridSize.x; x++) {
        for (int y=0; y<gridSize.y; y++) {
            cell.setPosition(x*cellSize+1, y*cellSize+1);
            if (cellStates[x][y] == Dead) {
                cell.setFillColor(Color::White);
            } else if (cellStates[x][y] == Alive) {
                cell.setFillColor(Color::Black);
            }

            window.draw(cell);
        }
    }
    window.display();
}
