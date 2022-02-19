#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class Student {
  private:
    int id;
    string name, surname;
    int quiz_scores[4] = {0, 0, 0, 0};
    int hw_scores[3] = {0, 0, 0};
    int final_score = 0;

  public:
    // constructor declaration
    Student() {};
    Student(const int id, const string name, const string surname) : id(id), name(name), surname(surname) {};
    Student(const int id, const string name, const string surname, const int quiz_scores[4], const int hw_scores[3], const int final_score);

    // getter declarations & definitions
    int getId(void) const {return id;};
    string getName(void) const {return name;};
    string getSurname(void) const {return surname;};
    int* getQuizScores(void) {return quiz_scores;};
    int* getHwScores(void) {return hw_scores;};
    int getFinalScore(void) const {return final_score;};

    // setter declarations
    void setId(const int id);
    void setName(const string name);
    void setSurname(const string surname);
    void setQuizScores(const int quiz_scores[4]);
    void setHwScores(const int hw_scores[3]);
    void setFinalScore(int final_score);

    // method declarations
    float overallCourseScore(const int *weights) const;
    void  getStudentInfo(const int *weights) const;
    void showStudentInfo(const int *weights) const;
    float getQuizAverage(void) const;
    float getHwAverage(void) const;
};

#endif // STUDENT_H
