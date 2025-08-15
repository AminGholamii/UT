#include "Date.hpp"

Date::Date(int year, int month, int day){

    if ( day > 30 || month > 12 )
        throw bad_request();

    day_ = day;
    month_ = month;
    year_ = year;
}

bool Date::isEqual(shared_ptr<Date> other){

    if ( day_ == other->day_ 
        && month_ == other->month_
        && year_ == other->year_){
            
            return true;
        }
        
    return false;
}

bool Date::isAfter(shared_ptr<Date> other){

    if (year_ != other->year_) 
        return year_ > other->year_;

    if (month_ != other->month_) 
        return month_ > other->month_;

    return day_ > other->day_;
}

bool Date::isBetween(shared_ptr<Date> from, shared_ptr<Date> to) {

    int current = year_ * 10000 + month_ * 100 + day_;
    int from_int = from->year_ * 10000 + from->month_ * 100 + from->day_;
    int to_int = to->year_ * 10000 + to->month_ * 100 + to->day_;
    
    return (current >= from_int && current <= to_int);
}

shared_ptr<Date> Date::advanceDayByOne(){

    int new_day = day_+1;
    int new_month = month_;
    int new_year = year_;

    if ( new_day > 30 ){
        new_day = 1;
        if ( new_month == 12 ){
            new_month = 1;
            new_year++;
        }
        else 
            new_month++;
    }

    return make_shared<Date>(new_year, new_month, new_day);
}

shared_ptr<Date> Date::advanceMonthByOne(){

    int new_day = day_;
    int new_month = month_+1;
    int new_year = year_;

    if ( new_month > 12 ){
        new_month = 1;
        new_year++;
    }
    return make_shared<Date>(new_year, new_month, new_day);
}

int Date::getDayNum() const{

    int diff = (year_ - 1404)*360 + (month_ - 1)*30 + (day_ - 1);
    int index = diff % 7;

    return index;
}