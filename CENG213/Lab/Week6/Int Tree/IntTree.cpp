#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "IllegalArgumentException.h"

#include "IntTree.h"

using namespace std;

// PUBLIC MEMBER FUNCTIONS:

// Default constructor.
IntTree::IntTree(IntTreeNode *r ) {
    root = r;
}

// Constructor that creates a full binary tree of a given height.
IntTree::IntTree(int height) {
    /* initialize random seed: */
    srand (time(NULL));
    root = NULL;
    construct(root, height);
}

// Constructor that creates a full binary tree of a given integer array.
IntTree::IntTree(int *arr, int length) {
    root = NULL;
    constructWithArray(root, arr, 0, length);
}

// Destructor.
IntTree::~IntTree() {
    deleteTree(root);
}

// Copy constructor
IntTree::IntTree(const IntTree &t) {
    if(t.root == NULL)
        root = NULL;
    else
        make_copy(root, t.root);
}

// Assignment operator
IntTree& IntTree::operator=(const IntTree &t) {
    if(this != &t) {
        deleteTree(root);
        make_copy(root, t.root);
    }
    return *this;
}

// Prints this tree in inorder.
void IntTree::print() {
    printInOrder(root);
    cout << endl;
}

// Prints this tree sideways.
void IntTree::printSideways() {
    printSideways(root, "");
}

// Returns the maximum value in this binary tree.
int IntTree::getMax() {
    return (getMax(root));
}

// Finds the sum of all values in this tree.
int IntTree::find_sum() {
    return find_sum(root);
}

/* TODO : Q1 */
/* Returns the height of the tree.
 */
int IntTree::height() {
    return height(root);
}

/* TODO : Q2 */
/* Returns if the tree contains the value val or not.
 */
bool IntTree::contains(int val) {
    return contains(root, val);
}

/* TODO : Q3 */
/* Prints the leaves of the tree from right to left 
 * (i.e. the leaves must be printed in the reverse order that 
 * they would be printed using a standard traversal). 
 * If the tree is empty your method should produce the output "no leaves”.
 */
void IntTree::printLeaves() {
    if (!root)
    {
        std::cout << "no leaves\n";
    }
    else
    {
        printLeaves(root);
    }
}

/* TODO : Q4 */
/* Changes the data stored in the tree, assigning sequential integers 
 * starting with 1 to each node so that preorder traversal will produce 
 * the numbers in order (1, 2, 3, etc.).
 */
void IntTree::numberNodes() {
    int n = 1;
    if (root)
    {
        numberNodes(root, n);
    }
}

/* TODO : Q5 */
/* Removes the leaves from the tree. 
 * A leaf node is a node that has empty left and right subtrees. 
 * If method is called on an empty tree, it does not change the tree. 
 */
void IntTree::removeLeaves() {
    IntTreeNode *temp;
    int left_deleted = 0, right_deleted = 0;
    if (root)
    {
        if (!root->left && !root->right)
        {
            temp = root;
            delete temp;
            root = NULL;
        }
        else
        {
            if (root->left && !root->left->left && !root->left->right)
            {
                temp = root->left;
                delete temp;
                root->left = NULL;
                left_deleted = 1;
            }
            if (root->right && !root->right->left && !root->right->right)
            {
                temp = root->right;
                delete temp;
                root->right = NULL;
                right_deleted = 1;
            }
            if (!left_deleted)
            {
                removeLeaves(root->left);
            }
            if (!right_deleted)
            {
                removeLeaves(root->right);
            }
        }
    }
}

/* TODO : Q6 */
/* Accepts an integer n and prints the values at level n 
 * from left to right on one line. 
 * (Root of the tree is at level 1, its children are at level 2 and so on). 
 * If there are no values at the level, method should produce no output. 
 * The method should throw an IllegalArgumentException if 
 * it is passed a value for a level that is less than 1.
 */
void IntTree::printLevel(int n) {
    
    if (n < 1)
    {
        throw IllegalArgumentException();
    }
    else
    {
        if (root)
        {
            printLevel(root, n-1);
        }
    }
}

// PRIVATE MEMBER FUNCTIONS:

// Helper method to construct a binary tree with a given height.
void IntTree::construct(IntTreeNode *&r, int h) {
    if (h>-1) {
        r = new IntTreeNode(rand() % 100 + 1);  // data value is in range 1..100
        construct(r->left, h-1);                // construct left subtree
        construct(r->right, h-1);               // construct right subtree
    }
}

// Helper method to construct a binary tree with a given array.
void IntTree::constructWithArray(IntTreeNode *&r, int *arr, int ind, int length) {
    if (ind < length) {
        r = new IntTreeNode(arr[ind]);
        if(2*ind+1 < length)
            constructWithArray(r->left, arr, 2*ind+1, length);
        if(2*ind+2 < length)
            constructWithArray(r->right, arr, 2*ind+2, length);
    }
}

// Helper method to delete all nodes in a tree.
void IntTree::deleteTree(IntTreeNode *&r) {
    if (r == NULL)
        return;
    deleteTree(r->left);
    deleteTree(r->right);
    delete r;
    r = NULL;
}

// Make t1 a deep copy of t2.
void IntTree::make_copy(IntTreeNode *&r1, IntTreeNode *r2) {
    if(r2 != NULL) {
        r1 = new IntTreeNode(r2->data);
        make_copy(r1->left, r2->left);
        make_copy(r1->right, r2->right);
    }
    else
        r1 = NULL;

}

// Helper method to print the nodes in inorder.
void IntTree::printInOrder(IntTreeNode *r) {
    if (r != NULL) {
        printInOrder(r->left);
        cout << r->data << " ";
        printInOrder(r->right);
    }
}

// Helper method to print the nodes sideways.
void IntTree::printSideways(IntTreeNode *r, string str) {
    if (r != NULL) {
        printSideways(r->right, str+"   ");
        cout << str << r->data <<  endl;
        printSideways(r->left, str + "   ");
    }
}

// Helper method to find the maximum value in this binary tree.
int IntTree::getMax(IntTreeNode *r) {
    int root_val, left, right, maxi;
    maxi = -1; // Assuming all values are positive integers

    if (r != NULL) {
        root_val = r->data;
        left = getMax(r->left);
        right = getMax(r->right);
        // Find the largest of the three values.
        if (left > right)
            maxi = left;
        else
            maxi = right;
        if (root_val > maxi)
            maxi = root_val;
    }
    return maxi;
}

// Helper method to find the overall sum of values.
int IntTree::find_sum(IntTreeNode *r) {
    if (r == NULL)
        return 0;
    else
        return (find_sum(r->left) + find_sum(r->right) + r->data);
}

/* TODO : Q1 : helper function */
int IntTree::height(IntTreeNode *r) {
    int height1, height2;
    if (!r)
    {
        return -1;
    }
    else
    {
        height1 = height(r->left);
        height2 = height(r->right);
        return height2 < height1 ? height1+1: height2+1;
    }
}

/* TODO : Q2 : helper function */
bool IntTree::contains(IntTreeNode *r, int val) {
    if (!r)
    {
        return false;
    }
    else
    {   
        if (r->data == val)
        {
            return 1;
        }
        else
        {
            return contains(r->left, val) || contains(r->right, val);
        }
    }
}

/* TODO : Q3 : helper function */
void IntTree::printLeaves(IntTreeNode *r) {
    if (r)
    {
        if (!r->left && !r->right)
        {
            std::cout << r->data << " ";
        }
        else
        {
            printLeaves(r->right);
            printLeaves(r->left);
        }
    }
}

/* TODO : Q4 : helper function */
void IntTree::numberNodes(IntTreeNode *r, int &n) {
    if (r)
    {
        r->data = n++;
        numberNodes(r->left, n);
        numberNodes(r->right, n);
    }
}

/* TODO : Q5 : helper function */
void IntTree::removeLeaves(IntTreeNode *&r) {
    IntTreeNode *temp;
    int left_deleted = 0, right_deleted = 0;
    if (r)
    {
        if (!r->left && !r->right)
        {
            temp = r;
            delete temp;
            root = NULL;
        }
        else
        {
            if (r->left && !r->left->left && !r->left->right)
            {
                temp = r->left;
                delete temp;
                r->left = NULL;
                left_deleted = 1;
            }
            if (r->right && !r->right->left && !r->right->right)
            {
                temp = r->right;
                delete temp;
                r->right = NULL;
                right_deleted = 1;
            }
            if (!left_deleted)
            {
                removeLeaves(r->left);
            }
            if (!right_deleted)
            {
                removeLeaves(r->right);
            }
        }
    }
}

/* TODO : Q6 : helper function */
void IntTree::printLevel(IntTreeNode *r, int n) {
    if (r)
    {
        if (n == 0)
        {
            std::cout << r->data << " ";
        }
        if (n > 0)
        {
            printLevel(r->left, n-1);
            printLevel(r->right, n-1);
        }
    }
}

int main()
{
    IntTree tree(-1);
    //tree.printLevel(1);
    //std::cout << "\n";
    //tree.printLevel(2);
    //std::cout << "\n";
    tree.removeLeaves();
    tree.printLevel(1);
    std::cout << "\n";
    return 0;
}