//
// Created by davidmg on 28-10-2023.
//

#include "Menu.h"

void Menu::add_Action(Action a) {
    this->d.addAction(a);
}
bool Menu::canBeAddedBack(int id, string uccode,string classcode){
    vector<UC> temp = d.get_uc_vector();
    string name;
    for(auto stu: d.get_all_students()){
        if(stu.getID() == id){
            name = stu.getName();
            break;
        }
    }
    for(auto &uc1 : temp) {
        if(uc1.getcode() == uccode) {
            vector<Turma> compatible_classes;
            vector<Turma> turmas = uc1.getClasses();
            for (auto &turma1 : turmas){
                bool flag = true;// ver se todas as turmas estão em equilíbrio
                for (auto &turma2 : turmas) {
                    if (turma1.getTurmaCode() != turma2.getTurmaCode()) {
                        int n = turma1.getStudents().size() - turma2.getStudents().size();
                        if(n >= 4){ //limit for class equilibrium
                            flag = false;
                            break;
                        }
                    }
                }
                if(flag) compatible_classes.push_back(turma1);
            }
            std::sort(compatible_classes.begin(), compatible_classes.end());
            bool exist = false;
            for(auto turma : compatible_classes){
                if(turma.getTurmaCode() == classcode){
                    exist = true;
                    break;
                }
            }
            if(exist){
                for(auto &turma : turmas){
                    if(turma.getTurmaCode() == classcode){
                        Student stu = Student(id,name);
                        turma.add_student(stu);
                        break;
                    }
                }
                uc1.setClasses(turmas);
            }
            else{
                return false;
            }
        }
    }
    d.set_uc_vector(temp);
    return true;
}
void Menu::undo() {
    stack<Action> temp = d.get_record();

    if(temp.top().getFunction() == "addUC") {
        removeUC(temp.top().get_id(), temp.top().getUcode());
        cout << "Action reverted succesfully." << '\n';
        cout << "Student " << temp.top().get_id() << " removed from UC " << temp.top().getUcode() << '\n';
    }
    else if(temp.top().getFunction() == "removeUC") {
        if(canBeAddedBack(temp.top().get_id(), temp.top().getUcode(), temp.top().getSource())){
            cout << "Action reverted succesfully." << '\n';
            cout << "Student " << temp.top().get_id() << " added back to class " << temp.top().getSource()
                << " of UC " << temp.top().getUcode() << '\n';
        }
        else{
            cout << "It was not possible to revert the last action due to class occupation requirements.";
        }
    }
    else if(temp.top().getFunction() == "switchUC") {
        if(canBeAddedBack(temp.top().get_id(), temp.top().getUcode(), temp.top().getSource())){
            removeUC(temp.top().get_id(),temp.top().getTarget());
            cout << "Action reverted succesfully." << '\n';
            cout << "Student " << temp.top().get_id() << " switched back from UC " << temp.top().getTarget()
                 << " to UC " << temp.top().getUcode() << '\n';
        }
        else{
            cout << "It was not possible to revert the last action due to class occupation requirements.";
        }
    }
    else if(temp.top().getFunction() == "switchClass") {
        if (canaddClass(temp.top().get_id(), temp.top().getSource(), temp.top().getUcode())) {
            removeClass(temp.top().get_id(), temp.top().getUcode(), temp.top().getTarget());
            cout << "Action reverted succesfully." << '\n';
        }

        else {
        cout << "It was not possible to revert the last action due to class occupation requirements.";
        }
    }
    temp.pop();
    d.set_record(temp);
}
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
        cout << "Please enter a valid student id with 9 digits." << '\n';
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
list<Schedule> Menu::consultUCSchedule(string uccode) {
    cout <<'\n';
    vector<UC> temp = d.get_uc_vector();
    list<Schedule> v;
    for(UC uc : temp) {
        if (uc.getcode() == uccode) {
            for (Turma turma : uc.getClasses()) {
                for (Schedule sche : turma.getSchedule()) v.push_back(sche);
            }
            break;
        }
    }
    if(v.empty())
        cout << "Please enter a valid UC code in the format (L.EICXXX)" << '\n';
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

    for(UC uc : temp) {
        if(uc.getcode() == uce){
            for(Turma turma : uc.getClasses()){
                list<Student> l;
                cout << turma.getTurmaCode() << '\n';
                for (auto stu: turma.getStudents())
                    l.push_back(stu);
                l.sort();
                if (l.empty()) cout << "Please enter a valid UC code in the format (L.EICXXX)" << '\n';
                for(auto stu1: l){
                    cout << stu1.getID() << ' ' << stu1.getName()  << '\n';
                }
                cout << "Class size: " << l.size() << '\n' << '\n';

            }
            break;
        }
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
bool Menu::addUC(int ID, string uc) {
    list<Schedule> current = consultStudentSchedule(ID);
    string name;
    vector<UC> temp = d.get_uc_vector();
    bool exists = false;
    for(auto stu: d.get_all_students()){
        if(stu.getID() == ID){
            exists = true;
            name = stu.getName();
            break;
        }
    }
    if (exists) {
       if(checkMaxUC(ID)){
           cout << "This student can not be added to more UCs"; //check if the student is register in more than 7 UCs
           return false;
       }
       else { // This student can be added to more UCs
            for(auto &uc1 : temp) {
                if(uc1.getcode() == uc) { // The UC we want to add the student to

                    vector<Turma> compatible_classes;
                    vector<Turma> turmas = uc1.getClasses();
                    for (auto &turma1 : turmas){
                        bool flag = true;// ver se todas as turmas estão em equilíbrio
                        for (auto &turma2 : turmas) {
                            if (turma1.getTurmaCode() != turma2.getTurmaCode()) {
                                int n = turma1.getStudents().size() - turma2.getStudents().size();
                                if(n >= 4){ //limit for class equilibrium
                                    flag = false;
                                    break;
                            }
                            }
                        }
                        if(flag) compatible_classes.push_back(turma1);
                    }
                    std::sort(compatible_classes.begin(), compatible_classes.end());
                    string classicode;
                    bool caninsert = false;
                    for(auto turma : compatible_classes){
                        if(compatibleSchedules(current,turma.getSchedule())){
                            classicode = turma.getTurmaCode();
                            caninsert=true;
                            break;
                        }
                    }
                    if(!caninsert){
                        cout<<"The student can't be added to the desired UC." << '\n';
                        return false;
                    }
                    else{
                        for(auto &turma : turmas){
                            if(classicode == turma.getTurmaCode()){
                                Student stu = Student(ID,name);
                                turma.add_student(stu);
                                cout<<"The student was added to class "<< classicode<<"."<<endl;
                                break;
                            }
                        }
                        uc1.setClasses(turmas);
                    }
                }
            }
            d.set_uc_vector(temp);
            return true;
       }
    }
    else {
        cout << "Please enter a valid student id with 9 digits." << '\n';
        return false;
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
    else return false;
}
bool Menu::compatibleSchedules(list<Schedule> current, vector<Schedule> novo) {
    for(auto sche: novo) {
        for(auto sche1 : current) {
            if (sche1.get_endhour() > sche.get_starthour() &&
                sche1.get_starthour() < sche.get_endhour() &&
                (sche.get_weekday() == sche1.get_weekday())) {
                if(sche1.get_type() == "T" || sche.get_type() == "T")
                    return true;
                else return false;
            }
        }
    }
    return true;
}
string Menu::removeUC(int ID, string uc1){
    vector<UC> temp = d.get_uc_vector();
    bool exists = false;
    string classcode;
    for(auto stu: d.get_all_students()){
        if(stu.getID() == ID){
            exists = true;
            break;
        }
    }
    if(exists){
        for(auto &uc : temp){
            if(uc1 == uc.getcode()){
                vector<Turma> turmas = uc.getClasses();
                for(auto &turma : turmas){
                    set<Student> students = turma.getStudents();
                    for(auto it = students.begin(); it != students.end(); it++){
                        if(it->getID() == ID) {
                            classcode = turma.getTurmaCode();
                            auto it1 = students.erase(it);
                            break;
                        }
                    }
                    turma.setStudents(students);

                }
                uc.setClasses(turmas);
                break;
            }
        }
        d.set_uc_vector(temp);
        cout << "The student was removed from the given UC." << '\n';
    }
    else {
        cout << "Please enter a valid student id with 9 digits." << '\n';
    }
    return classcode;
}
bool Menu::canaddUC(int id, string source_uc, string target_uc) {
    list<Schedule> current = consultStudentSchedule(id);
    for (auto it = current.begin(); it != current.end();it++) {
        if (it->get_uccode() == source_uc)
            auto it1 = current.erase(it);
            break;
    }
    string name;
    vector<UC> temp = d.get_uc_vector();
    bool exists = false;
    for(auto stu: d.get_all_students()){
        if(stu.getID() == id){
            exists = true;
            name = stu.getName();
            break;
        }
    }
    if (exists) {
        for (auto &uc1: temp) {
            if (uc1.getcode() == target_uc) { // The UC we want to add the student to
                vector<Turma> compatible_classes;
                vector<Turma> turmas = uc1.getClasses();
                for (auto &turma1: turmas) {
                    bool flag = true;// ver se todas as turmas estão em equilíbrio
                    for (auto &turma2: turmas) {
                        if (turma1.getTurmaCode() != turma2.getTurmaCode()) {
                            int n = turma1.getStudents().size() - turma2.getStudents().size();
                            if (n >= 4) { //limit for class equilibrium
                                flag = false;
                                break;
                            }
                        }
                    }
                    if (flag) compatible_classes.push_back(turma1);
                }
                std::sort(compatible_classes.begin(), compatible_classes.end());
                string classicode;
                bool caninsert = false;
                for (auto turma: compatible_classes) {
                    if (compatibleSchedules(current, turma.getSchedule())) {
                        classicode = turma.getTurmaCode();
                        caninsert = true;
                        break;
                    }
                }
                if (!caninsert) {
                    return false;
                }
                else {
                    for (auto &turma: turmas) {
                        if (classicode == turma.getTurmaCode()) {
                            Student stu = Student(id, name);
                            turma.add_student(stu);
                            cout << "The student was added to class " << classicode << " of " <<target_uc<<endl;
                            break;
                        }
                    }
                    uc1.setClasses(turmas);
                }
            }
        }
        d.set_uc_vector(temp);
        return true;
    }
    else {
        cout << "Please enter a valid student id with 9 digits." << '\n';
        return false;
    }

}
string Menu::ConsultClassbyUC(int id, string uc){
    vector<UC> temp = d.get_uc_vector();
    for(auto uc1: temp){
        if(uc1.getcode() == uc){
            for(auto turma: uc1.getClasses()){
                for(auto stu: turma.getStudents()){
                    if(stu.getID() == id){
                        return turma.getTurmaCode();
                    }
                }
            }
        }
    }
}
bool Menu::canaddClass(int id, std::string target_class, std::string uc) {
    vector<UC> temp = d.get_uc_vector();
    list<Schedule> current = consultStudentSchedule(id);
    for (auto it = current.begin(); it != current.end();it++) {
        if (it->get_uccode() == uc)
            auto it1 = current.erase(it);
        break;
    }
    string name;
    string source_classcode = ConsultClassbyUC(id, uc);
    bool exists = false;
    for (auto stu: d.get_all_students()) {
        if (stu.getID() == id) {
            exists = true;
            name = stu.getName();
            break;
        }
    }
    if (exists) {
        for (auto &uc1: temp) {
            if (uc1.getcode() == uc) { // The UC we want to add the student to
                vector<Turma> compatible_classes;
                vector<Turma> turmas = uc1.getClasses();
                for (auto &turma1: turmas) {
                    bool flag = true;// ver se todas as turmas estão em equilíbrio
                    for (auto &turma2: turmas) {
                        if (turma1.getTurmaCode() != turma2.getTurmaCode()) {
                            int n;

                            if (turma1.getTurmaCode() == source_classcode)
                                n = (turma1.getStudents().size() - 1) - turma2.getStudents().size();

                            else if (turma2.getTurmaCode() == source_classcode)
                                n = turma1.getStudents().size() - (turma2.getStudents().size() - 1);

                            else
                                n = turma1.getStudents().size() - turma2.getStudents().size();

                            if (n >= 4) { //limit for class equilibrium
                                flag = false;
                                break;
                            }
                        }
                    }
                    if (flag) compatible_classes.push_back(turma1);
                }
                std::sort(compatible_classes.begin(), compatible_classes.end());
                bool caninsert = false;
                for (auto turma: compatible_classes) {
                    if(turma.getTurmaCode() == target_class){
                        if (compatibleSchedules(current, turma.getSchedule()) ) {
                            caninsert = true;
                            break;
                        }
                    }
                }
                if (!caninsert) {
                    cout << "It's not possible to switch the student to the given class." << endl;
                    return false;
                }
                else {
                    for (auto &turma: turmas) {
                        if (target_class == turma.getTurmaCode()) {
                            Student stu = Student(id, name);
                            turma.add_student(stu);
                            cout << "The student was added to class " << target_class << " of " << uc <<
                            " and removed from "<< source_classcode<< endl;
                            break;
                        }
                    }
                    uc1.setClasses(turmas);
                }
            }
        }
        d.set_uc_vector(temp);
        return true;
    }
}
void Menu::removeClass(int id, string uc1, string classcode){
    vector<UC> temp = d.get_uc_vector();
    for(auto &uc : temp){
        if(uc1 == uc.getcode()){
            vector<Turma> turmas = uc.getClasses();
            for(auto &turma : turmas) {
                if (turma.getTurmaCode() == classcode) {
                    set<Student> students = turma.getStudents();
                    for (auto it = students.begin(); it != students.end(); it++) {
                        if (it->getID() == id) {
                            auto it1 = students.erase(it);
                            break;
                        }
                    }
                    turma.setStudents(students);
                }
            }
                uc.setClasses(turmas);
                break;
        }
    }
    d.set_uc_vector(temp);
}
Menu::Menu() {
    this->d = Data();
    d.parse_file1();
    d.parse_file2();
    d.parse_file3();
}
