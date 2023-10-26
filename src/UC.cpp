//
//
//

#include "UC.h"
UC::UC(std::string uccode) {
    this->UC_code = uccode;
}
UC::UC(std::string uccode, Class class1) {
    this->UC_code = uccode;
    this->classes.push_back(class1);
}

void UC::add_class(Class class1) {
    this->classes.push_back(class1);
}

std::string UC::getcode() {
    return this->UC_code;
}

std::vector<Class> UC::getClasses() {
    return this->classes;
}

void UC::setClasses(vector<Class> X) {
    this->classes = X;
}



