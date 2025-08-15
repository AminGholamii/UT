#ifndef EVENT_HPP
#define EVENT_HPP

#include "main.hpp"
#include "Date.hpp"

const string NORMAL = "normal";
const string PERIODIC = "periodic";
const string TASK = "task";
const string JOIN = "join_event";

const string DAILY = "Daily";
const string WEEKLY = "Weekly";
const string MONTHLY = "Monthly";

class Activity {
public:

    int getStartTime() const { return start_time_; };
    int getEndTime() const { return start_time_+duration_; };
    shared_ptr<Date> const getDate() { return date_; }
    string getType() const { return type_; }
    string getPeriodicType() const { return periodic_type_; }
    int getID() const { return id_; }
    string getTitle() const { return title_; }
    string getDescription() const { return description_; }

protected:
    shared_ptr<Date> date_;
    int start_time_;
    int duration_;
    string title_;
    string description_;
    string type_;
    string periodic_type_;
    int id_;
};

class Task : public Activity{
public:
    Task(shared_ptr<Date> date, int time, string title, string description, int id);

    void setNewDate(shared_ptr<Date> new_date) { date_ = new_date; }
    void setNewTime(int new_time) { start_time_ = new_time; }
    void setNewTitle(string new_title) { title_ = new_title; }
    void setNewDescription(string new_description) { description_ = new_description; }
};

class NormalEvent : public Activity {
public:
    NormalEvent(shared_ptr<Date> date, int start_time, int duration, string title, string description,
                int id, string type, string periodic_type = "");
};

class JoinEvent : public Activity {
public:
    JoinEvent(shared_ptr<Date> date, int start_time, int duration, vector<string> guests, string host,
         string title, string description, int id);

    string getHostName() const { return host_; }
    int getTimesAccepted() const { return times_accepted; }
    void someoneAccepted() { times_accepted++; }

private:
    string host_;
    vector<string> guests_;
    int times_accepted = 0;
};

class PeriodicEvent : public Activity{
public:

    shared_ptr<Date> getStartDate() const { return start_date_; }
    shared_ptr<Date> getEndDate() const { return end_date_; }

protected:
    shared_ptr<Date> start_date_;
    shared_ptr<Date> end_date_;
    string periodic_type;

};

class DailyEvent : public PeriodicEvent{
public:
    DailyEvent(shared_ptr<Date> start_date, shared_ptr<Date> end_date, int start_time, int duration,
            string title, string description);
};

class WeeklyEvent : public PeriodicEvent{
public:
    WeeklyEvent(shared_ptr<Date> start_date, shared_ptr<Date> end_date, int start_time, int duration,
            vector<int> week_days, string title, string description);

private:
    vector<int> week_days_;
};

class MonthlyEvent : public PeriodicEvent{
public:
    MonthlyEvent(shared_ptr<Date> start_date, shared_ptr<Date> end_date, int start_time, int duration,
        int day, string title, string description);

private:
    int day_;
};

#endif