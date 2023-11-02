//
//
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "UC.h"
#include "Student.h"
#include <algorithm>
#include "Data.h"
#include "Menu.h"
#include "Action.h"
#include <iomanip>
#include <cmath>
using namespace std;

int main(){
    Menu m = Menu();
    int choice;
    stack<string> lastchange;
    while (true) {
        std::cout << "-------------------------------------" << '\n';
        std::cout << "Welcome to Schedule Management System" << std::endl;
        std::cout << "1. View Class Schedule" << std::endl;
        std::cout << "2. View Student Schedule" << std::endl;
        std::cout << "3. View UC Schedule" << std::endl;
        std::cout << "4. UC changes" << std::endl;
        std::cout << "5. Switch class" << std::endl;
        std::cout << "6. List the students within a certain Class" << std::endl;
        std::cout << "7. List all students by Year:" << std::endl;
        std::cout << "8. UCs with the greatest number of students" << std::endl;
        std::cout << "9. List all Students by UC" << std::endl;
        std::cout << "10. List all UCs" << std::endl;
        std::cout << "11. List all Students" << std::endl;
        std::cout << "12. See log" << std::endl;
        std::cout << "13. Exit" << std::endl;
        if (!lastchange.empty()) std::cout << "14. Undo last system change (" << lastchange.top() << ')' << std::endl;
        std::cout << "Please enter your number choice: ";
        cin >> choice;
        if(!cin) {
            std::cout << "Invalid option." << '\n'
            << "The program will stop.";
            break;
        }

        std::cout << "-------------------------------------" << '\n';

        switch (choice) {
            case 1:
            {
                std::string clascode;
                cout << "Please enter the class code: ";
                cin >> clascode;
                list<Schedule> v = m.consultClassSchedule(clascode);
                for (Schedule s : v) {
                    string sh, eh;
                    float endhour = s.get_starthour() + s.get_duration();
                    if(s.get_starthour() < 10) sh = '0';
                    if(endhour < 10) eh = '0';
                    if (remainder(s.get_starthour(), 1) != 0) sh += to_string((int)s.get_starthour()) + ':' + "30";
                    else sh += to_string((int)s.get_starthour()) + ':' + "00";
                    if (remainder(endhour, 1) != 0) eh += to_string((int)endhour) + ':' + "30";
                    else eh += to_string((int)endhour) + ':' + "00";
                    cout << left << setw(9) << s.get_weekday() << " | " << setw(5) << sh <<
                         "->" << setw(5) << eh << " | " << setw(2) << s.get_type() << " | "
                         << s.get_uccode() << '\n';
                }

                break;
            }
            case 2:
            {
                int ID;
                cout << "Please enter the student ID: ";
                cin >> ID;
                list<Schedule> v = m.consultStudentSchedule(ID);
                for (Schedule s : v) {
                    string sh, eh;
                    float endhour = s.get_starthour() + s.get_duration();
                    if(s.get_starthour() < 10) sh = '0';
                    if(endhour < 10) eh = '0';
                    if (remainder(s.get_starthour(), 1) != 0) sh += to_string((int)s.get_starthour()) + ':' + "30";
                    else sh += to_string((int)s.get_starthour()) + ':' + "00";
                    if (remainder(endhour, 1) != 0) eh += to_string((int)endhour) + ':' + "30";
                    else eh += to_string((int)endhour) + ':' + "00";
                    cout << left << setw(9) << s.get_weekday() << " | " << setw(5) << sh <<
                         "->" << setw(5) << eh << " | " << setw(2) << s.get_type() << " | "
                         << setw(8) << s.get_uccode() << " | " << s.get_classcode() << '\n';
                }

                break;
            }
            case 3: {
                string uccode;
                cout << "Please enter the UC code: ";
                cin >> uccode;
                list<Schedule> v = m.consultUCSchedule(uccode);
                for (Schedule s : v) {
                    string sh, eh;
                    float endhour = s.get_starthour() + s.get_duration();
                    if(s.get_starthour() < 10) sh = '0';
                    if(endhour < 10) eh = '0';
                    if (remainder(s.get_starthour(), 1) != 0) sh += to_string((int)s.get_starthour()) + ':' + "30";
                    else sh += to_string((int)s.get_starthour()) + ':' + "00";
                    if (remainder(endhour, 1) != 0) eh += to_string((int)endhour) + ':' + "30";
                    else eh += to_string((int)endhour) + ':' + "00";
                    cout << left << setw(9) << s.get_weekday() << " | " << setw(5) << sh <<
                         "->" << setw(5) << eh << " | " << setw(2) << s.get_type() << " | "
                         << s.get_classcode() << '\n';
                }
                break;
            }
            case 4:
            {
                cout << "Select the desired option: " << '\n'
                    << "1. Add UC\n" << "2. Switch UCs\n"
                    << "3. Remove UC\n";
                int n;
                cin >> n;
                switch (n){
                    case 1: {
                        int id;
                        string uc;
                        cout << "Please enter the id of the student: ";
                        cin >> id;
                        cout << "Please enter the uccode: ";
                        cin >> uc;
                        if(m.addUC(id, uc)){
                            Action a = Action("addUC", id, uc);
                            m.add_Action(a);
                            lastchange.push("addUC");
                            break;
                        }
                    }
                    case 2: {
                        int id;
                        string uc1, uc2, classcode;
                        cout << "Please enter the id of the student: ";
                        cin >> id;
                        cout << "Please enter the uccode of the UC you want to remove: ";
                        cin >> uc1;
                        cout << "Please enter the uccode of the UC you want to add: ";
                        cin >> uc2;
                        if(m.canaddUC(id,uc1,uc2)){
                            classcode = m.removeUC(id,uc1);
                            Action a = Action("switchUC", id, uc1, classcode, uc2);
                            m.add_Action(a);
                            lastchange.push("switchUC");
                        }
                        else{
                            cout << "The student can not change UCs\n";
                        }
                        break;
                    }
                    case 3: {
                        int id;
                        string uc, classcode;
                        cout << "Please enter the id of the student: ";
                        cin >> id;
                        cout << "Please enter the uccode: ";
                        cin >> uc;
                        classcode = m.removeUC(id, uc);
                        Action a = Action("removeUC", id, uc, classcode);
                        m.add_Action(a);
                        lastchange.push("removeUC");
                        break;
                    }
                }
                break;
            }
            case 5:
            {
                int id;
                string uc, target_class, og_classcode;
                cout << "Please enter the id of the student: ";
                cin >> id;
                cout << "Please enter the uc to manipulate: ";
                cin >> uc;
                cout << "Please enter the desired class: ";
                cin >> target_class;
                og_classcode = m.ConsultClassbyUC(id, uc);
                if(m.canaddClass(id,target_class,uc)){
                    m.removeClass(id, uc, og_classcode);
                    Action a = Action("switchClass", id, uc, og_classcode, target_class);
                    m.add_Action(a);
                    lastchange.push("switchClass");
                }
                break;
            }
            case 6: {
                std::string clascode;
                int n;
                cout << "Please enter the class code: ";
                cin >> clascode;
                set<Student> s = m.listStudentsbyClass(clascode);
                if (s.empty())
                    cout << "Please enter a valid class code in the format (XLEICXX)" << '\n';

                else {
                    for (auto stu: s)
                        cout << stu.getID() << ' ' << stu.getName() << '\n';
                    cout << "Number of students on class " << clascode << " = " << s.size() << '\n';
                }
                break;
            }
            case 7:
            {
                char year;
                cout << "Please enter the year to search for: ";
                cin >> year;
                m.listStudentsbyYear(year);
                break;
            }
            case 8:
            {
                m.maxUCs();
                break;
            }
            case 9: {
                string uce;
                cout << "Please enter the UC to search for: ";
                cin >> uce;
                m.listStudentsbyUC(uce);
                break;
            }
            case 10: {
                m.listAllUCs();
                break;
            }
            case 11: {
                m.listAllStudents();
                break;
            }
            case 12: {
                queue<string> log_cpy = m.getLog();
                while(!log_cpy.empty()) {
                    cout << log_cpy.front() << '\n';
                    log_cpy.pop();
                }
                break;
            }
            case 13: {
                std::cout << "Goodbye!" << std::endl;
                return 0;
            }
            case 14: {
                m.undo();
                lastchange.pop();
                break;
            }
            default: {
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
                break;
            }
        }
    }
}