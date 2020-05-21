

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

class DSet {
private:

    int *rank;
    int *parent;
    int n;

public:

    DSet(int);

    void makeSet();

    int  find(int);

    void unionSet(int,
                  int);
};
#endif // ifndef DISJOINTSET_H
