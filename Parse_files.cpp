//
// Created by afdom on 10/10/2023.
//
#include <iostream>
#include <fstream>
#include <sstream>

#include "Class.h"
#include "Schedule.h"
#include "Student.h"
#include "UC.h"

std::vector<UC> uc_vector;

using namespace std;
void parse_files(){

    //cagalhao do afonso fds
    ifstream ucfile("classes_per_uc.csv");
    string line;
    getline(ucfile,line);
    while(getline(ucfile,line)){
        string uccode;
        string classcode;
        istringstream iss(line);
        getline(iss, uccode, ',');
        getline(iss, classcode);
        bool existia = false;
        for(UC uc : uc_vector) {
            if (uc.getcode() == uccode) {
                existia = true;
                uc.add_class(classcode);
                break;
            }
        }
        if (!existia) {
            uc_vector.push_back(UC(uccode,Class(classcode)));
        }


    }


    ifstream studentsfile("students_classes.csv");



    ifstream classesfile("classes.csv");








}


