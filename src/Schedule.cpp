//
// Created by afdom on 10/10/2023.
//

#include "Schedule.h"
Schedule::Schedule(std::string weekday, float start_hour, float duration, std::string type,string uc,string turmacode){
    this->weekday = weekday;
    this->start_hour = start_hour;
    this->duration = duration;
    this->type = type;
    this->uc = uc;
    this->turmacode = turmacode;
}

string Schedule::get_classcode() {
    return this->turmacode;
}
string Schedule::get_uccode() {
    return this->uc;
}

float Schedule::get_starthour(){
    return this->start_hour;
}
float Schedule::get_duration(){
    return this->duration;
}
string Schedule::get_type(){
    return this->type;
}
string Schedule::get_weekday(){
    return this->weekday;
}
float Schedule::get_endhour() {
    return start_hour + duration;
}
int getDayNumber(const std::string& day) {
    map<string, int> days = { {"Monday" , 0}, {"Tuesday" , 1}, {"Wednesday" , 2},
                              {"Thursday" , 3}, {"Friday" , 4}};
    if (days.find(day) != days.end()) return days[day];
    else return -1; // Invalid day
}

bool Schedule::operator< (Schedule sch) const {
    if (getDayNumber(weekday) < getDayNumber(sch.get_weekday())) return true;
    else if(getDayNumber(weekday) == getDayNumber(sch.get_weekday()))
        return (start_hour < sch.get_starthour());
    return false;
}
