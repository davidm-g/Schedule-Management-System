#ifndef PROJECT1_CODE_STUDENT_H
#define PROJECT1_CODE_STUDENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Schedule.h"
#include <map>


class Student {
private:
    std::string id;
    std::string name;
    //std::vector<Schedule> student_schedule;
    std::map<pair<string, string>, Schedule> student_schedule;
public:
    //Student();
    Student(std::string id, std::string name);
    std::string getName();
    std::string getID() const;
    std::string getName() const;
    map<pair<string, string>, Schedule> getSchedule();
    void addStudentSchedule(string uc_code, std::string classcode, Schedule sec) const;
    bool operator< (const Student s1) const;
    bool operator== (const Student s1) const;
};


#endif //PROJECT1_CODE_STUDENT_H
