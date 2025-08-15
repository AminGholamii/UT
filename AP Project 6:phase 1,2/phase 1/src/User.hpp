#ifndef USER_HPP
#define USER_HPP

#include "main.hpp"
#include "Functions.hpp"
#include "Event.hpp"

class User{
public:
    User(string username, string password);
    void addToCalendar(shared_ptr<Activity> new_activity);
    void addNormalEvent(shared_ptr<NormalEvent> new_event);
    void addPeriodicEvent(shared_ptr<PeriodicEvent> new_event);
    void addTask(shared_ptr<Task> new_task);
    bool taskExist(int entered_id);
    void deleteTask(int task_id);
    void editTask(int task_id, shared_ptr<Date> new_date, int new_time, string new_title, string new_description);

    void reportAll(shared_ptr<Date> from, shared_ptr<Date> to);
    void reportEvents(shared_ptr<Date> from, shared_ptr<Date> to);
    void reportPeriodicEvents(shared_ptr<Date> from, shared_ptr<Date> to);
    void reportTasks(shared_ptr<Date> from, shared_ptr<Date> to);

    string getUserName() const { return username_; }
    string getPassword() const { return password_; }
    vector<shared_ptr<Activity> > getCalendar() const { return calendar; }
    int getEventCode() const { return normal_events_code; }
    int getPeriodicEventCode() const { return periodic_events_code; }
    int getTaskCode() const { return tasks_code; }

private:
    string username_;
    string password_;
    int normal_events_code = 1;
    int periodic_events_code = 1;
    int tasks_code = 1;
    vector<shared_ptr<Activity> > calendar;
    vector<shared_ptr<NormalEvent> > normal_events;
    vector<shared_ptr<PeriodicEvent> > periodic_events;
    vector<shared_ptr<Task> > tasks;
};

#endif