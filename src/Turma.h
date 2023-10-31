#ifndef PROJECT1_CODE_TURMA_H
#define PROJECT1_CODE_TURMA_H

#include <string>
#include <vector>
#include <iostream>
#include "Student.h"
#include "Schedule.h"
#include <list>
#include <set>

// Conceptually, a class is identified by the code of the UC, weekday, start time, duration, and type (T/TP/PL).
// A schedule is composed by several classes. A student is identified by a name, and has an associated
// schedule. A class is identified by a code and has a given schedule.
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