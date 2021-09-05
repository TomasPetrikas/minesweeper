#include "Minesweeper.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* args[]) {
    try {
        int h = 8;
        int w = 8;
        int m = 10;
        Board b(h, w, m);
        string mode;
        int x, y;

        while (1) {
            b.print();
            // currently zero protection
            // "u" if uncovering, "f" if flagging, x and y are coordinates
            cin >> mode;
            cin >> x >> y;

            if (mode == "u") {
                b.uncover(x, y);
            }
            else if (mode == "f") {
                b.flag(x, y);
            }
            system("CLS");
        }
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }

    return 0;
}
