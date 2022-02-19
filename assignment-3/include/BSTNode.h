#ifndef BSTNODE_H
#define BSTNODE_H

#include "Node.h"

class BSTNode {
  private:
    BSTNode *right, *left;
    Node* process;
  public:
    /** Default constructor */
    BSTNode(Node *process, BSTNode *rightPtr = 0, BSTNode *leftPtr = 0) : process(process), right(rightPtr), left(leftPtr) {}
    /** Default destructor */
    virtual ~BSTNode() {}

    static BSTNode* addProcess(BSTNode *tree, Node *addedProcess, int *&insertionCount) {
        if (tree == NULL) {
            BSTNode *newNode = new BSTNode(addedProcess);
            return newNode;
        }
        *insertionCount = (*insertionCount) + 1;
        if (tree->process->getPriority() < addedProcess->getPriority()) {
            tree->right = addProcess(tree->right, addedProcess, insertionCount);
            return tree;
        } else {
            tree->left = addProcess(tree->left, addedProcess, insertionCount);
            return tree;
        }
    }

    static void printBSTRQ(BSTNode *tree) { // recersively prints out the bst for debug purposes
        if (tree == NULL) {
            return;
        }
        // traverses the binary tree in order (Left Node Right)
        printBSTRQ(tree->left);
        printf("Process id: %d   \tpriority: %d\n", tree->process->getPID(), tree->process->getPriority());
        printBSTRQ(tree->right);
    }

    static Node* getMinPriorityProcess(BSTNode *tree, int *&searchCount) { // returns process Node with the biggest priority int value (least prioritized)
        if (tree == NULL) {
            return NULL;
        }
        *searchCount = (*searchCount) + 1;
        while (tree->right != NULL) {
            *searchCount = (*searchCount) + 1;
            tree = tree->right;
        }
        return tree->process;
    }

    static Node* getMaxPriorityProcess(BSTNode *tree, int *&searchCount) { // returns process Node with the smallest priority int value (most prioritized)
        if (tree == NULL) {
            return NULL;
        }
        *searchCount = (*searchCount) + 1;
        while (tree->left != NULL) {
            *searchCount = (*searchCount) + 1;
            tree = tree->left;
        }
        return tree->process;
    }

    static bool isLeafNode(BSTNode *node) { // checks if the given BSTNode is a leaf node
        return node->left == NULL && node->right == NULL;
    }

    static BSTNode* removeFromTree(BSTNode *tree, const int priority, int *&searchCount) {
        if (tree == NULL) {
            return NULL;
        }
        *searchCount = (*searchCount) + 1;
        if (tree->process->getPriority() == priority) {
            if (isLeafNode(tree)) { // removes leaf node from bst
                delete tree; // deallocates memory for removed node
                return NULL;
            }
            // if removed node is not a leaf node
            if (tree->right != NULL) {
                tree->process = getMaxPriorityProcess(tree->right, searchCount); // smallest priority value node is replaced with removed tree node
                tree->right = removeFromTree(tree->right, tree->process->getPriority(), searchCount); // replaced tree node is removed from tree
                return tree;
            }
            // if right of node is null
            tree->process = getMinPriorityProcess(tree->left, searchCount); // biggest priority value node is replaced with the removed tree node
            tree->left = removeFromTree(tree->left, tree->process->getPriority(), searchCount); // replaced tree node is removed from tree
            return tree;
        }
        if (tree->process->getPriority() < priority) { // if searched value is bigger, keep searching on right of the node
            tree->right = removeFromTree(tree->right, priority, searchCount);
            return tree;
        }
        // if searched value is smaller, keep searching on left of the node
        tree->left = removeFromTree(tree->left, priority, searchCount);
        return tree;
    }
};

#endif // BSTNODE_H
