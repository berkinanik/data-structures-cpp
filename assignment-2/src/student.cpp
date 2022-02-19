#include <iostream>
#include <string>
#include "student.h"
#include "section.h"

using namespace std;

//constructor
Student::Student(const int &id, const SectionPtr preferences[], const int &preferenceCount) {
    if (preferenceCount >= 1 && preferenceCount <= 3) {
        mId = id;
        mPreferences = new SectionPtr[preferenceCount];
        for (int i = 0; i < preferenceCount; i++) {
            *(mPreferences + i) = preferences[i];
        }
        mPreferenceCount = preferenceCount;
    } else {
        cerr << "Invalid preference count";
        exit(1);
    };
}

//destructor
Student::~Student() {
    if (mPreferences != NULL) {
        delete[] mPreferences;
    }
}

// Copy Constructor
Student::Student(const Student &other) {
    mId = other.getId();
    mPreferences = new SectionPtr[other.getPreferenceCount()];
    for (int i = 0; i < other.getPreferenceCount(); i++) {
        *(mPreferences + i) = *(other.getPreferences() + i);
    }
    mPreferenceCount = other.getPreferenceCount();
}

// Assignment Operator
Student& Student::operator=(const Student &rhs) {
    if (this == &rhs) { return *this; } // handle self assignment
    mId = rhs.getId();
    mPreferences = new SectionPtr[rhs.getPreferenceCount()];
    for (int i = 0; i < rhs.getPreferenceCount(); i++) {
        *(mPreferences + i) = *(rhs.getPreferences() + i);
    }
    mPreferenceCount = rhs.getPreferenceCount();
    return *this;
}

int Student::getEligibleSectionCount(void) const {
    int sCount = 0;
    for (int i = 0; i < mPreferenceCount; i++) {
        const Section *currentSec = (*(mPreferences + i));
        if (!currentSec->sIsFull()) {
            sCount++;
        }
    }
    return sCount;
}

Section* Student::getMostPreferredSection(void) const {
    for (int i = 0; i < mPreferenceCount; i++) {
        const Section *currentSec = (*(mPreferences + i));
        if (!currentSec->sIsFull()) {
            return *(mPreferences + i);
        }
    }
}

string Student::getPreferencesAsText(void) const {
    string preferenceText;
    for (int i = 0; i < getPreferenceCount(); i++) {
        preferenceText += (*(mPreferences + i))->getDay();
    }
    return preferenceText;
}

// << operator custom overload implementation
ostream& operator<<(ostream &os, const Student &student) {
    return os << "Student " << student.getId() << " with preferences " << student.getPreferencesAsText();
}
