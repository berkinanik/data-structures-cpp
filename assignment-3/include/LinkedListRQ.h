#ifndef LINKEDLISTRQ_H
#define LINKEDLISTRQ_H

#include <iostream>
#include "LLNode.h"

using namespace std;

class LinkedListRQ {
  private:
    LLNode *head;
    int searchCount = 0, insertionTraversingCount = 0;
  public:
    /** Default constructor */
    LinkedListRQ(LLNode *headPtr = 0) : head(headPtr) {};
    /** Default destructor */
    virtual ~LinkedListRQ() {};

    bool llRQEmpty(void) const {
        return head == NULL;
    }

    void insertProcess(Node *process) {
        LLNode *tempPtr = head;
        LLNode *prevPtr = NULL;
        int newProcessPriority = process->getPriority();
        insertionTraversingCount++; // increasing insertion traversed node count by one after calling insertProcess method
        if (head == NULL) {
            LLNode *newNode = new LLNode(process);
            if (newNode != NULL) {
                head = newNode;
            } else {
                cerr << "Memory allocation for new LLNode failed!\n";
                exit(1);
            }
            return;
        }
        while (tempPtr != NULL) {
            int currentPriority = tempPtr->getProcess()->getPriority();
            if (newProcessPriority >= currentPriority) {
                prevPtr = tempPtr;
                tempPtr = tempPtr->getNextNode();
                insertionTraversingCount++; // increasing insertion traversed node count by one again after moving tempPtr to next
            } else {
                if (tempPtr == head) {
                    LLNode *newNode = new LLNode(process, tempPtr);
                    if (newNode != NULL) {
                        head = newNode;
                        return;
                    } else {
                        cerr << "Memory allocation for new LLNode failed!\n";
                        exit(1);
                        return;
                    }
                } else {
                    LLNode *newNode = new LLNode(process);
                    if (newNode != NULL) {
                        prevPtr->insertAfter(newNode);
                        return;
                    } else {
                        cerr << "Memory allocation for new LLNode failed!\n";
                        exit(1);
                        return;
                    }
                }
                return;
            }
        }
        // Increasing count did not increased beacuse prevPtr is already visited and pointer is stored
        LLNode *newNode = new LLNode(process);
        if (newNode != NULL) {
            prevPtr->insertAfter(newNode);
            return;
        } else {
            cerr << "Memory allocation for new LLNode failed!\n";
            exit(1);
            return;
        }
    };

    Node* deleteProcess(void) {
        searchCount++;
        if (head != NULL) {
            LLNode* tempPtr = head;
            head = tempPtr->getNextNode();
            Node* currentProcess = tempPtr->getProcess();
            delete tempPtr;
            return currentProcess;
        } else {
            return NULL;
        }
    };

    void printLLRQ(void) const {
        LLNode *tempPtr = head;
        while (tempPtr != NULL) {
            printf("Process id: %d   \tpriority: %d\n", tempPtr->getProcess()->getPID(), tempPtr->getProcess()->getPriority());
            tempPtr = tempPtr->getNextNode();
        }
    }

    int getSearchCount(void) const {
        return searchCount;
    }

    int getInsertionCount(void) const {
        return insertionTraversingCount;
    }
};

#endif // LINKEDLISTRQ_H
