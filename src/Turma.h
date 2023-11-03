#ifndef PROJECT1_CODE_TURMA_H
#define PROJECT1_CODE_TURMA_H

#include <string>
#include <vector>
#include <iostream>
#include "Student.h"
#include "Schedule.h"
#include <list>
#include <set>

/**
 * @class Turma
 * @brief
 * Categorizes a class using its unique identifier (class code) and provides
 * details about its schedule as well as a set of enrolled students.
 */
class Turma {
private:
    std::set<Student> students;
    std::string classcode;
    std::vector<Schedule> class_schedule;
public:
    Turma(std::string classcode);
    std::string getTurmaCode();
    void add_student(Student &s1);
    std::set<Student> getStudents();
    void setStudents(set<Student> students);
    void add_Schedule(Schedule sec);
    std::vector<Schedule> getSchedule();
    bool operator< (Turma t1) const;
};

#endif