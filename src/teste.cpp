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
using namespace std;

int main(){
    Menu m = Menu();
    int choice;
    while (true) {
        std::cout << "-------------------------------------" << '\n';
        std::cout << "Welcome to Schedule Management System" << std::endl;
        std::cout << "1. View Class Schedule" << std::endl;
        std::cout << "2. View Student Schedule" << std::endl;
        std::cout << "3. Add Student" << std::endl;
        std::cout << "4. Add Class" << std::endl;
        std::cout << "5. Add UC" << std::endl;
        std::cout << "6. Modify Class Schedule" << std::endl;
        std::cout << "7. Search for a Student" << std::endl;
        std::cout << "8. Search for a Class" << std::endl;
        std::cout << "9. Sort Schedules" << std::endl;
        std::cout << "10. List all UCs" << std::endl;
        std::cout << "11. List all Students" << std::endl;
        std::cout << "12. Exit" << std::endl;

        std::cout << "Please enter your choice (1-12): ";
        std::cin >> choice;
        std::cout << "-------------------------------------" << '\n';

        switch (choice) {
            case 1:
            {
                std::string clascod;
                cout << "Please enter the class code: ";
                cin >> clascod;
                m.consultClassSchedule(clascod);
                break;
            }
            case 2:
            {
                int ID;
                cout << "Please enter the student ID: ";
                cin >> ID;
                m.consultStudentSchedule(ID);
                break;
            }
            case 3:
                // Implement functionality for adding a student
                break;
            case 4:
                // Implement functionality for adding a class
                break;
            case 5:
                // Implement functionality for adding a UC
                break;
            case 6:
                // Implement functionality for modifying class schedule
                break;
            case 7:
                // Implement functionality for searching for a student
                break;
            case 8:
                // Implement functionality for searching for a class
                break;
            case 9:
                // Implement functionality for sorting schedules
                break;
            case 10:
                m.listAllUCs();
                break;
            case 11:
                m.listAllStudents();
                break;
            case 12:
                std::cout << "Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a valid option (1-12)." << std::endl;
                break;
        }
    }
}