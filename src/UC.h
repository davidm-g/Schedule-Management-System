#ifndef PROJECT1_CODE_UC_H
#define PROJECT1_CODE_UC_H
#include <string>
#include <vector>
#include <set>
#include "Class.h"

class UC {
    private:
        std::string UC_code;
        std::vector<Class> classes;
    public:
        UC();
        UC(std::string Uccode);
        UC(std::string Uccode, Class class1);
        void add_class(Class class1);
        std::string getcode() const;
        std::vector<Class>getClasses();

};


#endif