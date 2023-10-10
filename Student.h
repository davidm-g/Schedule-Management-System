#ifndef PROJECT1_CODE_STUDENT_H
#define PROJECT1_CODE_STUDENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Schedule.h"

class Student {
    private:
        int id;
        std::string name;
        std::vector<Schedule> student_schedule;
    public:
        //Student();
        Student(int id, std::string name);
        std::string getName();
        int getID();
        Schedule getSchedule(int id);
        void setSchedule(std::string uc_code, std::string classcode);
};


#endif //PROJECT1_CODE_STUDENT_H
