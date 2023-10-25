#ifndef PROJECT1_CODE_CLASS_H
#define PROJECT1_CODE_CLASS_H

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
class Class {
    private:
        std::set<Student> students;
        std::string classcode;
        std::string type;
        std::vector<Schedule> class_schedule;
    public:
        Class(std::string classcode);
        std::string getTurmaCode();
};


#endif