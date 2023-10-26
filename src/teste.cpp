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
vector<UC> parse_file1() {
    vector<UC> uc_vector;
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
    ucfile.close();
    return uc_vector;
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
vector<UC> parse_file3() {
    vector<UC> uc_vector = parse_file1();
    ifstream inputFile("classes.csv");
    string line;
    getline(inputFile, line);


    // extrair type e ignorar a vírgula


        while (getline(inputFile, line)) {
            istringstream iss(line);
            string classCode, ucCode, weekday, startHour, duration, type;
            getline(iss, classCode, ',');
            getline(iss, ucCode, ',');
            getline(iss, weekday, ',');
            getline(iss, startHour, ',');
            getline(iss, duration, ',');
            getline(iss, type);


            Schedule schedule(weekday, stof(startHour), stof(duration), type); // Create a Schedule object

            // Create a Class object and add the Schedule

            // Find the appropriate UC or create a new one

            for (UC& u : uc_vector) {
                if (u.getcode() == ucCode) {
                    for(Class& c : u.getClasses()){
                        if(c.getTurmaCode() == classCode) {
                            c.add_Schedule(schedule);
                            break;
                        }
                    }
                    break;

                }
            }




            // Add the Class object to the UC

        }

        inputFile.close();



    return uc_vector;
}
int main(){

    parse_file3();
    return 0;
}