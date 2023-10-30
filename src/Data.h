//
// Created by afdom on 10/10/2023.
//

#ifndef PROJECT1_CODE_DATA_H
#define PROJECT1_CODE_DATA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "UC.h"
#include "Student.h"
#include <algorithm>

class Data {
    private:
        vector<UC> uc_vector;
        set<Student> allstudents;
    public:
        Data();
        vector<UC> get_uc_vector();
        void set_uc_vector(vector<UC> uc_vector);
        set<Student> get_all_students();
        void parse_file1();
        void parse_file2();
        void parse_file3();
};


#endif //PROJECT1_CODE_DATA_H
