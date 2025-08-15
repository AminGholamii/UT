#ifndef HOLIDAYS_HPP
#define HOLIDAYS_HPP

#include "main.hpp"
#include "Exeptions.hpp"

inline map<string, int> DAYS_NUM = {{"Friday",0}, {"Saturday",1}, {"Sunday",2}, {"Monday",3}, {"Tuesday",4}, {"Wednesday",5}, {"Thursday",6}};

class Date{
public:
    Date(int year=1404, int month=1, int day=1);
    bool isEqual(shared_ptr<Date> second_date);
    bool isAfter(shared_ptr<Date> other);
    bool isBetween(shared_ptr<Date> from, shared_ptr<Date> to);
    shared_ptr<Date> advanceDayByOne();
    shared_ptr<Date> advanceMonthByOne();
    int getDayNum() const;

    int getYear() const { return year_; }
    int getMonth() const { return month_; }
    int getDay() const { return day_; }
    
private:
    int day_;
    int month_;
    int year_;
};

#endif