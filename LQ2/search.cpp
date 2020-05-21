#include <bits/stdc++.h>


#include "maze.cpp"
#include "minHeap.cpp"
using namespace std;

// step refers to each step taken in the maze
struct step {
    int        h;       // distance from exit
    int        id;      // id of this step
    int        parent;
    char       path;    // direction we used to get here
    vector<int>options; // edges
    // preprocess all options from each square and calculate f
};

struct LessThan {
    bool operator()(const step& lhs, const step& rhs) const  {
        return lhs.h > rhs.h;
    }
};

bool stepIsValid(int i, int j, int n, int m) {
    // Returns true if row number and column number
    // is in range
    return (i >= 0) && (i < n) && (j >= 0) && (j < m);
}

void search(Maze& m1) {
    vector<step> data;
    step indexAlign;

    data.push_back(indexAlign);

    int n, m;

    n = m1.row;
    m = m1.col;

    priority_queue<step, vector<step>, LessThan> pq;
    int x = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            step tmp;
            tmp.id     = x;
            tmp.h      = abs(i - m1.gi) + abs(j - m1.gj);
            tmp.parent = -1;
            int comp;

            if (stepIsValid(i + 1, j, n, m)) {
                comp = m1.gridLookUp(i + 1, j);

                if (m1.pathIsValid(comp, x)) {
                    // add to edge
                    tmp.options.push_back(comp);
                }
            }

            if (stepIsValid(i - 1, j, n, m)) {
                comp = m1.gridLookUp(i - 1, j);

                if (m1.pathIsValid(comp, x)) {
                    // add to edge
                    tmp.options.push_back(comp);
                }
            }

            if (stepIsValid(i,     j + 1, n, m)) {
                comp = m1.gridLookUp(i,     j + 1);

                if (m1.pathIsValid(comp, x)) {
                    // add to edge
                    tmp.options.push_back(comp);
                }
            }


            if (stepIsValid(i,     j - 1, n, m)) {
                comp = m1.gridLookUp(i,     j - 1);

                if (m1.pathIsValid(comp, x)) {
                    // add to edge
                    tmp.options.push_back(comp);
                }
            }


            data.push_back(tmp);
            x++;
        }
    }

    // put start node on the queue
    bool goalState = false;
    pq.push(data[m1.sID]);
    vector<int> pathTaken;

    // cout << "Path explored: " << endl;

    while (goalState == false) {
        // pop from pq
        step currentStep = pq.top();


        pq.pop();

        pathTaken.push_back(currentStep.id);

        cout << currentStep.id << " ";

        // what direction did it come from
        for (int i = 0; i < currentStep.options.size(); i++) {
            // add options to pq
            int option = currentStep.options[i];

            if (std::find(pathTaken.begin(), pathTaken.end(), data[option].id) == pathTaken.end()) {
                pq.push(data[option]);
            }


            if (option == currentStep.id - 1) {
                data[option].path   = 'E';
                data[option].parent = currentStep.id;
            } else if (option == currentStep.id + 1) {
                data[option].path   = 'W';
                data[option].parent = currentStep.id;
            } else if (option > currentStep.id - 1) {
                data[option].path   = 'N';
                data[option].parent = currentStep.id;
            } else if (option < currentStep.id + 1) {
                data[option].path   = 'S';
                data[option].parent = currentStep.id;
            } else {
                data[option].path   = 'X';
                data[option].parent = 1;
            }
        }

        if (currentStep.id == m1.gID) {
            goalState = true;
            break;
        }
    }
    cout << endl << "Path found: " << endl;
    char start;

    if (data[1].options.size() == 2) {
        start = 'S';
    } else {
        start = 'E';
    }

    vector<int> sol;
    sol.push_back(data[1].id);

    int par = data[1].parent;

    while (par != m1.gID) {
        sol.push_back(data[par].parent);
        cout << endl << data[par].parent << " ";
        par = data[par].parent;
    }
    par = data[1].parent;
    cout << endl << start << " ";

    while (par != m1.gID) {
        cout << data[par].path << " ";
        par = data[par].parent;
    }

    m1.printMazeSol(sol);
}

// Driver program to test above function
int main() {
    int col, row;

    row = 50;
    col = 88;

    // start = ij
    int si = 0;
    int sj = 0;

    // finish = ij
    int gi = row - 1;
    int gj = col - 1;


    Maze m1(row, col, si, sj, gi, gj);

    // m1.printGrid();

    search(m1);
}
