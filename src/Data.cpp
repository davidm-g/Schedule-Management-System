//
// Created by afdom on 10/10/2023.
//

#include "Data.h"

Data::Data() {
    this->uc_vector = vector<UC>();
    this->allstudents = set<Student>();
}

vector<UC> Data::get_uc_vector() {
    return this->uc_vector;
}
set<Student> Data::get_all_students(){
    return this->allstudents;
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
        bool existia = false;
        for (UC &uc: this->uc_vector) {
            if (uc.getcode() == uccode) {
                existia = true;
                Turma t = Turma(classcode);
                uc.add_class(t); // adicionar a uma UC existente uma Turma
                break;
            }
        }
        if (!existia) {
            Turma t = Turma(classcode);
            this->uc_vector.push_back(UC(uccode, t)); // adicionar ao vetor de UCs uma UC nova
        }

    }
}

void Data::parse_file2() {
    set<int> temp_scode;
    ifstream stufile("students_classes.csv");
    string line;
    getline(stufile, line); // ler e ignorar a primeira linha
    while(getline(stufile,line)){
        string scode,sname, uccode, classcode;
        istringstream iss(line);
        getline(iss, scode, ','); // extrair scode e ignorar a vírgula
        getline(iss, sname, ','); // extrair sname e ignorar a vírgula
        getline(iss, uccode, ','); // extrair uccode e ignorar a vírgula
        getline(iss, classcode); // extrair classcode e ignorar a vírgula
        int sid = stoi(scode);
        for(UC &uc : this->uc_vector) {
            if(uc.getcode() == uccode) {
                std::vector<Turma> cl = uc.getClasses();
                for (Turma &classe : cl) {
                    if (classe.getTurmaCode() == classcode) {
                        if(temp_scode.find(sid) == temp_scode.end()){
                            Student stu = Student(sid,sname);
                            this->allstudents.insert(stu);
                            classe.add_student(stu);
                            break;
                        }
                        else{
                            for(auto s: this->allstudents){
                                if(s.getID() == sid) classe.add_student(s);
                            }
                        }
                        break;

                    }
                }
                uc.setClasses(cl);
                break;
            }
        }
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

        for(UC &uc : this->uc_vector) {
            if(uc.getcode() == uccode) {
                std::vector<Turma> cl = uc.getClasses();
                for (Turma &classe : cl) {
                    if (classe.getTurmaCode() == classcode) {
                        Schedule sch = Schedule(weekday,sth,du,type,uccode,classcode);
                        classe.add_Schedule(sch);
                    }
                }
                uc.setClasses(cl);
                break;
            }
        }
    }
}
