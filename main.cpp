#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>
#include <filesystem>
#include "include/states.h"
#include "include/conroy.h"
#include "include/window.h"
using namespace std;
using namespace sf;

int main()
{
    const Vector2i windowSize = {800, 500};
    const int cellSize = 10;
    const Vector2i gridSize = {windowSize.x/cellSize, windowSize.y/cellSize};
    bool screenWrapping = true; // toroidal wrapping

    RenderWindow window(VideoMode(windowSize.x+1, windowSize.y+1), "Conroy's Game of Life", Style::Titlebar | Style::Close);
    vector<vector<cellState>> cellStates(gridSize.x, vector<cellState>(gridSize.y, Dead));

    RectangleShape cell{};
    cell.setSize(Vector2f(cellSize-1, cellSize-1));
    cell.setOutlineThickness(1);
    cell.setOutlineColor(Color(224, 224, 224));

    while(window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // toggle wrapping
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::W) {
                screenWrapping = !screenWrapping;
            }

            // add cells
            else if (Mouse::isButtonPressed(Mouse::Left)) {
                Vector2i mousePosition = Mouse::getPosition(window);
                Vector2i cellClicked = {mousePosition.x / cellSize, mousePosition.y / cellSize};
                if (cellClicked.x < 0 || cellClicked.x >= gridSize.x || cellClicked.y < 0 || cellClicked.y >= gridSize.y) continue;
                cellStates[cellClicked.x][cellClicked.y] = Alive;
            }

            // delete cells
            else if (Mouse::isButtonPressed(Mouse::Right)) {
                Vector2i mousePosition = Mouse::getPosition(window);
                Vector2i cellClicked = {mousePosition.x / cellSize, mousePosition.y / cellSize};
                if (cellClicked.x < 0 || cellClicked.x >= gridSize.x || cellClicked.y < 0 || cellClicked.y >= gridSize.y) continue;
                cellStates[cellClicked.x][cellClicked.y] = Dead;
            }

            // reset
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::R) {
                for (int x = 0; x < gridSize.x; ++x) {
                    for (int y = 0; y < gridSize.y; ++y) {
                        cellStates[x][y] = Dead;
                    }
                }
            }

            // begin run
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter) {
                window.setTitle("Conroy's Game of Life | Running");
                while (true) {
                    Event innerEvent{};
                    bool stopLoop = false;
                    while (window.pollEvent(innerEvent)) {
                        // pause run
                        if (innerEvent.type == Event::KeyReleased && innerEvent.key.code == Keyboard::Escape) {
                            stopLoop = true;
                            break;
                        }
                    }
                    if (stopLoop) break;

                    chrono::milliseconds duration(10);
                    this_thread::sleep_for(duration);
                    const bool stateChange = updateCellStates(cellStates, screenWrapping); // update cell states for next cycle; check if board changed
                    refreshScreen(cellStates, cell, cellSize, gridSize, window);
                    if (!stateChange) { // stop if nothing changed this iteration
                        break;
                    }
                }
                window.setTitle("Conroy's Game of Life");
            }
        }

        refreshScreen(cellStates, cell, cellSize, gridSize, window);
    }

    return 0;
}
