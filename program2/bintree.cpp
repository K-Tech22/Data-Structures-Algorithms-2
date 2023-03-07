// Author: Kush Chopra

#include "bintree.h"
#include <iostream>

using namespace std;

// Shows the data in a BST
ostream &operator<<(ostream &out, const BinTree &bt)
{
    bt.inorderHelper(bt.root);
    out << endl;
    return out;
}

// Helper function for displaying nodes in inorder
void BinTree::inorderHelper(Node *currNode) const
{
    if (currNode != NULL)
    {
        inorderHelper(currNode->left);
        cout << *currNode->data << " ";
        inorderHelper(currNode->right);
    }
}

// Default constructor
BinTree::BinTree()
{
    this->root = NULL;
}

// Copy constructor
BinTree::BinTree(const BinTree &bt)
{
    this->root = NULL;
    *this = bt;
}

// Destructor
BinTree::~BinTree()
{
    this->helperMakeEmpty(this->root);
}

// Returns true if the tree is empty othwerwise returns false
bool BinTree::isEmpty() const
{
    return this->root == NULL ? true : false;
}

// Deletes BST
void BinTree::makeEmpty()
{
    return helperMakeEmpty(this->root);
}

// Helper for deleting tree
// Preconditions: current node should not be NULL
// Postconditions: each node is deleted individually. In the end, the entire tree will be deleted
void BinTree::helperMakeEmpty(Node *&currNode)
{
    if (currNode != NULL)
    {
        // function calls on left and right chile
        helperMakeEmpty(currNode->left);
        helperMakeEmpty(currNode->right);

        // NodeData for the current node is deleted and set it to NULL
        delete currNode->data;
        currNode->data = NULL;

        // Node is deleted and set it to NULL
        delete currNode;
        currNode = NULL;
    }
}

// This function does a deep copy of another tree
BinTree &BinTree::operator=(const BinTree &bt)
{
    // Deletes the current tree first
    this->makeEmpty();

    // Calling helper function with current tree's root and the paramenter tree's root
    helperOperatorEQ(this->root, bt.root);

    // Returns the new tree after deep copying
    return *this;
}

// Helper function for deep copying
// Preconditions: Roots for both the trees should not be NULL
// Postconditions: Old tree is deleted and this->root is set to the parameter tree's root (deep copying)
void BinTree::helperOperatorEQ(Node *&oldRoot, Node *Root)
{
    if (Root != NULL)
    {
        // each node of this->BinTree is created as a new Node
        oldRoot = new Node;

        // New nodeData is created and set to parameter tree's NodeData
        NodeData *newNode = new NodeData(*Root->data);

        // each node set to parameter tree's root
        oldRoot->data = newNode;

        // recursive calls on both left and right children
        helperOperatorEQ(oldRoot->left, Root->left);
        helperOperatorEQ(oldRoot->right, Root->right);
    }
    // If node is NULL, current tree's node is also set to NULL
    if (Root == NULL)
    {
        oldRoot = NULL;
    }
}

// This function checks if current tree is equal to the parameter tree
// Preconditions: rhs must be a tree
// Postconditions: true if the trees are same
bool BinTree::operator==(const BinTree &rhs) const
{
    // Calls helper function if root is not NULL
    return this->root == NULL && rhs.root == NULL ? true : helperOperatorEQEQ(this->root, rhs.root);
}

// Helper function for operator==
bool BinTree::helperOperatorEQEQ(Node *thisNode, Node *rhsNode) const
{
    // if two trees' nodes are NULL, then returns true
    if ((thisNode == NULL && rhsNode == NULL))
    {
        return true;
    }

    if ((thisNode != NULL) && (rhsNode != NULL))
    {
        // returns bool value of two nodes' data & recursive calls to function with left and right child
        return (*thisNode->data == *rhsNode->data) &&
               helperOperatorEQEQ(thisNode->left, rhsNode->left) &&
               helperOperatorEQEQ(thisNode->right, rhsNode->right);
    }

    return false;
}

// This function checks if the two trees are unequal
// Preconditions: rhs must be a tree
// Postconditions: true if the trees are not equal
bool BinTree::operator!=(const BinTree &rhs) const
{
    return *this == rhs ? false : true;
}

// This function retrieves the node from the tree (is node is present)
// Preconditions: None
// Postconditions: True if node is found
bool BinTree::retrieve(const NodeData &nodeD, NodeData *&nodeData)
{
    // Calls helper function
    helperRetrieve(nodeD, nodeData, this->root);

    // Returns true if nodeData is not null
    return nodeData != NULL ? true : false;
}

// Helper function for retrieve
bool BinTree::helperRetrieve(const NodeData &nodeD, NodeData *&nodeData, Node *currNode) const
{
    // Returns false if current node is NULL
    if (currNode == NULL)
    {
        nodeData = NULL;
        return false;
    }
    else
    {
        if (*currNode->data == nodeD)
        {
            // Current node's data assigned to ans if node found
            NodeData *ans(currNode->data);
            nodeData = ans;

            return true;
        }
        else if (*currNode->data > nodeD)
        {
            // Recursive call to function with left child if node to be found is less than current node
            helperRetrieve(nodeD, nodeData, currNode->left);
        }
        else if (nodeD > *currNode->data)
        {
            // Recursive call to function with right child if node to be found is greater than current node
            helperRetrieve(nodeD, nodeData, currNode->right);
        }
    }
    return false;
}

// Inserts the node in the current tree
// Preconditions: Private function uses the node to be inserted
// Postconditions: true if node inserted successfully
bool BinTree::insert(NodeData *node)
{
    return helperInsert(this->root, node);
}

// Helper function for insert
bool BinTree::helperInsert(Node *&node, NodeData *newNode)
{
    if (node == NULL)
    {
        // New Node created if node is NULL
        node = new Node;

        // node's data set to newNode
        node->data = newNode;

        // left and right children are set to NULL
        node->left = NULL;
        node->right = NULL;
    }
    else if (*newNode < *node->data)
    {
        // Recursive call with left child if node to be inserted is less than current node
        helperInsert(node->left, newNode);
    }
    else if (*newNode > *node->data)
    {
        // Recursive call with right child if node to be inserted is greater than current node
        helperInsert(node->right, newNode);
    }
    else
    {
        return false;
    }

    return true;
}

// Returns the height of a node in the tree
// Preconditions: tree should be present for the node's height
// Postconditions: the height should be between 0-100
int BinTree::getHeight(const NodeData &node) const
{
    // Call to helper function if root of tree is present
    return this->root != NULL ? helperGetHeight(node, this->root) : 0;
}

// Helper function for getHeight
int BinTree::helperGetHeight(const NodeData &node, Node *currNode) const
{
    // Returns 0 if node is not present in the tree
    if (currNode == NULL)
    {
        return 0;
    }
    // Calls the other helper function if the node is found
    else if (*currNode->data == node)
    {
        return helperGetHeight2(currNode);
    }
    // Recursive calls with left and right children
    int left = helperGetHeight(node, currNode->left);
    int right = helperGetHeight(node, currNode->right);

    // Returns the max value of left and right children
    return max(left, right);
}

// Another helper function for get height
int BinTree::helperGetHeight2(Node *currNode) const
{
    // Returns recursive call to function with left and right children with addition to 1
    return currNode == NULL ? 0 : 1 + max(helperGetHeight2(currNode->left), helperGetHeight2(currNode->right));
}

// Converts a BST to an array
// Preconditions: None
// Postconditions: array is in BST sorted order where current tree is deleted
void BinTree::bstreeToArray(NodeData *arr[])
{
    // Calls helper function to convert BST to an array
    helperBstreeToArray(arr, this->root);

    // Deletes current tree
    this->makeEmpty();
}

// Helper function for bstreetoarray
int BinTree::helperBstreeToArray(NodeData *arr[], Node *currNode)
{
    int ans = 0;
    // Returns 0 if current node is NULL
    if (currNode == NULL)
    {
        return ans;
    }
    else
    {
        // Left child is initialized in the helper function
        int leftNode = helperBstreeToArray(arr, currNode->left);

        // NewNode is created
        NodeData *newNode;

        // NewNode NodeData is set to current node's data
        newNode = currNode->data;

        // Current node's data is set to NULL
        currNode->data = NULL;

        // arr is now newNode
        *(arr + leftNode) = newNode;

        // newNode is set to NULL afterwards so recursive calls can be made
        newNode = NULL;

        // Right child is initialized in the helper function
        int rightNode = helperBstreeToArray(arr, currNode->right);

        // ans is set to the value of left child + right child + 1
        ans = leftNode + rightNode + 1;
    }
    return ans;
}

// Converts an array to a BST
// Preconditions: None
// Postconditions: current BST is deleted to convert arr into a new BST
void BinTree::arrayToBSTree(NodeData *arr[])
{
    // Deleting current tree
    this->makeEmpty();

    // Initializing hi value and counter
    int hi = 0, count = 0;

    // array might has < 50 items
    while (count != 50)
    {
        // arr[count] is set to NULL if it does not point towards the node
        if (arr[count] == NULL)
        {
            arr[count] = NULL;
        }
        // Counts the number of nodes otherwise
        else
        {
            ++hi;
        }
        ++count;
    }
    // Calls helper function with the root of the tree
    helperArrayToBSTree(arr, this->root, 0, hi - 1);
}

// Helper function for converting an array to a BST
void BinTree::helperArrayToBSTree(NodeData *arr[], Node *currNode, int hi, int low)
{
    if (hi >= low)
    {
        // Finds the middle nodeData
        int m = (low + hi) / 2;

        // Initializes newNode as a new NodeData
        NodeData *newNode = new NodeData();

        // NewNode is assigned to the middle value of the array
        newNode = arr[m];

        // After assigning, middle element is set to NULL
        arr[m] = NULL;

        // calls insert function to insert newNode in the tree
        this->insert(newNode);

        // Recursive calls with left and right sides of the array
        helperArrayToBSTree(arr, currNode, low, m - 1);
        helperArrayToBSTree(arr, currNode, m + 1, hi);
    }
    // currNode is set to NULL if low value is greater
    else
    {
        currNode = NULL;
    }
}

// Displays the tree sideways
void BinTree::displaySideways() const
{
    sideways(this->root, 0);
}

// helper function for displaySideways
void BinTree::sideways(Node *current, int level) const
{
    if (current != NULL)
    {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--)
        {
            cout << "    ";
        }

        cout << *current->data << endl; // display information of object
        sideways(current->left, level);
    }
}