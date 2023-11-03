//
//
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
#include <queue>
using namespace std;
/**
 * @class Menu
 * @brief Represents the user-friendly interface for the schedule management system.
 * It shows available functionalities and their corresponding outputs in a clear, organized,
 * and logical manner, facilitating seamless program utilization and straightforward result
 * interpretation.
 */
class Menu {
    public:
        Menu();
        void add_Action(Action a);
        void undo();
        bool canBeAddedBack(int id, string uccode, string classcode);
        list<Schedule> consultStudentSchedule(int ID);
        list<Schedule> consultClassSchedule(string classcode);
        list<Schedule> consultUCSchedule(string uccode);
        set<Student> listStudentsbyClass(string classcode1);
        void listStudentsbyYear(char number);
        void listAllUCs();
        void listAllStudents();
        void listStudentsbyUC(string uc);
        void maxUCs();
        bool addUC(int ID, string uc);
        string removeUC(int ID, string uc1);
        bool checkMaxUC (int id);
        bool compatibleSchedules (list<Schedule> current, vector<Schedule> novo);
        bool canaddUC (int id, string source_uc, string target_uc);
        string ConsultClassbyUC(int id, string uc);
        bool canaddClass(int id, string target_class, string uc);
        void removeClass(int id, string uc, string classcode);
        queue<string> getLog();
private:
        Data d;
        queue<string> log;
};


#endif //PROJECT1_CODE_MENU_H
