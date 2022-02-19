#ifndef LLNODE_H
#define LLNODE_H

#include "Node.h"

// Linked List Node is implemented as LLNode class
class LLNode {
  private:
    LLNode* next;
    Node* process;
  public:
    /** Default constructor */
    LLNode(Node *process, LLNode *nextPtr = 0) : process(process), next(nextPtr) {}
    /** Default destructor */
    virtual ~LLNode() {}

    void insertAfter(LLNode* ptr) {
        ptr->next = next;
        next = ptr;
    };

    LLNode* deleteAfter(void) {
        LLNode* tempPtr = next;
        if (tempPtr == NULL) {
            return NULL;
        } else {
            next = tempPtr->next;
            return tempPtr;
        }
    };

    LLNode* getNextNode(void) const {
        return next;
    };

    Node* getProcess(void) const {
        return process;
    };
};

#endif // LLNODE_H
