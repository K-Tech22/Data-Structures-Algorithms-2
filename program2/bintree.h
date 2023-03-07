// Author: Kush Chopra

#ifndef BINTREE_H
#define BINTREE_H

#include "nodedata.h"

#include <iostream> //input and output
using namespace std;

class BinTree
{

    friend ostream &operator<<(ostream &, const BinTree &);

public:
    BinTree();

    BinTree(const BinTree &bt);

    ~BinTree();

    bool isEmpty() const;

    void makeEmpty();

    BinTree &operator=(const BinTree &);

    bool operator==(const BinTree &) const;

    bool operator!=(const BinTree &) const;

    bool insert(NodeData *);

    bool retrieve(const NodeData &, NodeData *&);

    int getHeight(const NodeData &) const;

    void bstreeToArray(NodeData *[]);

    void arrayToBSTree(NodeData *[]);

    void displaySideways() const;

private:
    struct Node
    {
        NodeData *data;
        Node *left;
        Node *right;
    };
    Node *root;

    void inorderHelper(Node *) const;

    bool helperInsert(Node *&node, NodeData *newNode);

    bool helperRetrieve(const NodeData &, NodeData *&, Node *) const;

    int helperGetHeight(const NodeData &, Node *) const;

    int helperGetHeight2(Node *) const;

    int helperBstreeToArray(NodeData *[], Node *);

    void helperArrayToBSTree(NodeData *[], Node *, int, int);

    void helperMakeEmpty(Node *&);

    void helperOperatorEQ(Node *&, Node *);

    bool helperOperatorEQEQ(Node *, Node *) const;

    bool helperOperatorNotEQ(Node *, Node *) const;

    void sideways(Node *, int) const;
};
#endif