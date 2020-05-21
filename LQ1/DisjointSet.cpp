#include <bits/stdc++.h>
#include "DisjointSet.h"


DSet::DSet(int n) {
    rank    = new int[n + 1];
    parent  = new int[n + 1];
    this->n = n;

    makeSet();
}

void DSet::makeSet() {
    for (int i = 0; i <= n; ++i) {
        parent[i] = i;
        rank[i]   = 1;
    }
}

int DSet::find(int e) {
    // rescursive find
    if (e != parent[e]) {
        // set parent to parent (path compression)
        parent[e] = find(parent[e]);
    }
    return parent[e];
}

void DSet::unionSet(int e1, int e2) {
    int p1 = find(e1);
    int p2 = find(e2);

    if (p1 == p2) {
        return;
    }

    // optimzation using size
    if (rank[p1] > rank[p2]) {
        parent[p2] = p1;

        // update size
        rank[p1] += rank[p2];
    } else {
        parent[p1] = p2;

        // update size
        rank[p2] += rank[p1];
    }
}

void DSet::setSize(int x) {
    rank[x] = 0;
}

int DSet::getSize(int x) {
    return rank[find(x)];
}

void DSet::groupData() {
    std::vector<int> groupList;

    for (int i = 0; i < n; i++) {
        if (rank[i] != 0) {
            // Make sure parent is root node
            find(i);

            if (std::find(groupList.begin(), groupList.end(), parent[i]) == groupList.end()) {
                groupList.push_back(parent[i]);
            }
        }
    }
    std::cout << "The grid has " << groupList.size() << " groups" << std::endl << std::endl;
    std::cout << "Listed groups: " << std::endl;

    for (auto& elem : groupList) {
        std::cout << elem << " ";
    }  std::cout << std::endl << std::endl;
}

void DSet::printSet() {
    std::cout << std::endl << "Elements: " << std::endl;

    // print nodes
    for (int i = 0; i < n; i++) {
        std::cout << i << " ";
    } std::cout << std::endl;

    std::cout << "Parents: " << std::endl;

    // print parents
    for (int i = 0; i < n; i++) {
        std::cout << parent[i] << " ";
    } std::cout << std::endl;

    // print true parent
    for (int i = 0; i < n; i++) {
        std::cout << find(i) << " ";
    } std::cout << std::endl;
    std::cout << "Rank: " << std::endl;

    // print size
    for (int i = 0; i < n; i++) {
        std::cout << rank[i] << " ";
    } std::cout << std::endl;
}
