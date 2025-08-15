#include "System.hpp"

shared_ptr<User> System::findUser(string entered_username){

    for ( auto user : users )
        if ( user->getUserName() == entered_username )
            return user;

    return nullptr;
}

void System::signUp(string username, string password){

    if ( currently_in_ != nullptr )
        throw permission_denied();

    if ( findUser(username) != nullptr )
        throw bad_request();

    shared_ptr<User> new_user = make_shared<User>(username, password);
    users.push_back(new_user);
    currently_in_ = new_user;
}

void System::logIn(string username, string password){

    if ( currently_in_ != nullptr )
        throw permission_denied();

    auto user = findUser(username);

    if ( user == nullptr )
        throw not_found();

    if ( user->getPassword() != password )
        throw permission_denied();

    currently_in_ = user;
}

void System::logOut(){

    if ( currently_in_ == nullptr )
        throw permission_denied();
    
    currently_in_ = nullptr;
}

void System::checkDateConflict(shared_ptr<Date> event_date, int start_time, int end_time){

    for ( auto activity : currently_in_->getCalendar() ){
        if ( activity->getType() != TASK && event_date->isEqual(activity->getDate()) 
            && start_time < activity->getEndTime() && end_time > activity->getStartTime() )
            throw overlap();
    }

    for ( auto date : holidays_ ){ 
        if ( event_date->isEqual(date) )
            throw holiday_found();
    }
}

void System::addNormalEvent(string date_str, int start_time, int duration, string title, string description){
        
    if ( currently_in_ == nullptr )
        throw permission_denied();

    validateDate(date_str);
    shared_ptr<Date> event_date = strToDate(date_str);
    checkDateConflict(event_date, start_time, start_time+duration);

    int event_id = currently_in_->getEventCode();
    shared_ptr<NormalEvent> new_event = make_shared<NormalEvent>(event_date, start_time, duration, title, description, event_id, NORMAL);
    currently_in_->addToCalendar(new_event);
    currently_in_->addNormalEvent(new_event);
}

void System::addPeriodicEvent(string start_date_str, string end_date_str, int start_time, int duration, vector<string>& week_days, string title, string description){

    if ( currently_in_ == nullptr )
        throw permission_denied();

    validateDate(start_date_str);
    validateDate(end_date_str);
    shared_ptr<Date> start_date = strToDate(start_date_str);
    shared_ptr<Date> end_date = strToDate(end_date_str);

    if ( week_days.empty() )
        throw bad_request();

    int event_code = currently_in_->getPeriodicEventCode();
    vector<int> week_days_num;
    for ( auto day : week_days )
        week_days_num.push_back(DAYS_NUM[day]);

    shared_ptr<WeeklyEvent> new_event = make_shared<WeeklyEvent>(start_date, end_date, start_time, duration, week_days_num, title, description);
    currently_in_->addPeriodicEvent(new_event);
    addWeeklyEvent(start_date, end_date, start_time, duration, week_days_num, title, description, event_code);
}

void System::addWeeklyEvent(shared_ptr<Date> start_date, shared_ptr<Date> end_date, int start_time, int duration,
    vector<int> week_days_num, string title, string description, int event_code){

    shared_ptr<Date> temp = start_date;
    int current_day = temp->getDayNum();
    bool overlap_happened = false;
    bool holiday_happened = false;
    vector<shared_ptr<Activity> > new_activities;

    while ( !(temp->isAfter(end_date)) ){

        if ( current_day == 7 )
            current_day = 0;

        if ( find(week_days_num.begin(), week_days_num.end(), current_day) != week_days_num.end() ){

            try {
                checkDateConflict(temp, start_time, start_time+duration);
            }
            
            catch(overlap& ex){
                overlap_happened = true;
                break;
            }

            catch(holiday_found& ex){
                holiday_happened = true;
                temp = temp->advanceDayByOne();
                current_day++;
                continue;
            }
            shared_ptr<NormalEvent> new_event = make_shared<NormalEvent>(temp, start_time, duration, title, description, event_code, PERIODIC, WEEKLY);
            new_activities.push_back(new_event);
        }
        temp = temp->advanceDayByOne();
        current_day++;
    }

    if ( overlap_happened )
        throw overlap();

    for ( auto activity : new_activities )
        currently_in_->addToCalendar(activity);

    if ( holiday_happened )
        throw holiday_found();
}

void System::addTask(string date_str, int time, string title, string description){

    if ( currently_in_ == nullptr )
        throw permission_denied();

    validateDate(date_str);
    shared_ptr<Date> date = strToDate(date_str);

    shared_ptr<Task> new_task = make_shared<Task>(date, time, title, description, currently_in_->getTaskCode());
    currently_in_->addTask(new_task);
    currently_in_->addToCalendar(new_task);
}

void System::deleteTask(int task_id){

    if ( currently_in_ == nullptr )
        throw permission_denied();

    if ( !(currently_in_->taskExist(task_id)) )
        throw not_found();
    
    currently_in_->deleteTask(task_id);
}

void System::editTask(int task_id, string new_date_str, int new_time, string new_title, string new_description){

    if ( currently_in_ == nullptr )
        throw permission_denied();

    if ( !(currently_in_->taskExist(task_id)) )
        throw not_found();

    validateDate(new_date_str);
    shared_ptr<Date> new_date = strToDate(new_date_str);
    currently_in_->editTask(task_id, new_date, new_time, new_title, new_description);
}

void System::addJoinEvent(string date_str, int start_time, int end_time, string guests_str, string title, string description){

    if ( currently_in_ == nullptr )
        throw permission_denied();

    validateDate(date_str);
    shared_ptr<Date> date = strToDate(date_str);

    validateGuestInput(guests_str);
    vector<string> guests_names;
    vector<shared_ptr<User> > guests;

    istringstream str_stream(guests_str);
    int commas_count = count(guests_str.begin(), guests_str.end(), ',');
    string username;
    shared_ptr<User> invited_user;

    for ( int i=0 ; i<commas_count ; i++ ){

        getline(str_stream, username, ',');
        invited_user = findUser(username);
        if ( invited_user == nullptr )
            throw not_found();

        guests.push_back(invited_user);
        guests_names.push_back(username);
    }
    str_stream >> username;
    invited_user = findUser(username);
    if ( invited_user == nullptr )
        throw not_found();

    guests.push_back(invited_user);
    guests_names.push_back(username);

    int duration = end_time-start_time;
    checkDateConflict(date, start_time, end_time);

    shared_ptr<JoinEvent> new_event = make_shared<JoinEvent>(date, start_time, duration, guests_names,
        currently_in_->getUserName(), title, description, join_event_code++);

    inviteUsers(guests, new_event);
}

void System::inviteUsers(vector<shared_ptr<User> >& guests, shared_ptr<JoinEvent> new_event){

    for ( auto guest : guests )
        guest->getInvitation(new_event);
}

string System::getInvitations(){

    if ( currently_in_ == nullptr )
        throw permission_denied();

    return currently_in_->showInvitations();
}

void System::confirmInvitation(int invitation_id){

    if ( currently_in_ == nullptr )
        throw permission_denied();

    auto new_event = currently_in_->confirmInvitation(invitation_id);
    if ( new_event != nullptr ){
        
        auto host = findUser(new_event->getHostName());
        host->addJoinEvent(new_event);
        host->addToCalendar(new_event);
    }
}

void System::rejectInvitation(int invitation_id){

    if ( currently_in_ == nullptr )
        throw permission_denied();

    currently_in_->rejectInvitation(invitation_id);
}

string System::report(string start_date_str, string end_date_str){

    if ( currently_in_ == nullptr )
        throw permission_denied();

    validateDate(start_date_str);
    validateDate(end_date_str);
    shared_ptr<Date> from = strToDate(start_date_str);
    shared_ptr<Date> to = strToDate(end_date_str);

    return currently_in_->reportAll(from,to);
}