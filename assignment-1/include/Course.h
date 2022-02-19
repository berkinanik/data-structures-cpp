#ifndef COURSE_H
#define COURSE_H
#include "Student.h"

class Course {
  private:
    Student students[10];
    int max_size = 10;
    int num = 0;
    int weights[3] = {30, 30, 40};

  public:
    // constructor declaration & definiton
    Course() {};

    // getter declarations
    int getNum(void) const {return num;};
    int* getWeights(void) {return weights;};

    // setter declarations
    void addNewStudent(Student new_student);
    void updateWeights(const int new_weights[3]);

    // method declaration
    void getStudentInfo(const int id) const;
    void calculateAverage(void) const;
    Student *findStudentById(const int id);
    void filterStudents(const int threshold, const int method) const;
};

#endif // COURSE_H
