#include <bits/stdc++.h>
#include "DisjointSet.h"

using namespace std;

int n;
int clusterCount = 0;

void printGrid(vector<vector<int> >& grid) {
    for (auto& row : grid) {
        for (auto& col : row) {
            cout << col << " ";
        } cout << endl;
    } cout << endl;
}

vector<vector<int> >readInput(string filename) {
    // read file
    ifstream ifs;

    int i   = 0;
    int val = 0;

    ifs.open(filename);

    ifs >> n;
    vector<vector<int> > grid(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ifs >> val;
            grid.at(i).push_back(val);
        }
    }
    return grid;
}

DSet preProcess(vector<vector<int> >& grid) {
    int  n = grid.size();
    int  m = grid[0].size();
    DSet cluster(n * m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // If cell is 0 set size to 0 to help identify
            if (grid[i][j] == 0) {
                cluster.setSize(i * (m) + j);
                continue;
            }

            // Check  neighbors that share lines
            // Down
            if ((i + 1 < n) && (grid[i + 1][j] == 1)) {
                cluster.unionSet(i * (m) + j, (i + 1) * (m) + j);
            }

            // Up
            if ((i - 1 >= 0) && (grid[i - 1][j] == 1)) {
                cluster.unionSet(i * (m) + j, (i - 1) * (m) + j);
            }

            // Right
            if ((j + 1 < m) && (grid[i][j + 1] == 1)) {
                cluster.unionSet(i * (m) + j, (i) * (m) + j + 1);
            }

            // Left
            if ((j - 1 >= 0) && (grid[i][j - 1] == 1)) {
                cluster.unionSet(i * (m) + j, (i) * (m) + j - 1);
            }
        }
    }
    return cluster;
}

int main() {
    // Read in file 2D matrix
    vector<vector<int> > grid;
    string filename = "input.txt";


    grid = readInput(filename);
    printGrid(grid);

    DSet cluster = preProcess(grid);

    // prints how many group and lists the parent of each one
    cluster.groupData();

    cout << "Size of group at postion 57 " << cluster.getSize(57) << endl;

    cout << "Size of group at postion 19 " << cluster.getSize(19) << endl;

    cout << "Size of group at postion 34 " << cluster.getSize(34) << endl;

    cout << "Size of group at postion 89 " << cluster.getSize(89) << endl;


    return 1;
}
