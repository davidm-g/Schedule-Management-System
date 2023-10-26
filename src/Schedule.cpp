//
// Created by afdom on 10/10/2023.
//

#include "Schedule.h"
Schedule::Schedule(std::string weekday, float start_hour, float duration, std::string type){
    this->weekday = weekday;
    this->start_hour = start_hour;
    this->duration = duration;
    this->type = type;
}
string Schedule::get_weekday(){
    return this->weekday;
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