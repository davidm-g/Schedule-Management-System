//
// Created by davidmg on 28-10-2023.
//

#include "Menu.h"
#include <algorithm>
void Menu::consultStudentSchedule(int ID){
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
    v.sort();
    for (Schedule s : v) {
        float endhour = s.get_starthour() + s.get_duration();
        cout << s.get_weekday() << " | " << s.get_starthour() <<
            "->" << endhour << " | " << s.get_type() << " | "
            <<  s.get_uccode() << " | " << s.get_classcode() << '\n';
    }
}
void Menu::consultClassSchedule(string classcode){
    std::vector<UC> temp = d.get_uc_vector();
    list<Schedule> v;

    for(UC uc: temp) {
        for (Turma turma: uc.getClasses()) {
            if(turma.getTurmaCode() == classcode){
                for(Schedule sche : turma.getSchedule()) v.push_back(sche);
            }
        }
    }
    v.sort();
    for (Schedule s : v) {
        float endhour = s.get_starthour() + s.get_duration();
        cout << s.get_weekday() << " | " << s.get_starthour() <<
             "->" << endhour << " | " << s.get_type() << " | "
             << s.get_uccode() << '\n';
    }


}
void Menu::listAllUCs() {
    for (UC uc : d.get_uc_vector()) {
        cout << uc.getcode() << '\n';
    }
}

void Menu::listAllStudents() {
    for (Student stu : d.get_all_students()) {
        cout << stu.getID() << ' ' << stu.getName() << '\n';
    }
}

Menu::Menu() {
    this->d = Data();
    d.parse_file1();
    d.parse_file2();
    d.parse_file3();
}