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
#include "include/presets.h"
using namespace std;
using namespace sf;

int main()
{
    const Vector2i windowSize = {800, 500};
    const vector<int> cellSizes = {4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30}; // px size per cell
    int cellSizeIdx = 3;
    Vector2i gridSize = {windowSize.x/cellSizes[cellSizeIdx], windowSize.y/cellSizes[cellSizeIdx]};
    bool screenWrapping = true; // toroidal wrapping
    bool showBoarders = true;

    RenderWindow window(VideoMode(windowSize.x+1, windowSize.y+1), "Conroy's Game of Life", Style::Titlebar | Style::Close);
    vector<vector<cellState>> cellStates(gridSize.x, vector<cellState>(gridSize.y, Dead));
    vector<vector<cellState>> lastState{}; // save position before running to reference back to

    RectangleShape cell{};
    cell.setSize(Vector2f(cellSizes[cellSizeIdx]-1, cellSizes[cellSizeIdx]-1));
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

            // toggle borders
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::B) {
                showBoarders = !showBoarders;
            }

            // change cell size
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up) {
                if (cellSizeIdx+1 >= cellSizes.size()) continue;
                cellSizeIdx += 1;
                gridSize = {windowSize.x/cellSizes[cellSizeIdx], windowSize.y/cellSizes[cellSizeIdx]};

                cellStates.resize(gridSize.x);
                for (vector<cellState>& row: cellStates) {
                    row.resize(gridSize.y, Dead);
                }
                lastState.clear();
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down) {
                if (cellSizeIdx-1 < 0) continue;
                cellSizeIdx -= 1;
                gridSize = {windowSize.x/cellSizes[cellSizeIdx], windowSize.y/cellSizes[cellSizeIdx]};

                cellStates.resize(gridSize.x);
                for (vector<cellState>& row: cellStates) {
                    row.resize(gridSize.y, Dead);
                }
                lastState.clear();
            }

            // add cells
            else if (Mouse::isButtonPressed(Mouse::Left)) {
                Vector2i mousePosition = Mouse::getPosition(window);
                Vector2i cellClicked = {mousePosition.x / cellSizes[cellSizeIdx], mousePosition.y / cellSizes[cellSizeIdx]};
                if (cellClicked.x < 0 || cellClicked.x >= gridSize.x || cellClicked.y < 0 || cellClicked.y >= gridSize.y) continue;
                cellStates[cellClicked.x][cellClicked.y] = Alive;
            }

            // delete cells
            else if (Mouse::isButtonPressed(Mouse::Right)) {
                Vector2i mousePosition = Mouse::getPosition(window);
                Vector2i cellClicked = {mousePosition.x / cellSizes[cellSizeIdx], mousePosition.y / cellSizes[cellSizeIdx]};
                if (cellClicked.x < 0 || cellClicked.x >= gridSize.x || cellClicked.y < 0 || cellClicked.y >= gridSize.y) continue;
                cellStates[cellClicked.x][cellClicked.y] = Dead;
            }

            // reset to last position before a run was executed
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::R) {
                if (!lastState.empty()) cellStates = lastState;
            }

            // delete all cells
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Delete) {
                for (int x = 0; x < gridSize.x; ++x) {
                    for (int y = 0; y < gridSize.y; ++y) {
                        cellStates[x][y] = Dead;
                    }
                }
            }

            // set preset
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num1) {
                flowerPreset1(cellStates);
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num2) {
                flowerPreset2(cellStates);
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num3) {
                flowerPreset3(cellStates);
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num4) {
                barcode(cellStates);
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num5) {
                glider(cellStates);
            }
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num6) {
                spaceship(cellStates);
            }

            // animate one cycle
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::N) {
                const bool _ = updateCellStates(cellStates, screenWrapping); // update cell states for next cycle; check if board changed
                refreshScreen(cellStates, cell, cellSizes[cellSizeIdx], gridSize, window, showBoarders);
            }

            // begin run
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter) {
                window.setTitle("Conroy's Game of Life | Running");
                lastState = cellStates;
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
                    refreshScreen(cellStates, cell, cellSizes[cellSizeIdx], gridSize, window, showBoarders);
                    if (!stateChange) { // stop if nothing changed this iteration
                        break;
                    }
                }
                window.setTitle("Conroy's Game of Life");
            }

            // save screenshot
            else if (event.type == Event::KeyReleased && event.key.code == Keyboard::P) {
                Texture texture;
                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);

                time_t now = time(nullptr);
                tm localTime = *localtime(&now);
                stringstream ss;
                ss << put_time(&localTime, "%Y-%m-%d_%H-%M-%S");
                const string suffix = ss.str();

                if (!filesystem::exists("screenshots")) {
                    filesystem::create_directory("screenshots");
                }
                if (texture.copyToImage().saveToFile("screenshots/conroy-" + suffix + ".png")) {
                    cout << "Screenshot saved" << endl;
                } else {
                    cerr << "Failed to save screenshot" << endl;
                }
            }
        }

        refreshScreen(cellStates, cell, cellSizes[cellSizeIdx], gridSize, window, showBoarders);
    }

    return 0;
}
