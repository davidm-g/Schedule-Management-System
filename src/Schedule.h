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
    string uc;
    string turmacode;


public:
    Schedule(std::string weekday, float start_hour, float duration, std::string type,string uc,string turmacode);
    std::string get_weekday();
    float get_starthour();
    float get_duration();
    string get_uccode();
    string get_classcode();
    std::string get_type();
    bool operator< (const Schedule sch) const;
};


#endif
