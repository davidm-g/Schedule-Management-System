//
// Created by afdom on 10/10/2023.
//

#include "Student.h"

Student::Student(std::string id, std::string name) {
    this->id = id;
    this->name = name;
}


std::string Student::getID() const {
    return this->id;
}
std::string Student::getName() const {
    return this->name;
}

map<pair<string,string>,Schedule> Student::getSchedule() const {
    return student_schedule;
}

void Student::addSchedule(Schedule sec,string uccode,string classcode) {
    pair<pair<string,string>,Schedule> x = make_pair(make_pair(uccode, classcode), sec);
    this->student_schedule.insert(x);
}

void Student::setSchedule(std::map<pair<string, string>, Schedule> s) {
    this->student_schedule = s;
}

bool Student::operator< (const Student s1) const{
    return this->id < s1.getID();
}

bool Student::operator== (const Student s1) const {
    return this->id == s1.getID() && this->name == s1.getName();
}