#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>

#define SIZE 10

using namespace std;

template <class T>
class MyQueue {
  protected:
    // member variables are implemented as protected
    // later may be used in waiting class
    T *qArray;
    int qFront, qRear, qCount, qCapacity;

  public:
    // queue constructor and destructor implementations
    MyQueue(const int &qSize = SIZE) {
        qArray = new T[qSize];
        qFront = 0;
        qRear = 0;
        qCount = 0;
        qCapacity = qSize;
    };

    virtual ~MyQueue() {
        if (qArray != NULL) {
            delete[] qArray;
        }
    };

    // necessary queue methods and implementations
    void qInsert(const T &item) {
        if (qIsFull()) {
            cerr << "Queue overflow\n";
        } else {
            qCount++;
            qArray[qRear] = item;
            qRear = (qRear + 1) % qCapacity;
        }
    };

    T qDelete(void) {
        if (qIsEmpty()) {
            cerr << "Queue empty\n";
        } else {
            T temp = qPeek();
            qCount--;
            qFront = (qFront + 1) % qCapacity;
            return temp;
        }
    };

    void qClear(void) {
        qFront = 0;
        qRear = 0;
        qCount = 0;
    };

    T qPeek(void) const {
        return qArray[qFront];
    };

    int qLength(void) const {
        return qCount;
    };

    int qIsEmpty(void) const {
        return qCount == 0;
    };

    int qIsFull(void) const {
        return qCount == qCapacity;
    };
};

#endif // MYQUEUE_H
