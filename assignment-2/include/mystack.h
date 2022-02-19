#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>

#define SIZE 10

using namespace std;

template <class T>
class MyStack {
  protected:
    // member variables are implemented as protected
    // later may be used in section class
    T *sArray;
    int sTop, sCapacity;

  public:
    // stack constructor and destructor implementations
    MyStack(const int &sSize = SIZE) {
        sArray = new T[sSize];
        sTop = -1;
        sCapacity = sSize;
    };

    virtual ~MyStack() {
        if (sArray != NULL) {
            delete[] sArray;
        }
    };

    // necessary stack methods and implementations
    int sPush(const T &item) {
        if (sIsFull()) {
            cerr << "Stack overflow\n";
            return 0;
        } else {
            sTop++;
            sArray[sTop] = item;
            return 1;
        }
    };

    T sPeek(void) const {
        if (sIsEmpty()) {
            cerr << "Stack empty\n";
        } else {
            return sArray[sTop];
        }
    };

    T sPop(void)  {
        if (sIsEmpty()) {
            cerr << "Stack empty\n";
        } else {
            T temp = sPeek();
            sTop--;
            return temp;
        }
    };

    int sIsEmpty(void) const {
        return sTop == -1;
    };

    int sIsFull(void) const {
        return sTop == sCapacity - 1;
    };

    void sClear(void) {
        sTop = -1;
    };
};

#endif // MYSTACK_H
