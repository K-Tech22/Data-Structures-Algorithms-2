#include "graphl.h"
#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

// copy constructor
GraphL::GraphL() : size(0)
{
    for (int i = 1; i <= 99; i++)
    {
        graphNodes[i].edgeHead = NULL;
        graphNodes[i].data = NULL;
        graphNodes[i].visited = false;
    }
}

// destructor
GraphL::~GraphL()
{
    int counter = 1;

    while (counter <= size)
    {

        graphNodes[counter].visited = false;
        delete graphNodes[counter].data;
        graphNodes[counter].data = NULL;

        if (graphNodes[counter].edgeHead != NULL)
        {
            EdgeNode *goodByeNode = graphNodes[counter].edgeHead;

            while (goodByeNode != NULL)
            {
                graphNodes[counter].edgeHead = graphNodes[counter].edgeHead->nextEdge;
                delete goodByeNode;
                goodByeNode = NULL;
                goodByeNode = graphNodes[counter].edgeHead;
            }
        }
        ++counter;
    }
}

void GraphL::buildGraph(ifstream &file)
{

    file >> size;
    string names = "";
    getline(file, names);

    for (int name = 1; name <= size; ++name)
    {
        getline(file, names);
        NodeData *curr = new NodeData(names);
        graphNodes[name].data = curr;
    }

    int nodeFrom, nodeTo;

    while (file >> nodeFrom >> nodeTo)
    {
        if (nodeFrom == 0)
        {
            break;
        }

        if (graphNodes[nodeFrom].edgeHead != NULL)
        {
            EdgeNode *curr = new EdgeNode;
            curr->adjGraphNode = nodeTo;
            curr->nextEdge = graphNodes[nodeFrom].edgeHead;
            graphNodes[nodeFrom].edgeHead = curr;
        }
        else
        {
            EdgeNode *curr = new EdgeNode;
            curr->adjGraphNode = nodeTo;
            graphNodes[nodeFrom].edgeHead = curr;
            graphNodes[nodeFrom].edgeHead->nextEdge = NULL;
        }
    }
}

void GraphL::displayGraph()
{
    int counter = 1;

    while (counter <= size)
    {
        {
            cout << "Node " << counter << "\t" << *graphNodes[counter].data << endl
                 << endl;

            EdgeNode *curr = graphNodes[counter].edgeHead;

            while (curr != NULL)
            {
                cout << "\t"
                     << "edge " << counter << " " << curr->adjGraphNode << endl;
                cout << endl;
                curr = curr->nextEdge;
            }
            ++counter;
        }
    }
}

void GraphL::depthFirstSearch()
{
    cout << "Depth-first ordering:";

    int counter = 1;

    while (counter <= size)
    {
        if (!graphNodes[counter].visited)
        {
            dfs(counter);
        }
        ++counter;
    }

    cout << endl;
}

void GraphL::dfs(int node)
{
    cout << " " << node;

    EdgeNode *curr = graphNodes[node].edgeHead;

    graphNodes[node].visited = true;

    while (curr != NULL)
    {
        if (!graphNodes[curr->adjGraphNode].visited)
        {
            dfs(curr->adjGraphNode);
        }

        curr = curr->nextEdge;
    }
}