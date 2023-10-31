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
#include <iomanip>
using namespace std;

int main(){
    Menu m = Menu();
    int choice;
    while (true) {
        std::cout << "-------------------------------------" << '\n';
        std::cout << "Welcome to Schedule Management System" << std::endl;
        std::cout << "1. View Class Schedule" << std::endl;
        std::cout << "2. View Student Schedule" << std::endl;
        std::cout << "3. Consult UCs enrollment per student" << std::endl;
        std::cout << "4. UC changes" << std::endl;
        std::cout << "5. Switch class" << std::endl;
        std::cout << "6. List the students within a certain Class" << std::endl;
        std::cout << "7. List all students by Year:" << std::endl;
        std::cout << "8. UCs with the greatest number of students" << std::endl;
        std::cout << "9. List all Students by UC" << std::endl;
        std::cout << "10. List all UCs" << std::endl;
        std::cout << "11. List all Students" << std::endl;
        std::cout << "12. Exit" << std::endl;
        std::cout << "Please enter your choice (1-12): ";
        std::cin >> choice;
        std::cout << "-------------------------------------" << '\n';

        switch (choice) {
            case 1:
            {
                std::string clascode;
                cout << "Please enter the class code: ";
                cin >> clascode;
                list<Schedule> v = m.consultClassSchedule(clascode);
                for (Schedule s : v) {
                    float endhour = s.get_starthour() + s.get_duration();
                    cout << left << setw(9) << s.get_weekday() << " | " << setw(5) << s.get_starthour() <<
                         "->" << setw(5) << endhour << " | " << setw(2) << s.get_type() << " | "
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
                    float endhour = s.get_starthour() + s.get_duration();
                    cout << left << setw(9) << s.get_weekday() << " | " << setw(5) << s.get_starthour() <<
                         "->" << setw(5) << endhour << " | " << setw(2) << s.get_type() << " | "
                         << setw(8) << s.get_uccode() << " | " << s.get_classcode() << '\n';
                }
                break;
            }
            case 3: {
                // Implement functionality for adding a student
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
                        m.addUC(id, uc);
                        break;
                    }
                    case 2: {
                        int id;
                        string uc1, uc2;
                        cout << "Please enter the id of the student: ";
                        cin >> id;
                        cout << "Please enter the uccode of the UC you want to remove: ";
                        cin >> uc1;
                        cout << "Please enter the uccode of the UC you want to add: ";
                        cin >> uc2;
                        if(m.canaddUC(id,uc1,uc2)){
                            m.removeUC(id,uc1);
                        }
                        else{
                            cout << "The student can not change UCs\n";
                        }
                        break;
                    }
                    case 3: {
                        int id;
                        string uc;
                        cout << "Please enter the id of the student: ";
                        cin >> id;
                        cout << "Please enter the uccode: ";
                        cin >> uc;
                        m.removeUC(id, uc);
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
                }
                break;
            }
            case 6:
            {
                std::string clascode;
                cout << "Please enter the class code: ";
                cin >> clascode;
                m.listStudentsbyClass(clascode);
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
                std::cout << "Goodbye!" << std::endl;
                return 0;
            }
            default:
                std::cout << "Invalid choice. Please enter a valid option (1-12)." << std::endl;
                break;
        }
    }
}