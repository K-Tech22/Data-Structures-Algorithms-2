#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"
#include <iostream>

using namespace std;

class GraphM
{

private:
    struct TableType
    {
        bool visited;
        int dist;
        int path;
    };
    static const int MAXNODES = 100;

    NodeData data[MAXNODES];

    int C[MAXNODES][MAXNODES];

    int size;

    TableType T[MAXNODES][MAXNODES];

    void helperPathFinder(int, int);

    void helperDistanceFinder(int, int);

public:
    GraphM();

    void buildGraph(ifstream &);

    bool insertEdge(int, int, int);

    bool removeEdge(int, int);

    void findShortestPath();

    void display(int, int);

    void displayAll();
};
#endif