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

    RenderWindow window(VideoMode(windowSize.x+1, windowSize.y+1), "Conroy's Game of Life", Style::Titlebar | Style::Close);
    vector<vector<cellState>> cellStates(gridSize.x, vector<cellState>(gridSize.y, Dead));

    RectangleShape cell{};
    cell.setSize(Vector2f(cellSize-1, cellSize-1));
    cell.setOutlineThickness(1);
    cell.setOutlineColor(Color(192, 192, 192));

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

            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::R) {
                for (int x = 0; x < gridSize.x; ++x) {
                    for (int y = 0; y < gridSize.y; ++y) {
                        cellStates[x][y] = Dead;
                    }
                }
            }

            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter) {
                window.setTitle("Conroy's Game of Life | Running");
                while (true) {
                    Event innerEvent{};
                    bool stopLoop = false;
                    while (window.pollEvent(innerEvent)) {
                        if (innerEvent.type == Event::KeyReleased && innerEvent.key.code == Keyboard::Escape) {
                            stopLoop = true;
                            break;
                        }
                    }
                    if (stopLoop) break;

                    chrono::milliseconds duration(10);
                    this_thread::sleep_for(duration);
                    const bool stateChange = updateCellStates(cellStates); // update cell states for next cycle; check if board changed
                    refreshScreen(cellStates, cell, cellSize, gridSize, window);
                    if (!stateChange) {
                        break; // stop if nothing changed this iteration
                    }
                }
                window.setTitle("Conroy's Game of Life");
            }
        }

        refreshScreen(cellStates, cell, cellSize, gridSize, window);

        // window.clear(Color::White);
        // for (int x=0; x<gridSize.x; x++) {
        //     for (int y=0; y<gridSize.y; y++) {
        //         cell.setPosition(x*cellSize+1, y*cellSize+1);
        //         if (cellStates[x][y] == Dead) {
        //             cell.setFillColor(Color::White);
        //         } else if (cellStates[x][y] == Alive) {
        //             cell.setFillColor(Color::Black);
        //         }
        //
        //         window.draw(cell);
        //     }
        // }
        // window.display();
    }

    return 0;
}
