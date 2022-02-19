#include <iostream>
#include "Course.h"
#include "Student.h"

using namespace std;

// setter declerations
void Course::addNewStudent(Student new_student) {
    if (this->num < this->max_size) {
        for (int i = 0; i < this->num; i++) {
            if (this->students[i].getId() == new_student.getId()) {
                cout << "Student with ID: " << new_student.getId() << " already exists" << endl;
                this->students[i].getStudentInfo(this->weights);
                return;
            }
        }
        this->students[num] = new_student;
        num++;
        cout << "Student: " << new_student.getName() + " " + new_student.getSurname() << " is added!" << endl;
    } else {
        cout << "Course capacity is full!" << endl;
    }
};

void Course::updateWeights(const int new_weights[3]) {
    cout << "New Weights: ";
    for (int i = 0; i < 3; i++) {
        this->weights[i] = new_weights[i];
        cout << new_weights[i] << " ";
    }
    cout << endl;
};

// method definitions
void Course::calculateAverage(void) const {
    float quizTotal = 0;
    float hwTotal = 0;
    float finalTotal = 0;
    float overallTotal = 0;
    for (int i = 0; i < this->num; i++) {
        quizTotal += students[i].getQuizAverage();
        hwTotal += students[i].getHwAverage();
        finalTotal += students[i].getFinalScore();
        overallTotal += students[i].overallCourseScore(this->weights);
    }
    float quizAverage = quizTotal / this->num;
    float hwAverage = hwTotal / this->num;
    float finalAverage = finalTotal / this->num;
    float overallAverage = overallTotal / this->num;
    cout << "Quiz Average: " << quizAverage << endl;
    cout << "Hw Average: " << hwAverage << endl;
    cout << "Final Exam Average: " << finalAverage << endl;
    cout << "Overall Score Average: " << overallAverage << endl;
};

void Course::getStudentInfo(const int id) const {
    for (int i = 0; i < this->num; i++) {
        if (this->students[i].getId() == id) {
            this->students[i].getStudentInfo(this->weights);
            return;
        }
    }
    cout << "Cannot find student with id : " << id << endl;
};

Student* Course::findStudentById(const int id) {
    for (int i = 0; i < this->num; i++) {
        if (this->students[i].getId() == id) {
            return &this->students[i];
        }
    }
    return NULL;
};

void Course::filterStudents(const int threshold, const int method) const {
    switch (method) {
    case 1:
        for (int i = 0; i < this->num; i++) {
            if (this->students[i].overallCourseScore(this->weights) > threshold) {
                this->students[i].getStudentInfo(this->weights);
            }
        }
        break;
    case 0:
        for (int i = 0; i < this->num; i++) {
            if (this->students[i].overallCourseScore(this->weights) < threshold) {
                this->students[i].getStudentInfo(this->weights);
            }
        }
        break;
    default:
        cout << "Invalid filter method" << endl;
        break;
    }
};
