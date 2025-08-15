#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "main.hpp"
#include "Date.hpp"
#include "Event.hpp"

const string POST = "POST";
const string PUT = "PUT";
const string GET = "GET";
const string DELETE = "DELETE";

const string SIGNUP = "signup";
const string LOGIN = "login";
const string LOGOUT = "logout";
const string EVENT = "event";
const string PERIODIC_EVENT = "periodic_event";
const string REPORT = "report";
const string JOIN_EVENT = "join_event";
const string CONFIRM = "confirm_join_event";
const string REJECT = "reject_join_event";

inline map<string, vector<string> > all_commands = {
    {POST, {SIGNUP, LOGIN, LOGOUT, EVENT, PERIODIC_EVENT, TASK, JOIN_EVENT, CONFIRM, REJECT}},
    {PUT, {TASK}},
    {GET, {REPORT, JOIN_EVENT}},
    {DELETE, {TASK}}
};

void readHolidays(vector<shared_ptr<Date> >& holidays, string path_to_file);
void validateMainCommand(string command);
void validateSecondCommand(string main_command, string second_command);
void everythingOK();
void printExeption(exception& ex);
void clearBuffer();
map<string, string> extractParameters(string input, string format);
shared_ptr<Date> strToDate(string date_str);
string dateToStr(shared_ptr<Date> date);
int getPriorityForType(string type);
void sortResult(vector<shared_ptr<Activity> >& result);
void printReport(vector<shared_ptr<Activity> >& result);

#endif