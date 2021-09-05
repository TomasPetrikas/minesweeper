#include "Minesweeper.h"
#include <iostream>
#include <string>
using namespace std;

void printTest(string testName, bool result, string msg = "") {
    if (result) {
        cout << "Test passed\n";
    }
    else {
        cout << testName << " failed";
        if (!msg.empty()) {
            cout << " (" << msg << ")";
        }
        cout << endl;
    }
}

// Testing basic IO
void PlayerTest1() {
    try {
        string name = "Name";
        Player p(name);
        printTest("Player Test 1", p.getName() == name);
    }
    catch (const char* msg) {
        printTest("Player Test 1", false, msg);
    }
}
// Testing wrong name length
void PlayerTest2() {
    try {
        string name = "NameWhichIsProbablyWayTooLong";
        Player p(name);
        printTest("Player Test 2", false);
    }
    catch (const char* msg) {
        printTest("Player Test 2", true);
    }
}

// Testing too many neighbors (must be 0 to 8 inclusive)
void CellTest1() {
    try {
        Cell c;
        c.setNeighbors(9);
        printTest("Cell Test 1", false);
    }
    catch (const char* msg) {
        printTest("Cell Test 1", true);
    }
}

// Creating a board
void BoardTest1() {
    try {
        Board b(15, 20, 50);
        printTest("Board Test 1", (b.getWidth() == 15 && b.getHeight() == 20));
    }
    catch (const char* msg) {
        printTest("Board Test 1", false, msg);
    }
}

// Creating a board with too many mines
void BoardTest2() {
    try {
        Board b(20, 15, 301);
        printTest("Board Test 2", false);
    }
    catch (const char* msg) {
        printTest("Board Test 2", true);
    }
}

// Attempting to flag an uncovered tile
void BoardTest3() {
    try {
        Board b(8, 8, 0);
        b.uncover(0, 0);
        b.flag(0, 0);
        printTest("Board Test 3", false);
    }
    catch (const char* msg) {
        printTest("Board Test 3", true);
    }
}

int main(int argc, char* args[]) {
    PlayerTest1();
    PlayerTest2();
    CellTest1();
    BoardTest1();
    BoardTest2();

    system("pause");
}
