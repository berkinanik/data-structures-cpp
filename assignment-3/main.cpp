#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Node.h"
#include "LinkedListRQ.h"
#include "BSTNode.h"

// BERKIN ANIK
// EE441 HW3

// RESULTS OBTAINED:
// You might check the txt files generated with different processes input texts and related outputs
// Program is run seperately for linked list and binary search tree implementation
// If you want to perform different aproach comment used block and uncomment other code block
// You need to comment out other part for right operation because operations performed on
// process nodes using pointers for processes, thus runtimes of processes are updated inplace.
//
// Linked list implementation works well for less number of processes because,
// In insertion linked list is need to traverse more nodes compared to BST beacuse it searches linearly
// Insertion complexity is bigger compared to BST, more process = more node traverse required
// But searching is much more faster compared to BST. After insertions head of the linked list is always
// the most prioritized processes. Searching always requires only 1 node to be reached (head node)
//
// BST implementation works well for higher number of processes because,
// Insertion is completed much faster compared to linked list. Binary search allowes logaritmic search
// complexity thus works much faster for insertion compared to linked list.
// But for searching since removal from bst and looking for the most prioritized process requires
// non constant numbers of nodes to be traversed, it has worse performance in searching compared to LL
// Non balanced implementation also affects performance of bst in a bad way.
//
// Overall Linked list is seems to be a better aproach for a less number of processes (~N<100)
// But for higher number of processes BST is a much better aproach. It requires by far less number of
// node traversal overall compared to linked list implementation. For example:
// for N=1000 processes
// BST node visit counts:
// 20522 nodes visited for searching
// 9261 nodes visited for insertion
// Linked list node visit counts:
// 1000 nodes visited for searching
// 157747 nodes visited for insertion
//
// You might check some other comments in this file also in the header files of the project
// for further explanations of some algorithms used for operation and meaning of some complex lines

using namespace std;

int main() {
    /* reading processes from file */
    ifstream processesFile; /* input file stream */
    processesFile.open("processes.txt");
    if (processesFile) { // check if process.txt is opened successfully
        // Node class is implemented to match the format used in this code block.
        // following codeblock is taken from the hw manual.
        int numProcesses; /* number of processes */
        processesFile >> numProcesses; /* read from file */
        Node process[numProcesses]; /* create Node array */
        int processID, arrivalTime, runTime, priority;
        for (int i = 0; i < numProcesses; ++i) {
            /* read 4 integers from file */
            processesFile >> processID >> arrivalTime >> runTime >> priority;
            /* construct i'th element of the array */
            process[i] = Node(processID, arrivalTime, runTime, priority);
        }
        /* end of reading from file */
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // LINKED LIST PART
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Creating linked list rq
        LinkedListRQ readyQueueLL = LinkedListRQ();
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // LinkedList is implemented as a class which stores the head of the list as a LinkedList Node (LLNode class)
        // All methods for linked list operations such as inserting deleting checking if list empty etc.
        // implemented as member functions of LinkedListRQ class
        // LinkedListRQ class takes Node class (process) pointers as input for its operations
        // It performs necessary creation and desctruction operations of new LLNode containing those Nodes under the hood
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Some TESTS for inserting process into linked list rq depending on the priorities.
        // After insertions highest priority process is always in front of the rq.
//        for (int i = 0; i < numProcesses; i++) {
//            readyQueueLL.insertProcess(&process[i]);
//        }
//        int processCount = 0;
//        for (int i = 0; i < numProcesses; i++) {
//            Node *currProcess = readyQueueLL.deleteProcess();
//            if (currProcess) {
//                processCount++;
//                printf("process (#%d) %d %d %d %d\n", processCount, currProcess->getPID(), currProcess->getArrTime(), currProcess->getRunTime(), currProcess->getPriority());
//            }
//        }
//        readyQueueLL.printLLRQ();
        // end of linked list TESTS
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /*ofstream linkedListOutputTxt;
        string linkedListOutputFileName;
        linkedListOutputFileName = "sampleOutput" + to_string(numProcesses) + "_LinkedList.txt";
        linkedListOutputTxt.open(linkedListOutputFileName);
        int time = 0;
        bool CPUBusy = false;
        Node* currentProcess;
        int processIndex = 0;
        while (processIndex < numProcesses || !readyQueueLL.llRQEmpty() || CPUBusy) {
            if (processIndex < numProcesses) { // there are processes not inserted into RQ
                if (process[processIndex].getArrTime() == time) { // if the process arrived now
                    readyQueueLL.insertProcess(&process[processIndex]); // insert it into RQ
                    processIndex++; // next process awaits insertion
                }
            }
            if (CPUBusy) { // CPU is running a process
                currentProcess->setRunTime(currentProcess->getRunTime() - 1); // 1 clock cycle elapsed for running process
                if (currentProcess->getRunTime() == 0) { // if it was last cycle of the process
                    printf("PID: %d  \tfinished execution at time %d\n", currentProcess->getPID(), time); // process finished execution
                    linkedListOutputTxt << "PID: " << currentProcess->getPID() << "  \tfinished execution at time " << time << endl;
                    CPUBusy = false; // CPU is no longer running a process
                }
            }
            if (!CPUBusy && !readyQueueLL.llRQEmpty()) { // CPU is not running a process but there are processes awaiting execution
                currentProcess = readyQueueLL.deleteProcess(); // new process selected and removed from RQ
                CPUBusy = true; // CPU is now running a process
            }
            time++; // 1 clock cycle elapsed
        }
        printf("\n%d nodes visited for searching\n%d nodes visited for insertion\n\n", readyQueueLL.getSearchCount(), readyQueueLL.getInsertionCount());
        linkedListOutputTxt << endl << readyQueueLL.getSearchCount() << " nodes visited for searching" << endl;
        linkedListOutputTxt << readyQueueLL.getInsertionCount() << " nodes visited for insertion" << endl;
        linkedListOutputTxt.close();*/
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // BINARY SEARCH TREE PART
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Creating Ready Queue as Binary Search Tree
        BSTNode *bstRQHead = NULL;
        // Created to integer pointers to count visited nodes while using BST RQ.
        int* bstInsertionCount = new int(0);
        int* bstSearchCount = new int(0);
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Binary Search Tree is implemented with a BSTNode class which contains process Node pointers as data
        // Methods for necessary operations of BST are implemented as static methods of BSTNode class
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // BST methods for traversing and adding new nodes to tree are implemented as recursive functions
        // Only head of the BST is stored and necessary operations are performed with static methods
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Some TESTS for adding process to binary search tree
        // After addition BST is traversed inorder LNR to reach processes in ascending order of their priorities
        // smallest priority value will be reached first (highest priority process)
//        for (int i = 0; i < numProcesses; i++) {
//            bstRQHead = BSTNode::addProcess(bstRQHead, &process[i], bstInsertionCount);
//        }
//        cout << "BST Nodes visited for insertion: " << *bstInsertionCount << endl;
//        cout << "PID: " << BSTNode::getMaxPriorityProcess(bstRQHead, bstSearchCount)->getPID() << "  \t" << "Priority: " << BSTNode::getMaxPriorityProcess(bstRQHead, bstSearchCount)->getPriority() << endl;
//        cout << "PID: " << BSTNode::getMinPriorityProcess(bstRQHead, bstSearchCount)->getPID() << "  \t" << "Priority: " << BSTNode::getMinPriorityProcess(bstRQHead, bstSearchCount)->getPriority() << endl;
//        cout << "BST Nodes visited for searching: " << *bstSearchCount << endl;
//        BSTNode::printBSTRQ(bstRQHead);
//        Node *maxPriorityProcess = BSTNode::getMaxPriorityProcess(bstRQHead, bstSearchCount);
//        cout << "max priority process: PID: " << maxPriorityProcess->getPID() << "  \tPriority: " << maxPriorityProcess->getPriority() << endl;
//        BSTNode::removeFromTree(bstRQHead, maxPriorityProcess->getPriority(), bstSearchCount);
//        BSTNode::printBSTRQ(bstRQHead);
        // End of BST TESTS
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ofstream bstOutputTxt;
        string bstOutputFileName;
        bstOutputFileName = "sampleOutput" + to_string(numProcesses) + "_BST.txt";
        bstOutputTxt.open(bstOutputFileName);
        int time = 0;
        bool CPUBusy = false;
        Node *currentProcess = NULL;
        int processIndex = 0;
        while (processIndex < numProcesses || bstRQHead != NULL || CPUBusy) {
            if (processIndex < numProcesses) { // there are processes not inserted into RQ
                if (process[processIndex].getArrTime() == time) { // if the process arrived now
                    bstRQHead = BSTNode::addProcess(bstRQHead, &process[processIndex], bstInsertionCount); // insert it into RQ
                    processIndex++; // next process awaits insertion
                }
            }
            if (CPUBusy) { // CPU is running a process
                currentProcess->setRunTime(currentProcess->getRunTime() - 1); // 1 clock cycle elapsed for running process
                if (currentProcess->getRunTime() == 0) { // if it was last cycle of the process
                    printf("PID: %d  \tfinished execution at time %d\n", currentProcess->getPID(), time); // process finished execution
                    bstOutputTxt << "PID: " << currentProcess->getPID() << "  \tfinished execution at time " << time << endl;
                    CPUBusy = false; // CPU is no longer running a process
                }
            }
            if (!CPUBusy && bstRQHead != NULL) { // CPU is not running a process but there are processes awaiting execution
                currentProcess = BSTNode::getMaxPriorityProcess(bstRQHead, bstSearchCount); // new process selected
                bstRQHead = BSTNode::removeFromTree(bstRQHead, currentProcess->getPriority(), bstSearchCount); // removed from rq
                CPUBusy = true; // CPU is now running a process
            }
            time++; // 1 clock cycle elapsed
        }
        printf("\n%d nodes visited for searching\n%d nodes visited for insertion\n\n", *bstSearchCount, *bstInsertionCount);
        bstOutputTxt << endl << *bstSearchCount << " nodes visited for searching" << endl;
        bstOutputTxt << *bstInsertionCount << " nodes visited for insertion" << endl;
        bstOutputTxt.close();
        return 0;
    } else {
        cerr << "Couldn't find processes.txt\n";
    }
}
