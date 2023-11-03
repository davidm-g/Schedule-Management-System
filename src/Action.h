//
// Created by davidmg on 02-11-2023.
//

#ifndef PROJECT1_CODE_ACTION_H
#define PROJECT1_CODE_ACTION_H

#include "Student.h"
#include <iostream>
#include "Turma.h"
#include "Schedule.h"
#include "UC.h"
#include <stack>
#include <algorithm>
#include <iomanip>
#include <queue>
using namespace std;
/**
 * @class Action
 * @brief Represents an undoable action (insertion,deletion, and switching of students from UCs and Classes)
 * made from the menu and retrieves its arguments.
 */
class Action {
private:
    string function;
    int id;
    string uccode, source, target;
public:
    Action(string function, int id, string uccode = "", string source= "", string target = "");
    int get_id();
    string getFunction();
    string getUcode();
    string getSource();
    string getTarget();
};
#endif //PROJECT1_CODE_ACTION_H
