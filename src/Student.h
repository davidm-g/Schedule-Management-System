#ifndef PROJECT1_CODE_STUDENT_H
#define PROJECT1_CODE_STUDENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Schedule.h"
#include <map>

/**
 * @class Student
 * @brief Portrays a student, identifying him by ID and name.
 */
class Student {
private:
    int id;
    std::string name;
public:
    Student(int id, std::string name = "");
    int getID() const;
    std::string getName() const;
    bool operator< (const Student s1) const;
    bool operator== (const Student s1) const;
};


#endif //PROJECT1_CODE_STUDENT_H
