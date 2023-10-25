#ifndef PROJECT1_CODE_SCHEDULE_H
#define PROJECT1_CODE_SCHEDULE_H


class Schedule {
    private:
        std::string uc_code;
        std::string classcode;
        std::string weekday;
        float start_time;
        float duration;
    public:
        Schedule(std::string uc_code, std::string classcode);
        std::string get_weekday();
        float get_start();
        float get_duration();
};


#endif
