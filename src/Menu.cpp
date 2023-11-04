//
// Created by davidmg on 28-10-2023.
//

#include "Menu.h"



/**
 * Adds a revertable action to the record stack. - complexity O(1)
 * @param action to add
 */
void Menu::add_Action(Action action) {
    this->d.addAction(action);
}
/**
 * Checks if a student with given id can be added back
 * to a class with given classcode from a specific
 * curricular unit with given uccode. - complexity O(202027527)
 * @param id of the given student.
 * @param uccode of the given UC.
 * @param classcode of the class
 * @return true if it can be added back, false otherwise
 */
bool Menu::canBeAddedBack(int id, string uccode,string classcode){
    map<string,UC> temp = d.get_uc_map();
    string name;
    for(auto stu: d.get_all_students()){
        if(stu.getID() == id){
            name = stu.getName();
            break;
        }
    }
    auto it = temp.find(uccode);
    vector<Turma> compatible_classes;
    vector<Turma> turmas = it->second.getClasses();
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
        it->second.setClasses(turmas);
    }
    else{
        return false;
    }


    d.set_uc_map(temp);
    return true;
}
/**
 * This function gets the last function executed from stack record,
 * tries to execute its inverse and removes it from the stack.
 */
bool Menu::undo() {
    stack<Action> temp = d.get_record();
    if(temp.top().getFunction() == "addUC") {
        removeUC(temp.top().get_id(), temp.top().getUcode());
        cout << "Action reverted succesfully." << '\n';
        cout << "Student " << temp.top().get_id() << " removed from UC " << temp.top().getUcode() << '\n';
        return true;
    }
    else if(temp.top().getFunction() == "removeUC") {
        if(canBeAddedBack(temp.top().get_id(), temp.top().getUcode(), temp.top().getSource())){
            cout << "Action reverted succesfully." << '\n';
            cout << "Student " << temp.top().get_id() << " added back to class " << temp.top().getSource()
                 << " of UC " << temp.top().getUcode() << '\n';
            return true;
        }
        else{
            cout << "It was not possible to revert the last action due to class occupation requirements." << '\n';
            return false;
        }
    }
    else if(temp.top().getFunction() == "switchUC") {
        if(canBeAddedBack(temp.top().get_id(), temp.top().getUcode(), temp.top().getSource())){
            removeUC(temp.top().get_id(),temp.top().getTarget());
            cout << "Action reverted succesfully." << '\n';
            cout << "Student " << temp.top().get_id() << " switched back from UC " << temp.top().getTarget()
                 << " to UC " << temp.top().getUcode()<<'\n';
            return true;
        }
        else{
            cout << "It was not possible to revert the last action due to class occupation requirements." << '\n';
            return false;
        }

    }
    else if(temp.top().getFunction() == "switchClass") {
        if (canaddClass(temp.top().get_id(), temp.top().getSource(), temp.top().getUcode())) {
            removeClass(temp.top().get_id(), temp.top().getUcode(), temp.top().getTarget());
            cout << "Action reverted succesfully." << '\n';
            return true;
        }

        else {
            cout << "It was not possible to revert the last action due to class occupation requirements." << '\n';
            return false;
        }
    }
    temp.pop();
    d.set_record(temp);
}
/**
 * Retrieves the schedule of a given student.
 * It also pushes this instruction to the log queue. - complexity O(N²)
 * @param ID of the student
 * @return a list of the schedules for the entire students week.
 */
list<Schedule> Menu::consultStudentSchedule(int ID){
    cout << '\n';
    map<string,UC> temp = d.get_uc_map();
    list<Schedule> v;
    string name;
    for(auto stu : d.get_all_students()){
        if(stu.getID() == ID) name = stu.getName();
    }
    for(auto uc: temp) {
        for (Turma turma : uc.second.getClasses()) {
            set<Student> students = turma.getStudents();
            Student stu = Student(ID,name);
            auto studentIter = students.find(stu);

            if (studentIter != students.end()) {
                vector<Schedule> schedules = turma.getSchedule();
                v.insert(v.end(), schedules.begin(), schedules.end());
                break;
            }
        }
    }
    if(v.empty()) {
        cout << "Please enter a valid student id with 9 digits." << '\n';
        return v;
    }

    v.sort();
    return v;
}
/**
 * Retrieves the schedule of a given class.
 * It also pushes this instruction to the log queue. - complexity O(N³)
 * @param classcode of the class to consult
 * @return a list of the schedules for the entire classes week.
 */
list<Schedule> Menu::consultClassSchedule(string classcode){
    cout << '\n';

    map<string,UC> temp = d.get_uc_map();
    list<Schedule> v;
    for(auto uc: temp) {
        for (Turma turma: uc.second.getClasses()) {
            if (turma.getTurmaCode() == classcode) {
                for (Schedule sche: turma.getSchedule()) v.push_back(sche);
            }
        }
    }
    if(v.empty()){
        cout << "Please enter a valid class code in the format (XLEICXX)" << '\n';
        return v;
    }

    v.sort();
    return v;
}
/**
 * Retrieves the schedule of a given UC.
 * It also pushes this instruction to the log queue. - complexity O(N²)
 * @param uccode of the given UC to consult
 * @return a list of the schedules for the entire UCs week.
 */
list<Schedule> Menu::consultUCSchedule(string uccode) {
    cout <<'\n';
    map<string,UC> temp = d.get_uc_map();
    list<Schedule> v;
    auto it = temp.find(uccode);
    for (Turma turma : it->second.getClasses()) {
        for (Schedule sche : turma.getSchedule()) v.push_back(sche);
    }



    if(v.empty()){
        cout << "Please enter a valid UC code in the format (L.EICXXX)" << '\n';
        return v;
    }
    v.sort();
    return v;
}
/**
 * Method to make a set for all the students enrolled in a certain class identified by its classcode. - complexity O(N³)
 * @param classcode for the specific class whose enrolled students we want to inquire about.
 * @return set of students enrolled in the class.
 */
set<Student> Menu::listStudentsbyClass(std::string classcode1) {
    cout << '\n';
    map<string,UC> temp = d.get_uc_map();

    set<Student> s;
    for(auto uc : temp){
        for(Turma turma: uc.second.getClasses()){
            if(turma.getTurmaCode() == classcode1){
                for(auto stu : turma.getStudents()){
                    s.insert(stu);
                }
            }
        }
    }

    return s;
}
/**
 * Method to print all the students enrolled in a certain Year identified by its number. - complexity (N³)
 * @param number that represents the specific year whose enrolled students we want to inquire about.
 */
bool Menu::listStudentsbyYear(char number){
    cout << '\n';
    set<Student> s;
    for (auto uc : d.get_uc_map()) {
        for(auto turma : uc.second.getClasses()){
            if (turma.getTurmaCode()[0] == number) {
                for (auto stu : turma.getStudents()) {
                    s.insert(stu);
                }
            }
        }
    }
    if(s.empty()) {

        cout << "Please enter a valid student year in the interval [1, 3]" << '\n';
    }
    else {
        cout << "Students enrolled in the year " << number << " :\n";
        for (Student stu : s) {
            cout << stu.getID() << ' ' << stu.getName() << '\n';
        }
        cout << "Ocupation of year " << number << " = " << s.size() << '\n';
    }

}
/**
 * Method to print all the students enrolled in a certain UC identified by its uccode. - complexity O(N²)
 * @param uccode of the given uc.
 */
bool Menu::listStudentsbyUC(string uc) {
    cout << '\n';
    map<string, UC> temp = d.get_uc_map();
    auto it = temp.find(uc);
    if (it != temp.end()) {
        for (Turma turma: it->second.getClasses()) {
            list<Student> l;
            cout << turma.getTurmaCode() << '\n';
            for (auto stu: turma.getStudents())
                l.push_back(stu);
            l.sort();
            for (auto stu1: l) {
                cout << stu1.getID() << ' ' << stu1.getName() << '\n';
            }
            cout << "Class size: " << l.size() << '\n' << '\n';
        }
        return true;
    }

    else {
        cout << "Please enter a valid UC code in the format (L.EICXXX)" << '\n';
        return false;
    }

}
/**
 * Prints every UC available for the students. - complexity O(N)
 */
void Menu::listAllUCs() {
    for(auto uc: d.get_uc_map()){
        cout << uc.second.getcode() << '\n';
    }
}
/**
 * Prints every student id and name.
 * Ends with the amount of existing unique students. - complexity O(N)
 */
void Menu::listAllStudents() {
    int count = 0;
    for (Student stu : d.get_all_students()) {
        cout << stu.getID() << ' ' << stu.getName() << '\n';
        count++;
    }
    cout << "Number of Students = " << count << '\n';
}
/**
 * Prints the UC(s) with more occupation by making use of two stacks,
 * one with all the ucs, and another with only the max occupation number. - complexity O(N²)
 */
void Menu::maxUCs() {
    stack<UC> ucs;
    stack<int> max_occup;

    for(auto uc : d.get_uc_map()) {
        int count = 0;
        for(auto turma: uc.second.getClasses()){
            count += turma.getStudents().size();
        }
        if(ucs.empty()){
            ucs.push(uc.second);
            max_occup.push(count);
        }
        else {
            if(max_occup.top() <= count){
                ucs.push(uc.second);
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
/**
 * Checks the possibility to add a student to another UC. - complexity O(N²)
 * @param ID of the student
 * @param uccode of the UC.
 * @return true if the student can be added to given UC, false otherwise.
 */
bool Menu::addUC(int ID, string uc) {
    list<Schedule> current = consultStudentSchedule(ID);
    string name;
    map<string, UC> temp = d.get_uc_map();
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
            auto it = temp.find(uc);
            vector<Turma> compatible_classes;
            vector<Turma> turmas = it->second.getClasses();
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
                it->second.setClasses(turmas);
            }
            d.set_uc_map(temp);
            return true;
        }
    }
    else {
        cout << "Please enter a valid student id with 9 digits." << '\n';
        return false;
    }
}
/**
 * Infers if a given student has reached its UC limit(7). - complexity O(N³)
 * @param id of the student.
 * @return true if it has reached the limit, false otherwise.
 */
bool Menu::checkMaxUC (int id) {
    int c = 0;
    for (auto uc : d.get_uc_map()) {
        for(auto turma : uc.second.getClasses()){
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
/**
 * Compares two schedules to determine compatibility, ensuring that
 * no classes overlap except in the case of both being theoretical classes. - complexity O(N²)
 * @param current the schedule in which we want to insert more classes(another schedule).
 * @param novo the schedule we want to add to an already existing one.
 * @return true if both schedules are compatible, false otherwise.
 */
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
/**
 * Removes the given student from the provided UC.
 * Prints a confirmation message at the end. - complexity O(N²)
 * @param ID of the student.
 * @param uccode of the UC.
 * @return the classcode of the class which the student was removed from.
 */
string Menu::removeUC(int ID, string uc1){
    map<string, UC> temp = d.get_uc_map();
    bool exists = false;
    string classcode;
    for(auto stu: d.get_all_students()){
        if(stu.getID() == ID){
            exists = true;
            break;
        }
    }
    if(exists){
        auto it3 = temp.find(uc1);

        vector<Turma> turmas = it3->second.getClasses();
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
        it3->second.setClasses(turmas);

        d.set_uc_map(temp);
        cout << "The student was removed from the given UC." << '\n';
    }
    else {
        cout << "Please enter a valid student id with 9 digits." << '\n';
    }
    return classcode;
}
/**
 * Verifies if a student can be added to a target UC,
 * taking into consideration that he will be removed
 * from the source UC. If possible the adding is done. - complexity O(N²)
 * @param id of the student.
 * @param source_uc the UC we want to switch from.
 * @param target_uc the UC we want to switch into.
 * @return true if the operation is possible, false otherwise.
 */
bool Menu::canaddUC(int id, string source_uc, string target_uc) {
    list<Schedule> current = consultStudentSchedule(id);
    for (auto it = current.begin(); it != current.end();it++) {
        if (it->get_uccode() == source_uc)
            auto it1 = current.erase(it);
        break;
    }
    //Pensar melhor nisto exatamente igual à add mas sem o for inicial;
    string name;
    map<string, UC> temp = d.get_uc_map();
    bool exists = false;
    for(auto stu: d.get_all_students()){
        if(stu.getID() == id){
            exists = true;
            name = stu.getName();
            break;
        }
    }
    if (exists) {
        auto it = temp.find(target_uc);
        vector<Turma> compatible_classes;
        vector<Turma> turmas = it->second.getClasses();
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
            it->second.setClasses(turmas);
        }
        d.set_uc_map(temp);
        return true;
    }
    else {
        cout << "Please enter a valid student id with 9 digits." << '\n';
        return false;
    }

}
/**
 *  Checks if a given student, identified by its id,
 *  is enrolled in a certain UC, identified by its uc_code. - complexity O(N²)
 * @param id of the student.
 * @param uc code of the given UC.
 * @return the classcode of the class the student is in, or an empty string if the student isn't enrolled in the UC.
 */
string Menu::ConsultClassbyUC(int id, string uc){
    map<string, UC> temp = d.get_uc_map();
    auto it = temp.find(uc);
    for(auto turma: it->second.getClasses()){
        for(auto stu: turma.getStudents()){
            if(stu.getID() == id){
                return turma.getTurmaCode();
            }
        }
    }
    return "";
}
/**
 * Verifies if a student can be added to a target class,
 * of a given UC, taking into consideration that he will
 * be removed from the original class. If possible the
 * adding is done. - complexity O(N³)
 * @param id of the student.
 * @param target_class the class we want to add the student into.
 * @param uccode of the given UC.
 * @return true if the operation is possible, false otherwise.
 */
bool Menu::canaddClass(int id, std::string target_class, std::string uc) {
    map<string, UC> temp = d.get_uc_map();
    list<Schedule> current = consultStudentSchedule(id);
    for (auto it = current.begin(); it != current.end();it++) {
        if (it->get_uccode() == uc)
            auto it1 = current.erase(it);
        break;
    }
    string name;
    string source_classcode = ConsultClassbyUC(id, uc);
    if (source_classcode == "") {
        cout << "The student is not enrolled in the provided UC" << '\n';

        return false;
    }
    bool exists = false;
    for (auto stu: d.get_all_students()) {
        if (stu.getID() == id) {
            exists = true;
            name = stu.getName();
            break;
        }
    }
    if (exists) {
        auto it = temp.find(uc);
        vector<Turma> compatible_classes;
        vector<Turma> turmas = it->second.getClasses();
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
                         " and removed from "<< source_classcode << endl;
                    break;
                }
            }
            it->second.setClasses(turmas);
        }


        d.set_uc_map(temp);
        return true;
    }

    return false;
}
/**
 * Removes the given student from the provided class, from the given UC. - complexity O(N³)
 * @param id of the student.
 * @param uc1 identifier of the UC.
 * @param classcode of the class.
 */
void Menu::removeClass(int id, string uc1, string classcode){
    map<string, UC> temp = d.get_uc_map();
    auto it = temp.find(uc1);
    vector<Turma> turmas = it->second.getClasses();
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
    it->second.setClasses(turmas);

    d.set_uc_map(temp);
}
Menu::Menu() {
    this->d = Data();
    d.parse_file1();
    d.parse_file2();
    d.parse_file3();
}
