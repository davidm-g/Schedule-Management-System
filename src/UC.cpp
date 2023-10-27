//
//
//

#include "UC.h"
UC::UC(std::string uccode) {
    this->UC_code = uccode;
}
UC::UC(std::string uccode, Turma class1) {
    this->UC_code = uccode;
    this->classes.push_back(class1);
}

void UC::add_class(Turma class1) {
    this->classes.push_back(class1);
}

std::string UC::getcode() {
    return this->UC_code;
}

std::vector<Turma> UC::getClasses() {
    return this->classes;
}

void UC::setClasses(vector<Turma> X) {
    this->classes = X;
}



