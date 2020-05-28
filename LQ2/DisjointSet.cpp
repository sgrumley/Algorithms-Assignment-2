#include <bits/stdc++.h>
#include "DisjointSet.h"


DSet::DSet(int n) {
    rank    = new int[n + 1];
    parent  = new int[n + 1];
    this->n = n + 1;

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
    } else {
        parent[p1] = p2;

        // update size
        rank[p2] += rank[p1];
    }
}
