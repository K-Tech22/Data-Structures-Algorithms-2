// Author: Kush Chopra

#include "bintree.h"
#include <fstream>
#include <iostream>
using namespace std;

const int ARRAYSIZE = 50;

void buildTree(BinTree &, ifstream &); //
void initArray(NodeData *[]);          // initialize array to NULL

int main()
{

    ifstream infile("inputdata_kush.txt");
    if (!infile)
    {
        cout << "File could not be opened." << endl;
        return 1;
    }

    NodeData notND("not");
    NodeData andND("and");
    NodeData sssND("sss");
    NodeData ttttND("tttt");
    NodeData oooND("ooo");
    NodeData yND("y");
    NodeData eND("e");
    NodeData mND("m");
    NodeData tND("t");

    BinTree T, T2, dup;
    NodeData *ndArray[ARRAYSIZE];
    initArray(ndArray);
    cout << "Initial data:" << endl
         << "  ";

    buildTree(T, infile);
    cout << endl;
    BinTree first(T);
    dup = dup = T;
    while (!infile.eof())
    {
        cout << "Tree Inorder:" << endl
             << T; // operator<< does endl
        T.displaySideways();

        // test retrieve
        NodeData *p; // pointer of retrieved object
        bool found;  // whether or not object was found in tree
        found = T.retrieve(andND, p);
        cout << "Retrieve --> b:  " << (found ? "found" : "not found") << endl;
        found = T.retrieve(notND, p);
        cout << "Retrieve --> a:  " << (found ? "found" : "not found") << endl;
        found = T.retrieve(sssND, p);
        cout << "Retrieve --> kush:  " << (found ? "found" : "not found") << endl;

        // test getHeight
        cout << "Height    --> kush:  " << T.getHeight(andND) << endl;
        cout << "Height    --> xylophone:  " << T.getHeight(notND) << endl;
        cout << "Height    --> hello:  " << T.getHeight(sssND) << endl;
        cout << "Height    --> world:  " << T.getHeight(ttttND) << endl;
        cout << "Height    --> x:  " << T.getHeight(oooND) << endl;
        cout << "Height    --> b:  " << T.getHeight(yND) << endl;

        T2 = T;
        cout << "T == T2?     " << (T == T2 ? "equal" : "not equal") << endl;
        cout << "T != first?  " << (T != first ? "not equal" : "equal") << endl;
        cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;
        dup = T;

        T.bstreeToArray(ndArray);
        T.arrayToBSTree(ndArray);
        T.displaySideways();

        T.makeEmpty();
        initArray(ndArray);

        cout << "---------------------------------------------------------------"
             << endl;
        cout << "Initial data:" << endl
             << "  ";
        buildTree(T, infile);
        cout << endl;
    }

    return 0;
}

void buildTree(BinTree &T, ifstream &infile)
{
    string s;

    for (;;)
    {
        infile >> s;
        cout << s << ' ';
        if (s == "$$")
            break;
        if (infile.eof())
            break;
        NodeData *ptr = new NodeData(s);

        bool success = T.insert(ptr);
        if (!success)
            delete ptr;
    }
}

void initArray(NodeData *ndArray[])
{
    for (int i = 0; i < ARRAYSIZE; i++)
        ndArray[i] = NULL;
}
