#include "iostream"
#include "section.h"

using namespace std;

Section::Section(const char &sDay, const int &sSize) : MyStack(sSize) {
    sectionDay = sDay;
}

// << operator custom overload implementation
ostream& operator<<(ostream &os, const Section &section) {
    return os << "Section " << section.getDay();
}
