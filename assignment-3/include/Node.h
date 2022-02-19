#ifndef NODE_H
#define NODE_H

class Node {
  private:
    int processID, arrivalTime, runTime, priority;
  public:
    /** Default constructor */
    Node() {};
    Node(const int &pPID, const int &pArrTime, const int &pRunTime, const int &pPriority) :
        processID(pPID), arrivalTime(pArrTime), runTime(pRunTime), priority(pPriority) {};
    /** Default destructor */
    virtual ~Node() {}

    // getter methods for private data members of Node class
    // they won't be changed
    // created while initializing a Node
    const int getPID(void) {return processID;};
    const int getArrTime(void) {return arrivalTime;};
    const int getPriority(void) {return priority;};

    // getter and setter of process run time
    const int getRunTime(void) {return runTime;};
    void setRunTime(const int &newRunTime) {
        runTime = newRunTime;
    };
};

#endif // NODE_H
