#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"
#include <iostream>

using namespace std;

class GraphL
{

private:
    struct EdgeNode;

    struct GraphNode
    {
        EdgeNode *edgeHead;
        NodeData *data;
        bool visited;
    };

    struct EdgeNode
    {
        int adjGraphNode;
        EdgeNode *nextEdge;
    };

    static const int MAXNODES = 100;

    GraphNode graphNodes[MAXNODES];

    int size;

    void destructor();

    void dfs(int);

public:
    GraphL();

    ~GraphL();

    void buildGraph(ifstream &);

    void displayGraph();

    void depthFirstSearch();
};
#endif