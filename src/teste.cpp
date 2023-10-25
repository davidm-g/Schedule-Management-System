//
// Created by afdom on 10/10/2023.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "UC.h"
using namespace std;
void parse_files(std::vector<UC>& uc_vector) {
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

    ifstream studentsfile("students_classes.csv");



    // ifstream classesfile("classes.csv");
}
int main(){
    vector<UC> uc_vector;
    parse_files(uc_vector);

    cout << uc_vector.size() << '\n';
    for(auto uc: uc_vector) {
        cout << uc.getcode() << '\n' << '\n';
        for (auto classe: uc.getClasses()) {
            cout << classe.getTurmaCode() << '\n';
        }
        cout << '\n' << '\n';
    }
    return 0;
}