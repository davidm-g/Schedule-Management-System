//
// Created by davidmg on 28-10-2023.
//

#include "Menu.h"
#include <algorithm>
#include <iomanip>
#include <queue>

list<Schedule> Menu::consultStudentSchedule(int ID){
    cout << '\n';
    std::vector<UC> temp = d.get_uc_vector();
    list<Schedule> v;

    for(UC uc: temp){
        for(Turma turma : uc.getClasses()){
            for(Student stu : turma.getStudents()){
                if(ID == stu.getID()){
                    for(Schedule sche : turma.getSchedule()){
                        v.push_back(sche);
                    }
                }
            }
        }
    }
    if(v.empty())
        cout << "Please enter a valid student id with 9 digits" << '\n';
    v.sort();
    return v;
}
list<Schedule> Menu::consultClassSchedule(string classcode){
    cout << '\n';
    std::vector<UC> temp = d.get_uc_vector();
    list<Schedule> v;
    for(UC uc: temp) {
        for (Turma turma: uc.getClasses()) {
            if (turma.getTurmaCode() == classcode) {
                for (Schedule sche: turma.getSchedule()) v.push_back(sche);
            }
        }
    }
    if(v.empty())
        cout << "Please enter a valid class code in the format (XLEICXX)" << '\n';
    v.sort();
    return v;


}
void Menu::listStudentsbyClass(std::string classcode1) {
   cout << '\n';
   vector<UC> temp = d.get_uc_vector();
   set<Student> s;
   for(UC uc : temp){
       for(Turma turma: uc.getClasses()){
           if(turma.getTurmaCode() == classcode1){
               for(auto stu : turma.getStudents()){
                   s.insert(stu);
               }
           }
       }
   }
   if(s.empty())
       cout << "Please enter a valid class code in the format (XLEICXX)" << '\n';
   for (auto stu : s)
       cout << stu.getID() << ' ' << stu.getName() << '\n';
   cout << "Number of students on class " << classcode1 << " = " << s.size() << '\n';
}
void Menu::listStudentsbyYear(char number){
    cout << '\n';
    set<Student> s;
    for (UC uc : d.get_uc_vector()) {
        for(auto turma : uc.getClasses()){
            if (turma.getTurmaCode()[0] == number) {
                for (auto stu : turma.getStudents()) {
                    s.insert(stu);
                }
            }
        }
    }
    if(s.empty()) cout << "Please enter a valid student year in the interval [1, 3]" << '\n';
    else {
        cout << "Students enrolled in the year " << number << " :\n";
        for (Student stu : s) {
            cout << stu.getID() << ' ' << stu.getName() << '\n';
        }
    }
    cout << "Ocuupation of year " << number << " = " << s.size() << '\n';
}

void Menu::listStudentsbyUC(string uce){
    cout << '\n';
    vector<UC> temp = d.get_uc_vector();
    list<Student> l;
    for(UC uc : temp) {
        if(uc.getcode() == uce){
            for(Turma turma : uc.getClasses()){
                cout << turma.getTurmaCode() << '\n';
                for (auto stu: turma.getStudents())
                    l.push_back(stu);


            }
            break;
        }
    }

    l.sort();
    if (l.empty()) cout << "Please enter a valid UC code in the format (L.EICXXX)" << '\n';
    for(auto stu1: l){
        cout << stu1.getID() << ' ' << stu1.getName() << '\n';
    }

}
void Menu::listAllUCs() {
    for(auto uc: d.get_uc_vector()){
        cout << uc.getcode() << '\n';
    }
}

void Menu::listAllStudents() {
    for (Student stu : d.get_all_students()) {
        cout << stu.getID() << ' ' << stu.getName() << '\n';
    }
}

void Menu::maxUCs() {
    stack<UC> ucs;
    stack<int> max_occup;

    for(UC uc : d.get_uc_vector()) {
        int count = 0;
        for(auto turma: uc.getClasses()){
            for(auto stu: turma.getStudents()) count++;
        }
        if(ucs.empty()){
            ucs.push(uc);
            max_occup.push(count);
        }
        else {
            if(max_occup.top() <= count){
                ucs.push(uc);
                max_occup.push(count);
            }
        }
    }
    int temp = max_occup.top();
    cout << "The UC(s) with more occupation is/are: ";
    while(max_occup.top() == temp){
        cout << ucs.top().getcode() << " | ";
        max_occup.pop();
        ucs.pop();
    }
    cout << "With " << temp << " students" << endl;
}
void Menu::addUC(int ID,string name, string uc) {
    list<Schedule> current = consultStudentSchedule(ID);
    vector<UC> temp = d.get_uc_vector();
    bool exists = false;
    for(auto stu: d.get_all_students()){
        if(stu.getID() == ID){
            exists = true;
            break;
        }
    }
    if (exists) {
       if(checkMaxUC(ID)) cout << "This student can not be added to more UCs";
       else { // This student can be added to more UCs
            for(auto uc1 : temp) {
                if(uc1.getcode() == uc) { // The UC we want to add the student to
                    bool flag = true;
                    while(flag) {
                        string classicode = min_class(uc);
                        for (auto turma: uc1.getClasses()) {
                            if (turma.getTurmaCode() == classicode) {
                                if(compatibleSchedules(current,turma.getSchedule())){
                                    Student stu = Student(ID,name);
                                    turma.add_student(stu);
                                    flag = false;
                                }
                            }
                        }
                    }
                }
            }
            d.set_uc_vector(temp);
       }
    }
    else {
        cout << "The given student does not exist." << '\n';
    }
}


bool Menu::checkMaxUC (int id) {
    int c = 0;
    for (auto uc : d.get_uc_vector()) {
        for(auto turma : uc.getClasses()){
            for(auto stu : turma.getStudents()) {
                if (stu.getID() == id) {
                    c++;
                    break;
                }
            }
        }
    }
    if (c >= 7) return true;
    else if (c < 6) return false;
}

bool Menu::compatibleSchedules(list<Schedule> current, vector<Schedule> novo) {

    for(auto sche: novo) {
        for(auto sche1 : current) {
            if (sche1.get_endhour() > sche.get_starthour() &&
                sche1.get_starthour() < sche.get_endhour()){
                if(sche1.get_type() == "T" || sche.get_type() == "T") return true;
                else return false;
            }
        }
    }
    return true;
}

string Menu::min_class(string uccode) {
    stack<Turma> classes;
    stack<int> min_occup;

    for(UC uc : d.get_uc_vector()) {
        if(uc.getcode() == uccode) {
            for (auto turma: uc.getClasses()) {
                int count = 0;
                for (auto stu: turma.getStudents()) count++;
                if (classes.empty()) {
                    classes.push(turma);
                    min_occup.push(count);
                }
                else {
                    if (min_occup.top() >= count) {
                        classes.push(turma);
                        min_occup.push(count);
                    }
                }
            }
            break;
        }
    }
    return classes.top().getTurmaCode();
}
Menu::Menu() {
    this->d = Data();
    d.parse_file1();
    d.parse_file2();
    d.parse_file3();
}
