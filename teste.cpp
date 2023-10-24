//
// Created by afdom on 10/10/2023.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "UC.h"
using namespace std;
void parse_files(std::vector<UC>& uc_vector) {

    ifstream ucfile("classes_per_uc.csv"); // abrir o ficheiro
    if (!ucfile.is_open()) {
        cout << "Error: Unable to open the file." << '\n';
    }
    string line;
    getline(ucfile, line); // ler e ignorar a primeira linha

    while (getline(ucfile, line)) {
        string uccode, classcode, virgula;
        istringstream iss(line); // manipular a linha
        getline(iss, uccode, ','); // extrair uccode e ignorar a vírgula
        getline(iss, classcode); // extrair classcode
        bool existia = false;
        for (UC uc: uc_vector) {
            if (uc.getcode() == uccode) {
                existia = true;
                uc.add_class(classcode); // adicionar a uma UC existente uma Class
                break;
            }
        }
        if (!existia) {
            uc_vector.push_back(UC(uccode, Class(classcode))); // adicionar ao vetor de UCs uma UC nova
        }


    }


    // ifstream studentsfile("students_classes.csv");


    // ifstream classesfile("classes.csv");
}
int main(){
    std::vector<UC> uc_vector;
    parse_files(uc_vector);
    cout << uc_vector.size();
    for(auto uc : uc_vector) cout << uc.getcode();
    return 0;
}