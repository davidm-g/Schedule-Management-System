//
// Created by afdom on 10/10/2023.
//

#include "Class.h"
Class::Class() {
    this->classcode= "";
    this->class_schedule = vector<Schedule>();
    this->students = set<Student>();
}
Class::Class(std::string classcode) {
    this->classcode = classcode;
    this->class_schedule = vector<Schedule>();
    this->students = set<Student>();
}
void Class::add_student(Student &s1){
    this->students.insert(s1);
}
std::string Class::getTurmaCode() const{
    return this->classcode;
}

std::set<Student> Class::getStudents() {
    return this->students;
}
void Class::add_Schedule(Schedule sch){
    class_schedule.push_back(sch);
}
std::vector<Schedule>& Class::getSchedule() {
    return this->class_schedule;
}