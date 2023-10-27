//
// Created by afdom on 10/10/2023.
//

#include "Student.h"

Student::Student(std::string id, std::string name) {
    this->id = id;
    this->name = name;
}

std::string Student::getName(){
    return this->name;
}
std::string Student::getID() const {
    return this->id;
}
std::string Student::getName() const {
    return this->name;
}

map<pair<string,string>,Schedule> Student::getSchedule() {
    return student_schedule;
}
/*
void Student::addStudentSchedule(string uc_code, std::string classcode, Schedule sec) const {
    pair<string,string> temp = {uc_code,classcode};
    this->student_schedule.insert(pair<pair<string,string>,Schedule>(temp,sec));
}
 */
bool Student::operator< (const Student s1) const{
    return this->id < s1.getID();
}

bool Student::operator== (const Student s1) const {
    return this->id == s1.getID() && this->name == s1.getName();
}