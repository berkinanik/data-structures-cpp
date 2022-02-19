#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

// constructor definition
Student::Student(const int id, const string name, const string surname, const int quiz_scores[4], const int hw_scores[3], const int final_score) {
    this->id = id;
    this->name = name;
    this->surname = surname;
    for (int i = 0; i < 4; i ++) {
        this->quiz_scores[i] = quiz_scores[i];
    }
    for (int i = 0; i < 3; i ++) {
        this->hw_scores[i] = hw_scores[i];
    }
    this->final_score = final_score;
}

// setter definitions

void Student::setId(const int id) {
    this->id = id;
};

void Student::setName(const string name) {
    this->name = name;
};

void Student::setSurname(const string surname) {
    this->surname = surname;
};

void Student::setQuizScores(const int quiz_scores[4]) {
    for (int i = 0; i < 4; i ++) {
        this->quiz_scores[i] = quiz_scores[i];
        cout << "New Quiz " << i << " Score: " << quiz_scores[i] << endl;
    }
};

void Student::setHwScores(const int hw_scores[3]) {
    for (int i = 0; i < 3; i ++) {
        this->hw_scores[i] = hw_scores[i];
        cout << "New Hw " << i << " Score: " << hw_scores[i] << endl;
    }
};

void Student::setFinalScore(const int final_score) {
    this->final_score = final_score;
    cout << "New Final Score: " << final_score << endl;
};

// method definitions
float Student::overallCourseScore(const int *weights) const {
    float quizAverage = this->getQuizAverage();
    float hwAverage = this->getHwAverage();
    return (quizAverage * ((float)*weights / 100)) + (hwAverage * ((float)*(weights+1) / 100)) + (this->final_score * ((float)*(weights+2) / 100));
};

void Student::getStudentInfo(const int *weights) const {
    cout << "Student ID: " << this->id << ", Name: " << this->name << ", Surname: " << this->surname << " Overall Score: " << this->overallCourseScore(weights) << endl;
};

void Student::showStudentInfo(const int *weights) const {
    this->getStudentInfo(weights);
    cout << " Quiz Scores:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << " - Quiz " << i+1 << ": " << this->quiz_scores[i] << endl;
    }
    cout << "Quiz Average: " << this->getQuizAverage() << endl;
    cout << " Hw Scores:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << " - Hw " << i+1 << ": " << this->hw_scores[i] << endl;
    }
    cout << "Hw Average: " << this->getHwAverage() << endl;
    cout << "Final Score: " << this->final_score << endl;
};

float Student::getQuizAverage(void) const {
    int total = 0;
    for (int i = 0; i < 4; i++) {
        total += this->quiz_scores[i];
    }
    return (float)total / 4;
};

float Student::getHwAverage(void) const {
    int total = 0;
    for (int i = 0; i < 3; i++) {
        total += this->quiz_scores[i];
    }
    return (float)total / 3;
};

