#include <bits/stdc++.h>
#include "DisjointSet.h"

using namespace std;

class Maze {
private:

    vector<vector<int> >grid;
    int nCells;
    DSet cells;

public:

    int si, sj, gi, gj, sID, gID;
    int row, col;

    Maze(int n, int m, int sx, int sy, int gx, int gy) : row(n), col(m), si(sx), sj(sy), gi(gx), gj(gy), nCells(n * m), cells(n * m) {
        int cellID = 1;

        grid.resize(row, vector<int>(col, 0));

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if ((i == gi) && (j == gj)) {
                    gID = cellID;
                }

                if ((i == si) && (j == sj)) {
                    sID = cellID;
                }
                grid[i][j] = cellID;
                cellID++;
            }
        }
        makeMaze();
    }

    bool pathIsValid(int a, int b) {
        if (cells.find(a) == cells.find(b)) {
            return true;
        }
        return false;
    }

    int gridLookUp(int x, int y) {
        return grid[x][y];
    }

    void makeMaze() {
        int start, finish, n;

        // Update to reflect user choice
        start  = grid[0][0];
        finish = grid[row - 1][col - 1];

        int rCol, rRow;
        srand((unsigned)time(NULL));

        // while goal is not reachable
        while (cells.find(start) != cells.find(finish)) {
            int d;
            int cx, cy;

            rCol = rand() % col;
            rRow = rand() % row;

            // get values
            cx = grid[rRow][rCol];

            // N=1 S=2 E=3 W=4
            d = getDirection(rRow, rCol);

            switch (d) {
            case 1:
                cy = grid[rRow - 1][rCol]; // North

                if (cells.find(cx) != cells.find(cy)) {
                    cells.unionSet(cx, cy);
                }
                break;

            case 2:
                cy = grid[rRow + 1][rCol]; // South

                if (cells.find(cx) != cells.find(cy)) {
                    cells.unionSet(cx, cy);
                }
                break;

            case 3:
                cy = grid[rRow][rCol + 1]; // East

                if (cells.find(cx) != cells.find(cy)) {
                    cells.unionSet(cx, cy);
                }
                break;

            case 4:
                cy =  grid[rRow][rCol - 1]; // West

                if (cells.find(cx) != cells.find(cy)) {
                    cells.unionSet(cx, cy);
                }
                break;

            default:

                cout << "broke" << endl;
            }
        }

        // cout << "works here" << endl;
        printMaze();
    }

    int getDirection(int r, int c) {
        // N=1 S=2 E=3 W=4
        int nCol = col - 1;
        int nRow = row - 1;
        int e;
        int NSEW[4] = { 1, 2, 3, 4 };

        int SEW[3] = { 2, 3, 4 };
        int NEW[3] = { 1, 3, 4 };
        int NSW[3] = { 1, 2, 4 };
        int NSE[3] = { 1, 2, 3 };

        int SE[2] = { 2, 3 };
        int NE[2] = { 1, 3 };
        int SW[2] = { 2, 4 };
        int NW[2] = { 1, 4 };

        // if chosen cell isnt on a boarder use full list of direction
        if ((r > 0) && (r != nRow) && (c > 0) && (c != nCol)) {
            e = rand() % 4;
            return NSEW[e];
        }

        // if chosen cell is in North East corner only make South West available
        if ((r == 0) && (c == nCol)) {
            // don't consider West or North
            e = rand() % 2;

            // cout << "Go South(i+1) or west(j-1) " << SW[e] << " N=1 S=2 E=3 W=4" << endl;
            return SW[e];
        }

        // if chosen cell is in South West corner only make North East available
        if ((r == nRow) && (c == 0)) {
            // don't consider South or East
            e = rand() % 2;

            // cout << "Go North(i-1) or East(j+1) " << NE[e] << " N=1 S=2 E=3 W=4" << endl;
            return NE[e];
        }

        // if chosen cell is in North West corner only make South East available
        if ((r == 0) && (c == 0)) {
            // don't consider West or South
            e = rand() % 2;

            // cout << "Go South(i+1) or east(j+1) " << SE[e] << " N=1 S=2 E=3 W=4" << endl;
            return SE[e];
        }

        // if chosen cell is in South East corner only make North West available
        if ((r == nRow) && (c == nCol)) {
            e = rand() % 2;

            return NW[e];
        }

        if (r == 0) {
            e = rand() % 3;
            return SEW[e];
        }

        if (r == nRow) {
            e = rand() % 3;

            return NEW[e];
        }

        if (c == 0) {
            e = rand() % 3 + 1;

            return NSE[e];
        }

        if (c == nCol) {
            e = rand() % 3 + 1;

            return NSW[e];
        }
    }

    void printMaze() {
        // top boundary
        for (int j = 1; j <= col; j++) {
            cout << " _";
        } cout << endl;

        // contents
        for (int i = 0; i < row; i++) {
            // start left border
            cout << "|";

            for (int j = 0; j < col; j++) {
                // row print
                if (i != row - 1) {
                    if (cells.find(grid[i][j]) != cells.find(grid[i + 1][j])) {
                        cout << "_";
                    } else {
                        cout << " ";
                    }
                } else {
                    cout << "_";
                }

                // Find a way if both are unions print " "
                // if col print
                if (j != col - 1) {
                    if (cells.find(grid[i][j]) != cells.find(grid[i][j + 1])) {
                        cout << "|";
                    } else {
                        cout << " ";
                    }
                } else {
                    // cout << "|";
                }
            }
            cout << "|";
            cout << endl;
        }
    }

    void printMazeSol(vector<int>& sol) {
        // top boundary
        cout << endl << endl;

        for (int j = 1; j <= col; j++) {
            cout << " _";
        } cout << endl;

        // contents
        for (int i = 0; i < row; i++) {
            // start left border
            cout << "|";

            for (int j = 0; j < col; j++) {
                // row print
                if (find(sol.begin(), sol.end(), grid[i][j]) != sol.end()) {
                    cout << "X";

                    // continue;
                }

                else if (i != row - 1) {
                    if (cells.find(grid[i][j]) != cells.find(grid[i + 1][j])) {
                        cout << "_";
                    } else {
                        cout << " ";
                    }
                } else {
                    cout << "_";
                }

                // Find a way if both are unions print " "
                // if col print
                if (j != col - 1) {
                    if (cells.find(grid[i][j]) != cells.find(grid[i][j + 1])) {
                        cout << "|";
                    } else {
                        cout << " ";
                    }
                } else {
                    // cout << "|";
                }
            }
            cout << "|";
            cout << endl;
        }
    }

    void printGrid() {
        cout << endl << endl << "Grid ID:" << endl;

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                // row print

                cout << grid[i][j] << " ";

                if (grid[i][j] < 10) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
};
