//
//
//

#include "Class.h"

Class::Class(std::string classcode) {
    this->classcode = classcode;
    this->class_schedule = vector<Schedule>();
}
void Class::add_student(Student &s1){
    this->students.insert(s1);
}
std::string Class::getTurmaCode() {
    return this->classcode;
}

std::set<Student> Class::getStudents() {
    return this->students;
}
void Class::add_Schedule(Schedule sec){
    this->class_schedule.push_back(sec);
}
std::vector<Schedule> Class::getSchedule() {
    return this->class_schedule;
}