//
//
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "UC.h"
#include "Student.h"
#include <algorithm>

using namespace std;

void parse_file1(std::vector<UC>& uc_vector) {
    ifstream ucfile("classes_per_uc.csv");
    string line;
    getline(ucfile, line); // ler e ignorar a primeira linha

    while (getline(ucfile, line)) {
        string uccode, classcode;
        istringstream iss(line); // manipular a linha
        getline(iss, uccode, ','); // extrair uccode e ignorar a vírgula
        getline(iss, classcode); // extrair classcode
        bool existia = false;
        for (UC &uc: uc_vector) {
            if (uc.getcode() == uccode) {
                existia = true;
                Class t = Class(classcode);
                uc.add_class(t); // adicionar a uma UC existente uma Class
                break;
            }
        }
        if (!existia) {
            Class t = Class(classcode);
            uc_vector.push_back(UC(uccode, t)); // adicionar ao vetor de UCs uma UC nova
        }

    }
}

void parse_file2(std::vector<UC>& uc_vector) {
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

        for(UC &uc : uc_vector) {
            if(uc.getcode() == uccode) {
                std::vector<Class> cl = uc.getClasses();
                for (Class &classe : cl) {
                    if (classe.getTurmaCode() == classcode) {
                        Student stu = Student(scode, sname);
                        classe.add_student(stu);
                        break;
                    }
                }
                uc.setClasses(cl);
                break;
            }
        }
    }
}

void parse_file3(std::vector<UC>& uc_vector) {
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

        for(UC &uc : uc_vector) {
            if(uc.getcode() == uccode) {
                std::vector<Class> cl = uc.getClasses();
                for (Class &classe : cl) {
                    if (classe.getTurmaCode() == classcode) {
                        Schedule sch = Schedule(weekday,sth,du,type);
                        classe.add_Schedule(sch);
                        break;
                    }
                }
                uc.setClasses(cl);
                break;
            }
        }
    }
}
int main(){
    vector<UC> uc_vector;

    parse_file1(uc_vector);
    parse_file2(uc_vector);
    parse_file3(uc_vector);

    cout << "Número de UCs = " << uc_vector.size() << '\n';
    int count_sch = 0;
    int count_stu = 0;
    for (auto uc : uc_vector) {
        for (auto cl : uc.getClasses()) {
            cout << '\n' << uc.getcode() << ' ' << cl.getTurmaCode() << '\n'; // imprime o código da uc e da turma
            for (auto sch : cl.getSchedule()) {
                cout << sch.get_weekday() << ' ' << sch.get_starthour() << ' ' << // imprime o horário
                     sch.get_duration() << ' ' << sch.get_type() << '\n';
                count_sch++; // conta o número de horários
            }
            for (auto stu : cl.getStudents()) {
                cout << '\n' << stu.getID() << ' ' << stu.getName();
                count_stu++;
            }
            cout << '\n' << "///////////////////////";
        }
    }
    cout << '\n' << "Número de horários = " << count_sch << '\n';
    cout << "Número de estudantes = " << count_stu << endl;
    return 0;
}