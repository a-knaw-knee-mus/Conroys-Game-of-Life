#include <SFML/Graphics.hpp>
#include <vector>
#include "states.h"
using namespace std;
using namespace sf;

void refreshScreen(vector<vector<cellState>>& cellStates, vector<vector<bool>>& visited, RectangleShape& cell, const int cellSize, const Vector2i gridSize, RenderWindow& window, const bool showBorders, const bool showVisited) {
    window.clear(Color::White);
    for (int x=0; x<gridSize.x; x++) {
        for (int y=0; y<gridSize.y; y++) {
            if (cellStates[x][y] == Alive) {
                cell.setSize(Vector2f(cellSize, cellSize));
                cell.setPosition(x*cellSize, y*cellSize);
                cell.setOutlineThickness(0);
                cell.setFillColor(Color::Black);
            } else if (showVisited && visited[x][y]) {
                if (showBorders) {
                    cell.setPosition(x*cellSize+1, y*cellSize+1);
                    cell.setSize(Vector2f(cellSize-1, cellSize-1));
                    cell.setOutlineThickness(1);
                } else {
                    cell.setPosition(x*cellSize, y*cellSize);
                    cell.setSize(Vector2f(cellSize, cellSize));
                    cell.setOutlineThickness(0);
                }
                cell.setFillColor(Color(255, 229, 204));
            } else if (cellStates[x][y] == Dead) {
                if (showBorders) {
                    cell.setPosition(x*cellSize+1, y*cellSize+1);
                    cell.setSize(Vector2f(cellSize-1, cellSize-1));
                    cell.setOutlineThickness(1);
                } else {
                    cell.setPosition(x*cellSize, y*cellSize);
                    cell.setSize(Vector2f(cellSize, cellSize));
                    cell.setOutlineThickness(0);
                }
                cell.setFillColor(Color::White);
            }

            window.draw(cell);
        }
    }
    window.display();
}
