#include <iostream>
#include <string>
#include "Student.h"
#include "Course.h"

using namespace std;

Course course;

void addNewStudent(const int ID, const string name, const string surname) {
    if (ID < 0 || name.empty() || surname.empty()) {
        cout << "Invalid student credentials" << endl;
        return;
    }
    cout << "Adding student..." << endl;
    course.addNewStudent(Student(ID, name, surname));
};

void addNewStudent(const int ID, const string name, const string surname, const int quiz_scores[4], const int hw_scores[3], const int final_score) {
    if (ID < 0 || name.empty() || surname.empty()) {
        cout << "Invalid student credentials" << endl;
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (quiz_scores[i] < 0 || quiz_scores[i] > 100) {
            cout << "Invalid quiz score" << endl;
            return;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (hw_scores[i] < 0 || hw_scores[i] > 100) {
            cout << "Invalid hw score" << endl;
            return;
        }
    }
    if (final_score < 0 || final_score > 100) {
        cout << "Invalid final score" << endl;
        return;
    }
    cout << "Adding student..." << endl;
    course.addNewStudent(Student(ID, name, surname, quiz_scores, hw_scores, final_score));
};

void showStudent(const int ID) {
    if (ID < 0) {
        cout << "Invalid student id" << endl;
        return;
    }
    cout << "Looking for student..." << endl;
    const int *weights = course.getWeights();
    Student *student = course.findStudentById(ID);
    if (student) {
        course.findStudentById(ID)->showStudentInfo(weights);
        return;
    } else {
        cout << "Could not find student with id: " << ID << endl;
    }
};

void changeStudentScores(const int ID, const int quiz_scores[4], const int hw_scores[3], const int final_score) {
    for (int i = 0; i < 4; i++) {
        if (quiz_scores[i] < 0 || quiz_scores[i] > 100) {
            cout << "Invalid quiz score" << endl;
            return;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (hw_scores[i] < 0 || hw_scores[i] > 100) {
            cout << "Invalid hw score" << endl;
            return;
        }
    }
    if (final_score < 0 || final_score > 100) {
        cout << "Invalid final score" << endl;
        return;
    }
    cout << "Updating student scores..." << endl;
    Student *student = course.findStudentById(ID);
    if (student) {
        student->setQuizScores(quiz_scores);
        student->setHwScores(hw_scores);
        student->setFinalScore(final_score);
        return;
    }
}

void changeWeights(const int weightQ, const int weightHW, const int weightF) {
    if (weightQ + weightHW + weightF != 100 || weightQ < 0
            || weightQ > 100 || weightHW < 0 || weightHW > 100
            || weightF < 0 || weightF > 100) {
        cout << "Invalid weight(s)..." << endl;
        return;
    }
    const int weights[] = {weightQ, weightHW, weightF};
    cout << "Updating weights..." << endl;
    course.updateWeights(weights);
};

void showAverage() {
    cout << "Showing classroom averages..." << endl;
    course.calculateAverage();
};

void showAbove(const int threshold) {
    if (threshold < 0 || threshold > 100) {
        cout << "Invalid threshold" << endl;
        return;
    }
    cout << "Showing students above " << threshold << " overall score..." << endl;
    course.filterStudents(threshold, 1);
};

void showBelow(const int threshold) {
    if (threshold < 0 || threshold > 100) {
        cout << "Invalid threshold" << endl;
        return;
    }
    cout << "Showing students below " << threshold << " overall score..." << endl;
    course.filterStudents(threshold, 0);
};

//void tests(void) {
//    const int quiz_invalid[] = {101, 10, 10, 10};
//    const int hw_invalid[] = {-5, 10, 10};
//    addNewStudent(2222222, "Berkin", "Anik");
//    const int quiz_scores1[] = {75, 100, 100, 100};
//    const int hw_scores1[] = {100, 15, 100};
//    changeStudentScores(2222222, quiz_invalid, hw_scores1, 100);
//    changeStudentScores(2222222, quiz_scores1, hw_invalid, 100);
//    changeStudentScores(2222222, quiz_scores1, hw_scores1, -5);
//    changeStudentScores(2222222, quiz_scores1, hw_scores1, 100);
//    cout << endl;
//    addNewStudent(2222222, "Berkin", "Anik2");
//    const int quiz_scores2[] = {50, 100, 100, 50};
//    const int hw_scores2[] = {40, 50, 10};
//    changeStudentScores(2222222, quiz_scores2, hw_scores2, 20);
//    cout << endl;
//    addNewStudent(3333333, "Berkin", "Anik3");
//    const int quiz_scores3[] = {80, 50, 80, 90};
//    const int hw_scores3[] = {80, 100, 80};
//    changeStudentScores(3333333, quiz_scores3, hw_scores3, 90);
//    cout << endl;
//    showStudent(2222222);
//    cout << endl;
//    showStudent(2222222);
//    cout << endl;
//    showStudent(3333333);
//    cout << endl;
//    showAverage();
//    cout << endl;
//    changeWeights(20, 20, 50);
//    changeWeights(20, 20, 100);
//    changeWeights(10, 10, 90);
//    cout << endl;
//    showAverage();
//    cout << endl;
//    showAbove(75);
//    cout << endl;
//    showBelow(75);
//    cout << endl;
//    addNewStudent(2222222, "berkin", "anik2");
//    cout << endl;
//    addNewStudent(-1561, "berkin", "anik2");
//    cout << endl;
//    addNewStudent(-1561, "", "anik2");
//    cout << endl;
//    showStudent(-1561);
//    const int quiz_scores4[] = {12, 12, 50, 100};
//    cout << endl;
//    const int hw_scores4[] = {48, 76, 56};
//    addNewStudent(4444444, "berkin", "anik4", quiz_scores4, hw_scores4, 67);
//    cout << endl;
//    showStudent(4444444);
//    cout << endl;
//    showAverage();
//    cout << endl;
//    showBelow(90);
//    cout << endl;
//    showAbove(70);
//}

int main() {
    while (true) {
        int input;
        cout << "\nChoose your option:" << endl;
        cout << "1) Add a student\n2) Search a student by ID\n3) Change a student's score\n4) Update weights\n";
        cout << "5) Show class average\n6) Show students with overall score above a threshold\n";
        cout << "7) Show students with overall score below a threshold\n8) Exit\n" << endl;
        cout << "Enter your option: ";
        cin >> input;
        cout << endl;
        switch (input) {
        case 1: {
            int id;
            string name;
            string surname;
            cout << "Enter student ID: ";
            cin >> id;
            cout << "Enter student name: ";
            cin >> name;
            cout << "Enter student surname: ";
            cin >> surname;
            cout << endl;
            addNewStudent(id, name, surname);
            break;
        }
        case 2: {
            int id;
            cout << "Enter student ID: ";
            cin >> id;
            showStudent(id);
            break;
        }
        case 3: {
            int id;
            int quiz_scores[4];
            int hw_scores[3];
            int final_score;
            cout << "Enter student ID: ";
            cin >> id;
            Student *student = course.findStudentById(id);
            if (!student) {
                cout << "Could not find student with id: " << id << endl;
                break;
            }
            for (int i = 0; i < 4; i++) {
                cout << "Enter quiz score " << i + 1 << ": ";
                cin >> quiz_scores[i];
            }
            for (int i = 0; i < 3; i++) {
                cout << "Enter hw score " << i + 1 << ": ";
                cin >> hw_scores[i];
            }
            cout << "Enter final score: ";
            cin >> final_score;
            changeStudentScores(id, quiz_scores, hw_scores, final_score);
            break;
        }
        case 4: {
            int weights[3];
            cout << "Enter new quiz weight: ";
            cin >> weights[0];
            cout << "Enter new hw weight: ";
            cin >> weights[1];
            cout << "Enter new final weight: ";
            cin >> weights[2];
            changeWeights(weights[0], weights[1], weights[2]);
            break;
        }
        case 5: {
            showAverage();
            break;
        }
        case 6: {
            int threshold;
            cout << "Enter threshold: ";
            cin >> threshold;
            showAbove(threshold);
            break;
        }
        case 7: {
            int threshold;
            cout << "Enter threshold: ";
            cin >> threshold;
            showBelow(threshold);
            break;
        }
        case 8:
            cout << "Exiting application..." << endl;
            return 0;
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
    }
//    tests();
}
