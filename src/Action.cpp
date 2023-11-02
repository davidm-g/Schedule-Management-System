//
// Created by davidmg on 02-11-2023.
//

#include "Action.h"
Action::Action(string function, int id, string uccode, string source, string target){
    this->id = id;
    this->uccode = uccode;
    this->function = function;
    this->source = source;
    this->target = target;

}
int Action::get_id(){
    return this->id;
}
string Action::getFunction(){
    return this->function;
}
string Action::getUcode(){
    return this->uccode;
}
string Action::getSource(){
    return this->source;
}
string Action::getTarget(){
    return this->target;
}