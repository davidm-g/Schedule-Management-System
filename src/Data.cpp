//
// Created by afdom on 10/10/2023.
//

#include "Data.h"


Data::Data() {
    this->allstudents = set<Student>();
    this->record = stack<Action>();

}

void Data::addAction(Action a) {
    record.push(a);
}
void Data::set_record(stack<Action> record){
    this->record = record;
}

stack<Action> Data::get_record() {
    return this->record;
}

set<Student> Data::get_all_students(){
    return this->allstudents;
}
void Data::set_uc_map(map<string,UC> uc_map) {
    this->uc_map = uc_map;
}
void Data::parse_file1() {
    ifstream ucfile("classes_per_uc.csv");
    string line;
    getline(ucfile, line); // ler e ignorar a primeira linha

    while (getline(ucfile, line)) {
        string uccode, classcode;
        istringstream iss(line); // manipular a linha
        getline(iss, uccode, ','); // extrair uccode e ignorar a vírgula
        getline(iss, classcode); // extrair classcode
        auto it = uc_map.find(uccode);
        if(it != uc_map.end()){
            Turma t = Turma(classcode);
            it->second.add_class(t);
        }
        else{
            Turma t = Turma(classcode);
            UC uc = UC(uccode,t);
            this->uc_map.insert(make_pair(uccode,uc));
        }
    }
}

void Data::parse_file2() {
    set<int> temp_scode;
    ifstream stufile("students_classes.csv");
    string line;
    getline(stufile, line); // ler e ignorar a primeira linha
    while (getline(stufile, line)) {
        string scode, sname, uccode, classcode;
        istringstream iss(line);
        getline(iss, scode, ','); // extrair scode e ignorar a vírgula
        getline(iss, sname, ','); // extrair sname e ignorar a vírgula
        getline(iss, uccode, ','); // extrair uccode e ignorar a vírgula
        getline(iss, classcode); // extrair classcode e ignorar a vírgula
        int sid = stoi(scode);
        auto it = uc_map.find(uccode);
        std::vector<Turma> cl1 = it->second.getClasses();
        for (auto &turma: cl1) {
            if (turma.getTurmaCode() == classcode) {
                if (temp_scode.find(sid) == temp_scode.end()) {
                    Student stu = Student(sid, sname);
                    this->allstudents.insert(stu);
                    turma.add_student(stu);
                }
                else {
                    for (auto s: this->allstudents) {
                        if (s.getID() == sid) turma.add_student(s);
                    }
                }
            }
        }
        it->second.setClasses(cl1);
    }
}

void Data::parse_file3() {
    ifstream clfile("classes.csv");
    string line;
    getline(clfile, line);
    while (getline(clfile, line)){
        string classcode,uccode,weekday,duration,starthour,type;
        istringstream iss(line);
        getline(iss, classcode, ','); // extrair classcode e ignorar a vírgula
        getline(iss, uccode, ','); // extrair uccode e ignorar a vírgula
        getline(iss, weekday, ','); // extrair weekday e ignorar a vírgula
        getline(iss, starthour, ','); // extrair starthour e ignorar a vírgula
        getline(iss, duration, ','); // extrair duration e ignorar a vírgula
        getline(iss, type); // extrair type
        float du = stof(duration);
        float sth = stof(starthour);
        auto it = this->uc_map.find(uccode);
        std::vector<Turma> cl1 = it->second.getClasses();
        for(auto &turma : cl1){
            if (turma.getTurmaCode() == classcode) {
                Schedule sch = Schedule(weekday,sth,du,type,uccode,classcode);
                turma.add_Schedule(sch);
            }
        }
        it->second.setClasses(cl1);
    }
}

map<string,UC> Data::get_uc_map(){
    return this->uc_map;
}
