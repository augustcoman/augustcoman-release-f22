/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>
#include <stack>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    if(root != NULL) {
        mirror(root);
    }
}

template <typename T>
void BinaryTree<T>::mirror(Node *subRoot) {
    if(subRoot != NULL) {
        Node* temp = subRoot->left;
        subRoot->left = subRoot->right;
        subRoot->right = temp;
        mirror(subRoot->left);
        mirror(subRoot->right);
    }
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    std::stack<typename BinaryTree<T>::Node*> stack;
    Node* current = root;
    Node* previous = NULL;
    while(current != NULL) {
        stack.push(current);
        current = current->left;
    }
    while(!stack.empty()) {
        previous = stack.top();
        current = stack.top()->right;
        stack.pop();
        while(current != NULL) {
            stack.push(current);
            current = current->left;
        }
        if(!stack.empty() && previous->elem > stack.top()->elem) {
            return false;
        }
    }
    return true;
}

/*
    Node* prev = NULL;
    InorderTraversal<T> traverser(root);
    for(typename TreeTraversal<T>::Iterator t = traverser.begin(); t != traverser.end(); ++t) {
        if(prev != NULL && (*t)->elem < prev->elem) {
            return false;
        }
        prev = *t;
    }
    return true;

    Node* prev = NULL;
    InorderTraversal<T> traverser(root);
    typename TreeTraversal<T>::Iterator t = traverser.begin();
    while(t != traverser.end()) {
        if(prev != NULL && (*t)->elem < prev->elem) {
            return false;
        }
        prev = *t;
        ++t;
    }
    return true;
*/

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    Node* previous = NULL;
    return recursiveOrderHelper(root, previous);
}


template <typename T>
bool BinaryTree<T>::recursiveOrderHelper(Node *subRoot, Node *&previous) const
{
    // your code here
    if(subRoot == NULL) {
        return true;
    }
    if(!recursiveOrderHelper(subRoot->left, previous)) {
        return false;
    }
    if(previous != NULL && previous->elem > subRoot->elem) {
        return false;
    }
    previous = subRoot;
    return recursiveOrderHelper(subRoot->right, previous);
}
