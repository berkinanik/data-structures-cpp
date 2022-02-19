#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "student.h"
#include "section.h"
#include "waiting.h"

using namespace std;

Section *sections[3];
Waiting waitingStudents = Waiting(50);

// Berkin ANIK
//There are 3 main classes for this program: Student, Section, Waiting
//Section class is inherited from a custom Stack (MyStack class)
//Waiting class is inherited from a custom Queue (MyQueue class)
//Section and Waiting classes hold Student pointers in their arrays
//With this approach, there are no unnecessary Student objects created
//Also Student objects holds preferences of students as pointers to Section classes
//Again this approach, allows efficient memory management
//Another important benefit of this approach is to allow programmer to
//call necessary methods on Section, Waiting or Student objects by accessing
//stored object by pointers stored as member variables in those classes
//(e.g. using Student pointer in Section or Queue or
//using Section pointer in Student class).

// this is the function to call in a loop for checking waiting students queue
// this function is called in a while loop depending on its return value
int checkWaitingStudents(const int &eligibleCount = 1) {
    int checkedStudentCount = 0;
    int waitingCount = waitingStudents.qLength();
    int assigningNow = 1;
    while (checkedStudentCount < waitingCount) {
        Student *checkedStudent = waitingStudents.qDelete();
        if (checkedStudent != NULL) {
            if (checkedStudent->getEligibleSectionCount() == eligibleCount && assigningNow) {
                Section *mostPreferred = checkedStudent->getMostPreferredSection();
                if (mostPreferred != NULL) {
                    const int added = mostPreferred->sPush(checkedStudent);
                    if (added) {
                        cout << *checkedStudent << " is added to " << *mostPreferred << " from waiting queue" << endl;
                        assigningNow = 0;
                        checkedStudentCount++;
                        continue;
                    }
                }
            }
            waitingStudents.qInsert(checkedStudent);
            checkedStudentCount++;
        } else {
            break;
        }
    }
    if (eligibleCount > 1) {
        while (checkWaitingStudents(eligibleCount - 1)) {}
    }
    if (assigningNow) { // no student has assigned exit
        return 0;
    } else {
        return 1;
    }
}

int main() {
    ifstream preferencesTxt;
    string inputTextFile = "preferences.txt";
    string outputTextFile = "out.txt";
    preferencesTxt.open(inputTextFile);
    char output[100];
    int sectionCount = 0;
    cout << "\nReading section details and student preferences from: " << inputTextFile << endl;
    // Reading of input from text file
    // first Sections are created then students are read and created one by one
    if (preferencesTxt.is_open()) {
        while (!preferencesTxt.eof()) {
            preferencesTxt >> output;
            if (sectionCount < 3) {
                sections[sectionCount] = new Section(output[0], (int)output[2] - 48);
                sectionCount++;
                cout << "Section " << output[0] << " with capacity ";
                cout << output[2] << " is created!" << endl;
            } else {
                int studentId = 0;
                int preferenceCount = 0;
                Section *preferences[3];
                int inputIndex = 3;
                for (int i = 2; i >= 0; i--) {
                    studentId = studentId + (((int)output[i] - 48) * pow(10, 2 - i));
                }
                while (output[inputIndex] != NULL) {
                    if (output[inputIndex] == ',') {
                        inputIndex++;
                    } else {
                        char sectionName = output[inputIndex];
                        Section* currentSec;
                        for (int i = 0; i < 3; i++) {
                            if (sections[i]->getDay() == sectionName) {
                                currentSec = sections[i];
                                break;
                            }
                        }
                        preferences[preferenceCount] = currentSec;
                        preferenceCount++;
                        inputIndex++;
                    }
                }
                Student* newStudent = new Student(studentId, preferences, preferenceCount);
                // If a student has only one eligible section s/he is assigned to that section if possible
                if (newStudent->getEligibleSectionCount() == 1) {
                    Section *mostPreferred = newStudent->getMostPreferredSection();
                    const int added = mostPreferred->sPush(newStudent);
                    if (added) {
                        cout << *newStudent << " is added to " << *mostPreferred << endl;
                        // After adding a student waiting queue is checked and assigned if any possible
                        while (checkWaitingStudents(1)) {}
                        continue;
                    }
                }
                waitingStudents.qInsert(newStudent);
                cout << *newStudent << " is added to waiting queue" << endl;
            }
        }
    }
    preferencesTxt.close();
    // after creating all students and constructing waiting queue correctly
    // unassigned students are considered to be assigned to available preferred sections
    while (checkWaitingStudents(3)) {}
    cout << "\nProgram Results: \n\n";
    ofstream outputtxt;
    outputtxt.open(outputTextFile);
    int printedSectionCount = 0;
    // since section input order might be random as indicated in the task
    // in order to print out results correctly sections are traversed 3*3 times
    // printing out the sections in correct order no matter the order of section input
    while (printedSectionCount < 3) {
        for (int i = 2; i >= 0; i--) {
            switch (sections[i]->getDay()) {
            case 'W':
                if (printedSectionCount == 0) {
                    cout << "Wednesday:\n";
                    outputtxt << "Wednesdey:\n";
                    break;
                } else {
                    continue;
                }
            case 'T':
                if (printedSectionCount == 1) {
                    cout << "Thursday:\n";
                    outputtxt << "Thursday:\n";
                    break;
                } else {
                    continue;
                }
            case 'F':
                if (printedSectionCount == 2) {
                    cout << "Friday:\n";
                    outputtxt << "Friday:\n";
                    break;
                } else {
                    continue;
                }
            default:
                break;
            }
            while (!sections[i]->sIsEmpty()) {
                Student *student = sections[i]->sPop();
                cout << student->getId() << endl;
                outputtxt << student->getId() << endl;
            }
            cout << endl;
            outputtxt << endl;
            printedSectionCount++;
        }
    }
    cout << "Unassigned:\n";
    outputtxt << "Unassigned:\n";
    while (!waitingStudents.qIsEmpty()) {
        Student *student = waitingStudents.qDelete();
        cout << student->getId() << endl;
        outputtxt << student->getId() << endl;
    }
    outputtxt.close();
    cout << "\nOutputted results to: " << outputTextFile << endl;
    return 0;
}
