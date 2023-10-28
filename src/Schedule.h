#ifndef PROJECT1_CODE_SCHEDULE_H
#define PROJECT1_CODE_SCHEDULE_H
#include <string>
#include <iostream>
#include <map>

using namespace std;
class Schedule {
private:
    std::string weekday;
    float start_hour;
    float duration;
    std::string type;

public:
    Schedule(std::string weekday, float start_hour, float duration, std::string type);
    std::string get_weekday();
    float get_starthour();
    float get_duration();
    std::string get_type();

};


#endif
