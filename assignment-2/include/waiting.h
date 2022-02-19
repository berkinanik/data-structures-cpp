#ifndef WAITING_H
#define WAITING_H

#include <myqueue.h>

class Student; // as in the student class where Section object is defined Student is defined

// Waiting Queue holds values of Pointers to Student objects in it
class Waiting : public MyQueue<Student*> {
  private:

  public:
    /** constructor */
    Waiting(const int &qSize) : MyQueue(qSize) {};
    /** destructor */
    ~Waiting() {};
};

#endif // WAITING_H
