// presets the user can choose from that set specific cells throughout the window in different patterns
#include <vector>
#include <SFML/Graphics.hpp>
#include "states.h"
using namespace std;
using namespace sf;

void resetCells(vector<vector<cellState>>& cellStates) {
    for (int x=0; x<cellStates.size(); x++) {
        for (int y=0; y<cellStates[0].size(); y++) {
            cellStates[x][y] = Dead;
        }
    }
}

// vertical line 36 long; dont let it connect from top to bottom
void flowerPreset1(vector<vector<cellState>>& cellStates) {
    resetCells(cellStates);
    Vector2i middleCoord = {int(cellStates.size()/2), int(cellStates[0].size()/2)};

    for (int i=0; i<17; i++) {
        if (middleCoord.y+i < cellStates[0].size()-1) {
            cellStates[middleCoord.x][middleCoord.y+i] = Alive;
        }
        if (middleCoord.y-i >= 1) {
            cellStates[middleCoord.x][middleCoord.y-i] = Alive;
        }
    }
}

// vertical line 17 long; dont let it connect from top to bottom
void flowerPreset2(vector<vector<cellState>>& cellStates) {
    resetCells(cellStates);
    Vector2i middleCoord = {int(cellStates.size()/2), int(cellStates[0].size()/2)};

    for (int i=0; i<8; i++) {
        if (middleCoord.y+i < cellStates[0].size()-1) {
            cellStates[middleCoord.x][middleCoord.y+i] = Alive;
        }
        if (middleCoord.y-i >= 1) {
            cellStates[middleCoord.x][middleCoord.y-i] = Alive;
        }
    }
}

// vertical line 29 long; dont let it connect from top to bottom
void flowerPreset3(vector<vector<cellState>>& cellStates) {
    resetCells(cellStates);
    Vector2i middleCoord = {int(cellStates.size()/2), int(cellStates[0].size()/2)};

    for (int i=0; i<14; i++) {
        if (middleCoord.y+i < cellStates[0].size()-1) {
            cellStates[middleCoord.x][middleCoord.y+i] = Alive;
        }
        if (middleCoord.y-i >= 1) {
            cellStates[middleCoord.x][middleCoord.y-i] = Alive;
        }
    }
}

// vertical line from top to bottom
void barcode(vector<vector<cellState>>& cellStates) {
    resetCells(cellStates);
    Vector2i middleCoord = {int(cellStates.size()/2), int(cellStates[0].size()/2)};

    int i = 0;
    do {
        if (middleCoord.y+i < cellStates[0].size()) {
            cellStates[middleCoord.x][middleCoord.y+i] = Alive;
        }
        if (middleCoord.y-i >= 0) {
            cellStates[middleCoord.x][middleCoord.y-i] = Alive;
        }
        if (middleCoord.y+i >= cellStates[0].size() && middleCoord.y-i < 0) break;
        i++;
    } while (true);
}

void glider(vector<vector<cellState>>& cellStates) {
    resetCells(cellStates);

    cellStates[2][1] = Alive;
    cellStates[3][2] = Alive;
    cellStates[3][3] = Alive;
    cellStates[2][3] = Alive;
    cellStates[1][3] = Alive;
}

void spaceship(vector<vector<cellState>>& cellStates) {
    resetCells(cellStates);

    const int middleY = cellStates[0].size()/2;

    cellStates[1][middleY-1] = Alive;
    cellStates[4][middleY-1] = Alive;
    cellStates[5][middleY] = Alive;
    cellStates[1][middleY+1] = Alive;
    cellStates[5][middleY+1] = Alive;
    cellStates[2][middleY+2] = Alive;
    cellStates[3][middleY+2] = Alive;
    cellStates[4][middleY+2] = Alive;
    cellStates[5][middleY+2] = Alive;
}

void rPentomino(vector<vector<cellState>>& cellStates) {
    resetCells(cellStates);
    Vector2i middleCoord = {int(cellStates.size()/2), int(cellStates[0].size()/2)};

    cellStates[middleCoord.x][middleCoord.y-1] = Alive;
    cellStates[middleCoord.x+1][middleCoord.y-1] = Alive;
    cellStates[middleCoord.x][middleCoord.y] = Alive;
    cellStates[middleCoord.x-1][middleCoord.y] = Alive;
    cellStates[middleCoord.x][middleCoord.y+1] = Alive;
}

void halfAliveRandom(vector<vector<cellState>>& cellStates) {
    for (int x=0; x<cellStates.size(); x++) {
        for (int y=0; y<cellStates[0].size(); y++) {
            int alive = rand() % 2;
            if (alive == 0) cellStates[x][y] = Alive;
            else cellStates[x][y] = Dead;
        }
    }
}

void queenBeeShuttle(vector<vector<cellState>>& cellStates) {
    resetCells(cellStates);

    cellStates[2][5] = Alive;
    cellStates[2][6] = Alive;
    cellStates[3][5] = Alive;
    cellStates[3][6] = Alive;
    cellStates[7][5] = Alive;
    cellStates[8][4] = Alive;
    cellStates[8][6] = Alive;
    cellStates[9][3] = Alive;
    cellStates[9][7] = Alive;
    cellStates[10][4] = Alive;
    cellStates[10][5] = Alive;
    cellStates[10][6] = Alive;
    cellStates[11][2] = Alive;
    cellStates[11][3] = Alive;
    cellStates[11][7] = Alive;
    cellStates[11][8] = Alive;
    cellStates[22][4] = Alive;
    cellStates[22][5] = Alive;
    cellStates[23][4] = Alive;
    cellStates[23][5] = Alive;
}