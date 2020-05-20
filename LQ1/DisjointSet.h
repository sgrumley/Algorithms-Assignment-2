

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

    void setSize(int);

    void groupData();

    int  getSize(int);

    void printSet();
};
#endif // ifndef DISJOINTSET_H
