    //
// Created by davidmg on 28-10-2023.
//

#ifndef PROJECT1_CODE_MENU_H
#define PROJECT1_CODE_MENU_H
#include "Student.h"
#include <iostream>
#include "Turma.h"
#include "Schedule.h"
#include "UC.h"
#include "Data.h"
using namespace std;

class Menu {
    public:
        Menu();
        void consultStudentSchedule(int ID);
        void consultClassSchedule(string classcode);
        void listAllUCs();
        void listAllStudents();
    private:
        Data d;
};


#endif //PROJECT1_CODE_MENU_H
