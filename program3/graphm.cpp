#include "graphm.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <iomanip>

using namespace std;

// Copy constructor
GraphM::GraphM() : size(0)
{
    for (int i = 1; i < MAXNODES; i++)
    {
        for (int j = 1; j < MAXNODES; j++)
        {
            C[i][j] = INT_MAX;
            T[i][j].visited = false;
            T[i][j].dist = INT_MAX;
            T[i][j].path = 0;
        }
    }
}

// buildGraph: Organzies graph information from the file
// Preconditions: A file must be valid
// Postconditions: Gets information regarding size, names, from nodes, to nodes, and total distance between them
void GraphM::buildGraph(ifstream &file)
{
    // Gets the size
    file >> size;
    string names = "";

    // Gets the names of the nodes
    getline(file, names);

    // Loops around the names of the nodes
    for (int name = 1; name <= size; name++)
    {
        // Calls setData from nodedata.cpp to set the name of the node
        data[name].setData(file);
    }

    int nodeFrom, nodeTo, dist;

    // Reads from node, to node, and distance between them in the line
    file >> nodeFrom >> nodeTo >> dist;

    while (nodeFrom != 0 && nodeTo != 0 && dist != 0)
    {
        C[nodeFrom][nodeTo] = dist;
        file >> nodeFrom >> nodeTo >> dist;
    }
}

// findShortestPath: Finds the path from one node to every other node
// Preconditions: Nodes should be valid
// Postconditions: Gets the path from one node to every other node
void GraphM::findShortestPath()
{
    // Loops from source nodes till it reaches max node
    for (int source = 1; source <= size; source++)
    {
        // Dist and visited set to 0 and true initially
        T[source][source].dist = 0;
        T[source][source].visited = true;

        // Loops to find adjacent nodes
        for (int i = 1; i <= size; i++)
        {
            if (C[source][i] != INT_MAX)
            {
                // Sets the distance between the nodes
                T[source][i].dist = C[source][i];

                // Sets the path between the nodes
                T[source][i].path = source;
            }
        }

        int v = 0;
        bool is_done = false;

        while (!is_done)
        {
            int node = INT_MAX;
            v = 0;

            // Finds adjacent node closest to source node
            for (int n = 1; n <= size; n++)
            {
                if (!T[source][n].visited && (C[source][n] < node))
                {
                    // Set to dist
                    node = C[source][n];
                    v = n;
                }
            }

            if (v == 0)
            {
                is_done = true;
                break;
            }

            // True if node is visited now
            T[source][v].visited = true;

            for (int w = 1; w <= size; ++w)
            {
                if ((T[source][w].visited) || (C[v][w] == INT_MAX) || (v == w))
                {
                    continue;
                }

                if (T[source][w].dist > T[source][v].dist + C[v][w])
                {
                    T[source][w].dist = T[source][v].dist + C[v][w];
                    T[source][w].path = v;
                }
            }
        }
    }
}

// displayAll: displays the info found by findShortestPath
// Preconditions: none
// Postconditions: outputs the data in table format
void GraphM::displayAll()
{
    cout << endl;
    // Headings
    cout << "Description" << setw(20) << "From_node" << setw(20) << "To_node"
         << setw(20) << "Distance" << setw(20) << "Path" << endl;

    // Loops from from nodes
    for (int nodeFrom = 1; nodeFrom <= size; nodeFrom++)
    {
        cout << data[nodeFrom] << endl;

        // Loops from to nodes
        for (int nodeTo = 1; nodeTo <= size; nodeTo++)
        {
            if (T[nodeFrom][nodeTo].dist != 0)
            {
                // prints node from and node to
                cout << setw(27) << nodeFrom << setw(20) << nodeTo;

                if (T[nodeFrom][nodeTo].dist == INT_MAX)
                {
                    // if dist not available
                    cout << setw(20) << "---" << endl;
                }
                else
                {
                    cout << setw(20) << T[nodeFrom][nodeTo].dist << setw(20);
                    int curr = nodeTo;
                    int dist = 0;
                    int distance[size];

                    distance[dist++] = curr;

                    while (curr != nodeFrom)
                    {
                        curr = T[nodeFrom][curr].path;
                        distance[dist++] = curr;
                    }

                    for (int i = dist - 1; i >= 0; i--)
                    {
                        cout << distance[i] << " ";
                    }

                    cout << endl;
                }
            }
        }
    }
}

// display: displays the path from one node to another
// Preconditions: none
// Postconditions: prints distance
void GraphM::display(int nodeFrom, int nodeTo)
{
    // check if nodes are valid
    if (nodeTo < 0 || nodeFrom < 0 || nodeTo > size || nodeFrom > size)
    {
        cout << nodeFrom << " " << nodeTo << " "
             << "-> No Path";

        return;
    }

    cout << nodeFrom << " " << nodeTo;

    // When no path is found
    if (T[nodeFrom][nodeTo].dist == INT_MAX)
    {
        cout << " -> No Path" << endl;
    }
    else
    {
        cout << " " << T[nodeFrom][nodeTo].dist << " ";

        // calls helper method to find path
        helperPathFinder(nodeFrom, nodeTo);
        cout << endl;

        // calls helper method to find distance
        helperDistanceFinder(nodeFrom, nodeTo);
    }
    cout << endl;
}

// helper function
void GraphM::helperDistanceFinder(int nodeFrom, int nodeTo)
{
    if (nodeFrom == nodeTo)
    {
        cout << data[nodeTo] << endl;

        return;
    }

    else if (T[nodeFrom][nodeTo].dist == INT_MAX)
    {
        return;
    }
    else
    {
        int to = nodeTo;

        helperDistanceFinder(nodeFrom, nodeTo = T[nodeFrom][nodeTo].path);

        cout << data[to] << endl;
    }
}

// helper function
void GraphM::helperPathFinder(int nodeFrom, int nodeTo)
{
    if (T[nodeFrom][nodeTo].dist == INT_MAX)
    {
        return;
    }

    if (nodeFrom == nodeTo)
    {
        cout << nodeTo << " ";

        return;
    }

    int pathData = nodeTo; // assign to path to pathData
    helperPathFinder(nodeFrom, nodeTo = T[nodeFrom][nodeTo].path);

    cout << pathData << " ";
}

// insertEdge: inserts edge between two nodes
// Preconditions: none
// Postconditions: edge inserted
bool GraphM::insertEdge(int nodeFrom, int nodeTo, int path)
{
    // check for valid edge
    if (nodeFrom > 0 && nodeFrom <= size && nodeTo > 0 && nodeTo <= size && path > 0 && path && nodeFrom != nodeTo)
    {
        C[nodeFrom][nodeTo] = path;
        // Call func again
        findShortestPath();
        return true;
    }
    return false;
}

// removeEdge: removes the edge
// Preconditions: none
// Postconditions: edge removed
bool GraphM::removeEdge(int nodeFrom, int nodeTo)
{
    // check for valid edge
    if (nodeFrom > 0 && nodeTo > 0)
    {
        C[nodeFrom][nodeTo] = INT_MAX;
        findShortestPath();
        return true;
    }
    return false;
}