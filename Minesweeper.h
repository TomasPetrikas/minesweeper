#ifndef MINESWEEPER_H_INCLUDED
#define MINESWEEPER_H_INCLUDED

#include <string>
#include <vector>

class Player {
    std::string name;

public:
    std::string getName();
    Player(std::string);
    ~Player();
};

class Cell {
    bool mine;
    bool covered;
    bool flagged;
    int neighbors;

public:
    void setMine();
    void setMine(bool);
    bool isMine();

    void toggleCovered();
    void setCovered(bool);
    bool isCovered();

    void toggleFlagged();
    void setFlagged(bool);
    bool isFlagged();

    void incrementNeighbors();
    void setNeighbors(int);
    int getNeighbors();

    Cell();
    ~Cell();
};

class Board {
    int width;
    int height;
    std::vector< std::vector<Cell> > board;

    void updateNeighbors(int x, int y);
    void uncoverZeros(int x, int y);

public:
    int getWidth();
    int getHeight();

    void flag(int x, int y);
    void uncover(int x, int y);
    void print();
    void printDebug();

    Board(int w, int h, int mines);
    ~Board();
};

#endif // MINESWEEPER_H_INCLUDED
