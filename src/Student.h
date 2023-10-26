#ifndef PROJECT1_CODE_STUDENT_H
#define PROJECT1_CODE_STUDENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Schedule.h"

class Student {
    private:
        std::string id;
        std::string name;
        std::vector<Schedule> student_schedule;
    public:
        //Student();
        Student(std::string id, std::string name);
        std::string getName();
        std::string getID() const;
        Schedule getSchedule(int id);
        void setSchedule(std::string uc_code, std::string classcode);
        bool operator< (const Student& s1) const;
};


#endif //PROJECT1_CODE_STUDENT_H
