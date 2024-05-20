#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>
#include <filesystem>
using namespace std;
using namespace sf;

enum cellState {
    Dead,
    Alive
};

int main()
{
    const Vector2i windowSize = {800, 500};
    const int cellSize = 10;
    const Vector2i gridSize = {windowSize.x/cellSize, windowSize.y/cellSize};

    RenderWindow window(VideoMode(windowSize.x+1, windowSize.y+1), "Conroy's Game of Life", Style::Titlebar | Style::Close);
    vector<vector<cellState>> cellStates(gridSize.x, vector<cellState>(gridSize.y, Dead));

    RectangleShape cell{};
    cell.setSize(Vector2f(cellSize-1, cellSize-1));
    cell.setOutlineThickness(1);
    cell.setOutlineColor(Color(192, 192, 192));

    bool isLeftMousePressed=false, isRightMousePressed=false;

    while(window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            else if (Mouse::isButtonPressed(Mouse::Left)) {
                Vector2i mousePosition = Mouse::getPosition(window);
                Vector2i cell = {mousePosition.x / cellSize, mousePosition.y / cellSize};
                if (cell.x < 0 || cell.x >= gridSize.x || cell.y < 0 || cell.y >= gridSize.y) continue;
                cellStates[cell.x][cell.y] = Alive;
            }
            else if (Mouse::isButtonPressed(Mouse::Right)) {
                Vector2i mousePosition = Mouse::getPosition(window);
                Vector2i cell = {mousePosition.x / cellSize, mousePosition.y / cellSize};
                if (cell.x < 0 || cell.x >= gridSize.x || cell.y < 0 || cell.y >= gridSize.y) continue;
                cellStates[cell.x][cell.y] = Dead;
            }

            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
                for (int x = 0; x < gridSize.x; ++x) {
                    for (int y = 0; y < gridSize.y; ++y) {
                        cellStates[x][y] = Dead;
                    }
                }
            }
        }

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

    return 0;
}
