//
// Created by afdom on 10/10/2023.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "UC.h"
#include "Student.h"
#include <algorithm>

using namespace std;
/* bool compareByUccode( UC& uc, const std::string& uccode) {
    return uc.getcode() < uccode;
}
 */
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
/*
>>>>NÃO ESTÁ A FUNCIONAR<<<<
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
               for (Class &classe : uc.getClasses()) {
                    if (classe.getTurmaCode() == classcode) {
                        Student s1 = Student(scode, sname);
                        classe.add_student(s1);
                        break;
                    }
                }
                break;
            }
        }
        //uc_code[uccode][classcode]

        //auto it= lower_bound(uc_vector.begin(),uc_vector.end(),uccode,compareByUccode);

    }
}
    */
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
        getline(iss, type); // extrair type e ignorar a vírgula
        float du = stof(duration);
        float sth = stof(starthour);
        int p1 = 0;
        int p2 = 0;
        for(int i = 0; i < uc_vector.size();i++) {
            if(uc_vector[i].getcode() == uccode){
                p1 = i;
                break;
            }
        }
        for(int i = 0; i < uc_vector[p1].getClasses().size();i++) {
            if (uc_vector[p1].getClasses()[i].getTurmaCode() == classcode){
                p2 = i;
                break;
            }

        }
        uc_vector[p1].getClasses()[p2].getSchedule().push_back(Schedule(weekday,sth,du,type));
        /*
        for(UC &uc : uc_vector) {
            if(uc.getcode() == uccode) {
                for (Class &classe : uc.getClasses()) {
                    if (classe.getTurmaCode() == classcode) {
                        Schedule sch = Schedule(weekday,sth,du,type);
                        classe.add_Schedule(sch);
                        break;
                    }
                }
            }
        }
         */
    }

}
int main(){
    vector<UC> uc_vector;

    parse_file1(uc_vector);
    //parse_file2(uc_vector);
    parse_file3(uc_vector);

    cout << uc_vector.size() << '\n';

    for(auto s : uc_vector[0].getClasses()[0].getSchedule()) {
        cout << uc_vector[0].getcode() << ' ' << uc_vector[0].getClasses()[0].getTurmaCode() << '\n';
        cout << s.get_weekday() << ' ' << s.get_starthour() << s.get_duration() << s.get_type() << '\n';
    }
    return 0;
}