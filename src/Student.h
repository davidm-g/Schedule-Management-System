#ifndef PROJECT1_CODE_STUDENT_H
#define PROJECT1_CODE_STUDENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Schedule.h"
#include <map>


class Student {
private:
    int id;
    std::string name;
    //std::vector<Schedule> student_schedule;
public:
    //Student();
    Student(int id, std::string name);
    int getID() const;
    std::string getName() const;
    std::map<pair<string, string>, Schedule> getSchedule() const;
    void addSchedule(Schedule sec,string uccode,string classcode);
    void setSchedule(std::map<pair<string, string>, Schedule> s);
    bool operator< (const Student s1) const;
    bool operator== (const Student s1) const;
};


#endif //PROJECT1_CODE_STUDENT_H
