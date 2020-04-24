#include <bits/stdc++.h>

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

int getClusterSize(int id, vector<int>& clusterSize) {
    return clusterSize.at(id - 2);
}

void searchCluster(vector<vector<int> >& grid, int i, int j, int clusterID) {
    // have a count in here as well

    if ((i < 0) || (i >= n) || (j < 0) || (j >= n) || (grid.at(i).at(j) != 1)) {
        return;
    }

    // mark node with id
    grid.at(i).at(j) = clusterID;

    // maybe make clusterCount public
    clusterCount++;

    // call each neighbour
    searchCluster(grid, i + 1, j,     clusterID); // down
    searchCluster(grid, i,     j + 1, clusterID); // right
    searchCluster(grid, i - 1, j,     clusterID); // top
    searchCluster(grid, i,     j - 1, clusterID); // left
}

void preProcess(vector<vector<int> >& grid) {
    int clusterID = 2;
    int i         = 0;
    int j         = 0; // only need i, j if we are storing values
    vector<int> clusterSize;

    // potensially add a vector<pair<int, int>> to keep track of co ordinates if required

    for (auto& row : grid) {
        for (auto& col : row) {
            if (col == 1) {
                // search logic only need to go right or down
                clusterCount = 0;
                searchCluster(grid, i, j, clusterID);
                cout << "Cluster number" << clusterCount << endl;

                // col = clusterID;
                // clusterCount++;
                clusterID++;

                clusterSize.push_back(clusterCount);
            } else if (col == 0) {
                // not part of a cluster
            } else {
                // visited
            }
            j++;
        } j = 0;
        i++;
    }
    printGrid(grid);

    for (int i = 0; i < clusterSize.size(); i++) {
        cout <<  clusterSize.at(i) << " ";
    } cout << endl << endl;

    // use DFS to find all groups
    // if the position is a 1 then change it to cluster ID starting at id=2
    // clusterID++ when no more in that cluster
    // create a vector of counts related to the clusterID

    // if next square does not equal 1 or 0 it has been visited
}

int main() {
    // Read in file 2D matrix
    vector<vector<int> > grid;
    string filename = "input.txt";

    grid = readInput(filename);
    cout << "read " << endl;
    printGrid(grid);

    preProcess(grid);
    printGrid(grid);

    // are we allowed to sue the boost library???
    // turn into grid class that performs preprocess and data then query the object for results

    // a) when given an input access its location for the clusterID and return the max from vector
    // b) return the length of the max vector to find how many groups
    // c) list all groups - does this mean the locations or the size of each - if locations add them to 2D vector of pairs where the internal vector represents a group
    return 1;
}
