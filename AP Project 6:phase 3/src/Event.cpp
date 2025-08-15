#include "Event.hpp"

NormalEvent::NormalEvent(shared_ptr<Date> date, int start_time, int duration, string title, string description,
     int id, string type, string periodic_type){

    if ( duration <= 0 || start_time < 0 || start_time > 23 )
        throw bad_request();

    date_ = date;
    start_time_ = start_time;
    duration_ = duration;
    title_ = title;
    description_ = description;
    id_ = id;
    type_ = type;
    periodic_type_ = periodic_type;
}

DailyEvent::DailyEvent(shared_ptr<Date> start_date, shared_ptr<Date> end_date, int start_time, int duration,
                        string title, string description){

    if ( duration <= 0 || start_time < 0 || start_time > 23 )
        throw bad_request();
    
    periodic_type = DAILY;
    start_date_ = start_date;
    end_date_ = end_date;
    start_time_ = start_time;
    duration_ = duration;
    title_ = title;
    description_ = description;
}

WeeklyEvent::WeeklyEvent(shared_ptr<Date> start_date, shared_ptr<Date> end_date, int start_time, int duration,
                            vector<int> week_days, string title, string description){

    if ( duration <= 0 || start_time < 0 || start_time > 23 )
        throw bad_request();
    
    periodic_type = WEEKLY;
    start_date_ = start_date;
    end_date_ = end_date;
    start_time_ = start_time;
    duration_ = duration;
    week_days_ = week_days;
    title_ = title;
    description_ = description;
}

MonthlyEvent::MonthlyEvent(shared_ptr<Date> start_date, shared_ptr<Date> end_date, int start_time, int duration,
                            int day, string title, string description){

    if ( duration <= 0 || start_time < 0 || start_time > 23 )
        throw bad_request();

    periodic_type = MONTHLY;
    start_date_ = start_date;
    end_date_ = end_date;
    start_time_ = start_time;
    duration_ = duration;
    day_ = day;
    title_ = title;
    description_ = description;
}

Task::Task(shared_ptr<Date> date, int time, string title, string description, int id){

    if ( time < 0 || time > 24 )
        throw bad_request();

    date_ = date;
    start_time_ = time;
    duration_ = 0;
    title_ = title;
    description_ = description;
    id_ = id;
    type_ = TASK;
}

JoinEvent::JoinEvent(shared_ptr<Date> date, int start_time, int duration, vector<string> guests, string host,
     string title, string description, int id){

    if ( duration <= 0 || start_time < 0 || start_time > 23 )
        throw bad_request();

    date_ = date;
    start_time_ = start_time;
    duration_ = duration;
    host_ = host;
    guests_ = guests;
    title_ = title;
    description_ = description;
    id_ = id;
    type_ = JOIN;
}