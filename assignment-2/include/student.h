#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

class Section; // Section class defined to tell compiler this class exists
// Direct including of Section class from Section.h would cause Circular Import error
// Both classes holds each others' pointers as properties of them
// Student objects holds preferences as pointers to existing Section objects
typedef Section* SectionPtr;

class Student {
  private:
    // private member variables
    int mId;
    SectionPtr* mPreferences;
    int mPreferenceCount;

  public:
    /*constructors*/
    Student() {};
    Student(const int &id, const SectionPtr preferences[], const int &preferenceCount);
    /*destructor*/
    ~Student();
    // copy constructor and assignment operator are implemented as a practice
    /*Copy constructor*/
    Student(const Student &other);
    /*Assignment operator*/
    Student& operator=(const Student &other);

    /*getters for private member variables*/
    int getId(void) const { return mId; };
    SectionPtr* getPreferences(void) const { return mPreferences; }
    int getPreferenceCount(void) const { return mPreferenceCount; }
    int getEligibleSectionCount(void) const;
    Section* getMostPreferredSection(void) const;
    string getPreferencesAsText(void) const;

    // overloading << operator to have custom Student output to console
    friend ostream& operator<<(ostream &os, const Student &student);
};

#endif // STUDENT_H
