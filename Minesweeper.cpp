/*
Autorius: Tomas Petrikas (tomas.petrikas99@gmail.com)
2019

Taip pavyko kad cia kazkur uzsipainiojau su koordinatemis ir dabar height yra
plotis, o width yra aukstis. Visa kita (kas siuo momentu yra) lyg ir veikia.
*/

#include "Minesweeper.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
using namespace std;

// Maziausi ir didziausi leidziami lentos plociai/auksciai
#define MIN_SIZE 8
#define MAX_SIZE 30

// Maziausias ir didziausias leidziamas minu tankumas
#define MIN_DENSITY 0.00
#define MAX_DENSITY 0.95

/*****************************************************************************/

string Player::getName() {
    return name;
}

Player::Player(string n) {
    //cout << "Player constructor\n";

    // Vardas privalo tureti 1-20 simboliu
    if (n.length() >= 1 && n.length() <= 20) {
        name = n;
    }
    else if (n.length() == 0) {
        throw "Error: name must be non-empty";
    }
    else {
        throw "Error: name too long";
    }
}

Player::~Player() {
    //cout << "Player destructor\n";
}

/*****************************************************************************/

// Jei setMine() naudojamas be parametru, manoma kad norime mina prideti
void Cell::setMine() {
    mine = true;
}
// Kitu atveju galime patikslinti
void Cell::setMine(bool m) {
    mine = m;
}
bool Cell::isMine() {
    return mine;
}

// Kintamaji "covered" galima perjungineti arba tiesiog nustatyti
void Cell::toggleCovered() {
    covered = !covered;
}
void Cell::setCovered(bool c) {
    covered = c;
}
bool Cell::isCovered() {
    return covered;
}

// Analogiskai su "flagged"
void Cell::toggleFlagged() {
    flagged = !flagged;
}
void Cell::setFlagged(bool f) {
    flagged = f;
}
bool Cell::isFlagged() {
    return flagged;
}

// Prie "neighbors" galima prideti 1 arba nustatyti
void Cell::incrementNeighbors() {
    ++neighbors;
}
void Cell::setNeighbors(int n) {
    // Jei cell turi mina, sakome kad turi -1 kaimina
    if (n < -1) {
        throw "Error: cell has negative neighbors";
    }
    else if (n > 8) {
        throw "Error: cell has too many neighbors";
    }
    neighbors = n;
}
int Cell::getNeighbors() {
    return neighbors;
}

Cell::Cell() : mine(false), covered(true), flagged(false), neighbors(0) {
    //cout << "Cell constructor\n";
}

Cell::~Cell() {
    //cout << "Cell destructor\n";
}

/*****************************************************************************/

// Naudojama generuojant lenta konstruktoriuje
void Board::updateNeighbors(int x, int y) {
    // Upper left
    if (x-1 >= 0 && y-1 >= 0) {
        if (board[x-1][y-1].isMine() == false) {
            board[x-1][y-1].incrementNeighbors();
        }
    }
    // Upper middle
    if (y-1 >= 0) {
        if (board[x][y-1].isMine() == false) {
            board[x][y-1].incrementNeighbors();
        }
    }
    // Upper right
    if (x+1 <= width-1 && y-1 >= 0) {
        if (board[x+1][y-1].isMine() == false) {
            board[x+1][y-1].incrementNeighbors();
        }
    }
    // Middle left
    if (x-1 >= 0) {
        if (board[x-1][y].isMine() == false) {
            board[x-1][y].incrementNeighbors();
        }
    }
    // Middle right
    if (x+1 <= width-1) {
        if (board[x+1][y].isMine() == false) {
            board[x+1][y].incrementNeighbors();
        }
    }
    // Bottom left
    if (x-1 >= 0 && y+1 <= height-1) {
        if (board[x-1][y+1].isMine() == false) {
            board[x-1][y+1].incrementNeighbors();
        }
    }
    // Bottom middle
    if (y+1 <= height-1) {
        if (board[x][y+1].isMine() == false) {
            board[x][y+1].incrementNeighbors();
        }
    }
    // Bottom right
    if (x+1 <= width-1 && y+1 <= height-1) {
        if (board[x+1][y+1].isMine() == false) {
            board[x+1][y+1].incrementNeighbors();
        }
    }
}

// Sitas rekursiskai atveria visa regiona langeliu kurie yra nuliai arba
// yra prie nulio
void Board::uncoverZeros(int x, int y) {
    //cout << "uncoverZeros( " << x << ", " << y << ") called\n";
    int coveredNeighbors = 0;
    // Upper left
    if (x-1 >= 0 && y-1 >= 0) {
        if (board[x-1][y-1].isCovered()) {
            ++coveredNeighbors;
            board[x-1][y-1].setCovered(false);
            if (board[x-1][y-1].getNeighbors() == 0) {
                uncoverZeros(x-1, y-1);
            }
        }
    }
    // Upper middle
    if (y-1 >= 0) {
        if (board[x][y-1].isCovered()) {
            board[x][y-1].setCovered(false);
            if (board[x][y-1].getNeighbors() == 0) {
                uncoverZeros(x, y-1);
            }
        }
    }
    // Upper right
    if (x+1 <= width-1 && y-1 >= 0) {
        if (board[x+1][y-1].isCovered()) {
            board[x+1][y-1].setCovered(false);
            if (board[x+1][y-1].getNeighbors() == 0) {
                uncoverZeros(x+1, y-1);
            }
        }
    }
    // Middle left
    if (x-1 >= 0) {
        if (board[x-1][y].isCovered()) {
            board[x-1][y].setCovered(false);
            if (board[x-1][y].getNeighbors() == 0) {
                uncoverZeros(x-1, y);
            }
        }
    }
    // Middle right
    if (x+1 <= width-1) {
        if (board[x+1][y].isCovered()) {
            board[x+1][y].setCovered(false);
            if (board[x+1][y].getNeighbors() == 0) {
                uncoverZeros(x+1, y);
            }
        }
    }
    // Bottom left
    if (x-1 >= 0 && y+1 <= height-1) {
        if (board[x-1][y+1].isCovered()) {
            board[x-1][y+1].setCovered(false);
            if (board[x-1][y+1].getNeighbors() == 0) {
                uncoverZeros(x, y+1);
            }
        }
    }
    // Bottom middle
    if (y+1 <= height-1) {
        if (board[x][y+1].isCovered()) {
            board[x][y+1].setCovered(false);
            if (board[x][y+1].getNeighbors() == 0) {
                uncoverZeros(x, y+1);
            }
        }
    }
    // Bottom right
    if (x+1 <= width-1 && y+1 <= height-1) {
        if (board[x+1][y+1].isCovered()) {
            board[x+1][y+1].setCovered(false);
            if (board[x+1][y+1].getNeighbors() == 0) {
                uncoverZeros(x+1, y+1);
            }
        }
    }
}

int Board::getWidth() {
    return width;
}
int Board::getHeight() {
    return height;
}

void Board::flag(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        throw "Error: flag out of bounds";
    }
    if (board[x][y].isCovered() == false) {
        throw "Error: attempting to flag uncovered tile";
    }
    board[x][y].toggleFlagged();
}

void Board::uncover(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        throw "Error: cover out of bounds";
    }
    if (board[x][y].isMine()) {
        // Pralaimejimas
        // TODO
        return;
    }
    board[x][y].setCovered(false);

    // Jei nera kaiminu, atveriame viska aplinkui automatiskai
    if (board[x][y].getNeighbors() == 0) {
        uncoverZeros(x, y);
    }
}

void Board::print() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (board[i][j].isCovered()) {
                if (board[i][j].isFlagged()) {
                    cout << "!";
                }
                else {
                    cout << "#";
                }
            }
            // Matomas tik viena karta pralaimejimo atveju
            else if (board[i][j].isMine()) {
                cout << "X";
            }
            else {
                cout << board[i][j].getNeighbors();
            }
        }
        cout << endl;
    }
}

void Board::printDebug() {
    cout << "MINES: \n";
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            cout << board[i][j].isMine() << " ";
        }
        cout << endl;
    }
    cout << endl << "COVER: \n";
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            cout << board[i][j].isCovered() << " ";
        }
        cout << endl;
    }
    cout << endl << "FLAGS: \n";
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            cout << board[i][j].isFlagged() << " ";
        }
        cout << endl;
    }
    cout << endl << "NEIGHBORS: \n";
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (board[i][j].isMine()) {
                cout << "X ";
            }
            else {
                cout << board[i][j].getNeighbors() << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

Board::Board(int w, int h, int mines) {
    //cout << "Board constructor\n";
    if (w < MIN_SIZE || h < MIN_SIZE) {
        throw "Error: board too small";
    }
    if (w > MAX_SIZE || h > MAX_SIZE) {
        throw "Error: board too big";
    }
    // Surandame kiek maziausiai/daugiausiai gali buti minu pagal
    // nustatymus virstuje
    int minDensity = round(w * h * MIN_DENSITY);
    int maxDensity = round(w * h * MAX_DENSITY);
    if (mines < minDensity) {
        throw "Error: too few mines";
    }
    if (mines > maxDensity) {
        throw "Error: too many mines";
    }

    // Sudarome lenta
    width = w;
    height = h;
    board.resize(width);
    for (int i = 0; i < width; ++i) {
        board[i].resize(height);
    }

    // Sugeneruojame minu pozicijas
    vector<int> mineSpots;
    mineSpots.resize(width*height);
    for (size_t i = 0; i < mineSpots.size(); ++i) {
        mineSpots[i] = i;
    }
    srand(time(0));
    shuffle(mineSpots.begin(), mineSpots.end(), default_random_engine(rand()));

    /*cout << mineSpots.size() << endl;
    for (int i = 0; i < mineSpots.size(); ++i) {
        cout << mineSpots[i] << endl;
    }*/

    // Sudeliojame minas
    // (Galima geriau padaryti negu O(n^3), bet kolkas tegu taip)
    for (int i = 0; i < mines; ++i) {
        int posX, posY;
        int counter = mineSpots[i];
        bool done = false;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (counter == 0) {
                    posX = x;
                    posY = y;
                    done = true;
                    break;
                }
                counter--;
            }
            if (done) {
                break;
            }
        }
        //cout << mineSpots[i] << ": " << "(" << posX << ", " << posY << ")\n";

        board[posX][posY].setMine();
        board[posX][posY].setNeighbors(-1);
        updateNeighbors(posX, posY);
    }
}

Board::~Board() {
    //cout << "Board destructor\n";
}
