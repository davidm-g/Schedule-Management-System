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

bool Student::operator< (const Student& s1) const{
    return this->id < s1.getID();
}
