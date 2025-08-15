#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "main.hpp"
#include "Functions.hpp"
#include "User.hpp"
#include "Exeptions.hpp"
#include "Date.hpp"

class System{
public:
    void run();
    void applyCommand(string main_command, string second_command);
    shared_ptr<User> findUser(string entered_username);
    void signUp();
    void logIn();
    void logOut();
    void checkDateConflict(shared_ptr<Date> event_date, int start_time, int end_time);
    void addNormalEvent();
    void addPeriodicEvent();
    void addDailyEvent(shared_ptr<Date> start_date, shared_ptr<Date> end_date, int start_time, int duration,
         string title, string description, int event_code);
    void addWeeklyEvent(shared_ptr<Date> start_date, shared_ptr<Date> end_date, int start_time, int duration,
        vector<int> week_days, string title, string description, int event_code);
    void addMonthlyEvent(shared_ptr<Date> start_date, shared_ptr<Date> end_date, int start_time, int duration,
        int day, string title, string description, int event_code);

    void addTask();
    void deleteTask();
    void editTask();

    void addJoinEvent();
    void getInvitations();
    void inviteUsers(vector<shared_ptr<User> >& guests, shared_ptr<JoinEvent> new_event);
    void confirmInvitation();
    void rejectInvitation();


    void report();

    void setHolidays(vector<shared_ptr<Date> > holidays){ holidays_ = holidays; }

private:
    vector<shared_ptr<User> > users;
    shared_ptr<User> currently_in_ = nullptr;
    vector<shared_ptr<Date> > holidays_;
    int join_event_code = 1;
};

#endif