//
// Created by afdom on 10/10/2023.
//

#include "UC.h"
UC::UC() {
    this->UC_code = "";
    this->classes = vector<Class>();
}

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

std::string UC::getcode() const{
    return this->UC_code;
}

std::vector<Class> UC::getClasses() {
    return this->classes;
}

/*
bool UC::operator< (UC &uc2) const {
    return (this->UC_code < uc2.getcode());
}
 */

