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

bool Turma::operator< (Turma t1) const {
    if (students.size() < t1.getStudents().size()) return true;
    else if (students.size() == t1.getStudents().size()) return classcode < t1.getTurmaCode();
    return false;
}
void Turma::setStudents(set<Student> students){
    this->students=students;
}