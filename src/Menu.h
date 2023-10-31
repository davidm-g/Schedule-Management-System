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
#include <stack>
#include <algorithm>
#include <iomanip>
#include <queue>
using namespace std;

class Menu {
    public:
        Menu();
        list<Schedule> consultStudentSchedule(int ID);
        list<Schedule> consultClassSchedule(string classcode);
        void listStudentsbyClass(string classcode1);
        void listStudentsbyYear(char number);
        void listAllUCs();
        void listAllStudents();
        void listStudentsbyUC(string uce);
        void maxUCs();
        void addUC(int ID, string uc);
        void removeUC(int ID, string uc1);
        bool checkMaxUC (int id);
        bool compatibleSchedules (list<Schedule> current, vector<Schedule> novo);
        void switchUC (int id, string uc1, string uc2);
private:
        Data d;
};


#endif //PROJECT1_CODE_MENU_H
