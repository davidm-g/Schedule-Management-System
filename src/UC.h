#ifndef PROJECT1_CODE_UC_H
#define PROJECT1_CODE_UC_H
#include <string>
#include <vector>
#include <set>
#include "Turma.h"

class UC {
private:
    std::string UC_code;
    std::vector<Turma> classes;
public:
    UC(std::string Uccode);
    UC(std::string Uccode, Turma class1);
    void add_class(Turma class1);
    std::string getcode();
    std::vector<Turma>getClasses();
    void setClasses(vector<Turma> X);
};


#endif