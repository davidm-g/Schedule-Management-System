//
// Created by afdom on 10/10/2023.
//

#include "Student.h"

Student::Student(int id, std::string name) {
    this->id = id;
    this->name = name;
}


int Student::getID() const {
    return this->id;
}
std::string Student::getName() const {
    return this->name;
}

bool Student::operator< (const Student s1) const{
    return this->id < s1.getID();
}

bool Student::operator== (const Student s1) const {
    return this->id == s1.getID() && this->name == s1.getName();
}