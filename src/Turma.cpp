//
//
//

#include "Turma.h"
#include "Student.h"

Turma::Turma(std::string classcode) {
    this->classcode = classcode;
    this->class_schedule = vector<Schedule>();
}
void Turma::add_student(Student &s1){
    this->students.insert(s1);
    //
}
std::string Turma::getTurmaCode() {
    return this->classcode;
}

std::set<Student> Turma::getStudents() {
    return this->students;
}

void Turma::add_Schedule(Schedule sec){
    this->class_schedule.push_back(sec);
}

std::vector<Schedule> Turma::getSchedule() {
    return this->class_schedule;
}