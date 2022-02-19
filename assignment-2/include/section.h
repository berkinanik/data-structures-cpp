#ifndef SECTION_H
#define SECTION_H

#include <iostream>
#include "mystack.h"

using namespace std;

class Student; // as in the student class where Section object is defined Student is defined

// Section Stack holds values of Pointers to Student objects in it
class Section : public MyStack<Student*> {
  private:
    char sectionDay;
  public:
    /** constructor */
    Section() {};
    Section(const char &sDay, const int &sSize);
    /** destructor */
    ~Section() {};

    char getDay(void) const { return sectionDay; };

    // overloading << operator to have custom output section to console
    friend ostream& operator<<(ostream &os, const Section &section);
};

#endif // SECTION_H
