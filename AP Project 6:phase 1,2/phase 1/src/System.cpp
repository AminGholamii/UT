#include "System.hpp"

void System::run(){
    
    string main_command;
    while ( cin >> main_command ){

        if ( cin.eof() ) 
            return;

        try {
            
            validateMainCommand(main_command);
            string second_command;
            cin >> second_command;
            char question_mark;
            cin >> question_mark;
            if ( question_mark != '?' )
                throw bad_request();
            
            validateSecondCommand(main_command, second_command);
            applyCommand(main_command, second_command);
        }
        
        catch (exception& ex){
            clearBuffer();
            printExeption(ex);
        }
    }        
}

void System::applyCommand(string main_command, string second_command){
    
    if ( second_command == SIGNUP )
        signUp();

    else if ( second_command == LOGIN )
        logIn();

    else if ( second_command == LOGOUT )
        logOut();

    else if ( second_command == EVENT )
        addNormalEvent();

    else if ( second_command == PERIODIC_EVENT )
        addPeriodicEvent();

    else if ( second_command == TASK ){
        if ( main_command == POST )
            addTask();

        else if ( main_command == DELETE )
            deleteTask();

        else 
            editTask();
    }

    else if ( second_command == REPORT )
        report();
}

shared_ptr<User> System::findUser(string entered_username){

    for ( auto user : users )
        if ( user->getUserName() == entered_username )
            return user;

    return nullptr;
}

void System::signUp(){

    try {

        string line;
        getline(cin, line);

        if ( currently_in_ != nullptr )
            throw permission_denied();

        string re_format = "\\s+(\\S+)\\s+\"(\\S+)\"";
        map<string, string> params = extractParameters(line, re_format);

        if ( params.find("username") == params.end() || params.find("password") == params.end() )
            throw bad_request();

        string username = params["username"];
        string password = params["password"];

        if ( findUser(username) != nullptr )
            throw bad_request();

        shared_ptr<User> new_user = make_shared<User>(username, password);
        users.push_back(new_user);
        currently_in_ = new_user;
        everythingOK();
    }

    catch (exception& ex){
        printExeption(ex);
        return;
    }
}

void System::logIn(){

    string line;
    getline(cin, line);
    try{
        if ( currently_in_ != nullptr )
            throw permission_denied();

        string re_format = "\\s+(\\S+)\\s+\"(\\S+)\"";
        map<string, string> params = extractParameters(line, re_format);

        if ( params.find("username") == params.end() || params.find("password") == params.end() )
            throw bad_request();

        string username = params["username"];
        string password = params["password"];

        auto user = findUser(username);

        if ( user == nullptr )
            throw not_found();

        if ( user->getPassword() != password )
            throw permission_denied();

        currently_in_ = user;
        everythingOK();
    }

    catch (exception& ex){
        printExeption(ex);
        return;
    }
}

void System::logOut(){

    try {
        clearBuffer();
        if ( currently_in_ == nullptr )
            throw permission_denied();
        
        currently_in_ = nullptr;
        everythingOK();
    }

    catch (exception& ex){
        printExeption(ex);
    }
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

void System::addNormalEvent(){

    try {
        
        string line;
        getline(cin, line);

        if ( currently_in_ == nullptr )
            throw permission_denied();

        string re_format = "\\s+(\\w+)\\s+(?:\"([^\"]+)\"|(\\S+))";
        map<string, string> params = extractParameters(line, re_format);

        if ( params.find("date") == params.end() || params.find("start_time") == params.end()
              || params.find("duration") == params.end() || params.find("title") == params.end() ) 
            throw bad_request();

        try {
            shared_ptr<Date> event_date = strToDate(params["date"]);
            int start_time = stoi(params["start_time"]);
            int duration = stoi(params["duration"]);

            checkDateConflict(event_date, start_time, start_time+duration);

            string title = params["title"];
            string description;

            if ( params.find("description") != params.end() )
                description = params["description"];

            int event_id = currently_in_->getEventCode();
            shared_ptr<NormalEvent> new_event = make_shared<NormalEvent>(event_date, start_time, duration, title, description, event_id, NORMAL);
            currently_in_->addToCalendar(new_event);
            currently_in_->addNormalEvent(new_event);
            everythingOK();
        }

        catch(...){
            exception_ptr ex_ptr = current_exception();
            rethrow_exception(ex_ptr);
        }
    }

    catch(exception& ex){
        printExeption(ex);
    }
}

void System::addPeriodicEvent(){

    try{

        string line;
        getline(cin, line);

        if ( currently_in_ == nullptr )
            throw permission_denied();

        string re_format = "\\s+(\\w+)\\s+(?:\"([^\"]+)\"|(\\S+))";
        map<string, string> params = extractParameters(line, re_format);

        if ( params.find("start_date") == params.end() || params.find("end_date") == params.end()
             || params.find("start_time") == params.end() || params.find("type") == params.end()
             || params.find("duration") == params.end() || params.find("title") == params.end() ) 
            throw bad_request();

        try {
            shared_ptr<Date> start_date = strToDate(params["start_date"]);
            shared_ptr<Date> end_date = strToDate(params["end_date"]);

            int start_time = stoi(params["start_time"]);
            int duration = stoi(params["duration"]);

            string title = params["title"];
            string description;
            if ( params.find("description") != params.end() )
                description = params["description"];

            string type = params["type"];
            int event_code = currently_in_->getPeriodicEventCode();

            if ( type == DAILY ){
                
                shared_ptr<DailyEvent> new_event = make_shared<DailyEvent>(start_date, end_date, start_time, duration, title, description);
                currently_in_->addPeriodicEvent(new_event);
                addDailyEvent(start_date, end_date, start_time, duration, title, description, event_code);
            }

            else if ( type == WEEKLY ){

                if ( params.find("week_days") == params.end() || params["week_days"].empty() )
                    throw bad_request();

                string week_days_ = params["week_days"];
                vector<int> week_days_num;

                int commas_count = count(week_days_.begin(), week_days_.end(), ',');
                istringstream str_stream(params["week_days"]);
                string day_of_week;

                for ( int i=0 ; i<commas_count ; i++){

                    getline(str_stream, day_of_week, ',');
                    if ( DAYS_NUM.find(day_of_week) == DAYS_NUM.end() )
                        throw bad_request();
                    
                    week_days_num.push_back(DAYS_NUM[day_of_week]);
                }

                str_stream >> day_of_week;
                if ( DAYS_NUM.find(day_of_week) == DAYS_NUM.end() )
                    throw bad_request();

                week_days_num.push_back(DAYS_NUM[day_of_week]);

                shared_ptr<WeeklyEvent> new_event = make_shared<WeeklyEvent>(start_date, end_date, start_time, duration, week_days_num, title, description);
                currently_in_->addPeriodicEvent(new_event);
                addWeeklyEvent(start_date, end_date, start_time, duration, week_days_num, title, description, event_code);
            }

            else if ( type == MONTHLY ){

                if ( params.find("day") == params.end() || params["day"].empty() )
                    throw bad_request();

                int day = stoi(params["day"]);
                shared_ptr<MonthlyEvent> new_event = make_shared<MonthlyEvent>(start_date, end_date, start_time, duration, day, title, description);
                currently_in_->addPeriodicEvent(new_event);
                addMonthlyEvent(start_date, end_date, start_time, duration, day, title, description, event_code);
            }

            else 
                throw bad_request();
        }

        catch(...){
            exception_ptr ex_ptr = current_exception();
            rethrow_exception(ex_ptr);
        }
    }

    catch (exception& ex){
        printExeption(ex);
    }
}

void System::addDailyEvent(shared_ptr<Date> start_date, shared_ptr<Date> end_date, int start_time, int duration, 
                            string title, string description, int event_code){

    shared_ptr<Date> temp = start_date;
    bool overlap_happened = false;
    bool holiday_happened = false;
    vector<shared_ptr<Activity> > new_activities;
    while ( !(temp->isAfter(end_date)) ){

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
            continue;
        }

        shared_ptr<NormalEvent> new_event = make_shared<NormalEvent>(temp, start_time, duration, title, description, event_code, PERIODIC, DAILY);
        new_activities.push_back(new_event);
        temp = temp->advanceDayByOne();
    } 

    if ( overlap_happened )
        throw overlap();

    for ( auto activity : new_activities )
        currently_in_->addToCalendar(activity);

    if ( holiday_happened )
        throw holiday_found();
    
    everythingOK();
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

    everythingOK();
}

void System::addMonthlyEvent(shared_ptr<Date> start_date, shared_ptr<Date> end_date, int start_time, int duration,
    int day, string title, string description, int event_code){
    
    shared_ptr<Date> temp = make_shared<Date>(start_date->getYear(), start_date->getMonth(), day);
    if ( temp->isAfter(start_date) || temp->isEqual(start_date) );
    else 
        temp = temp->advanceMonthByOne();
    
    bool overlap_happened = false;
    bool holiday_happened = false;
    vector<shared_ptr<Activity> > new_activities;
    while ( !(temp->isAfter(end_date)) ){

        try {
            checkDateConflict(temp, start_time, start_time+duration);
        }

        catch(overlap& ex){
            overlap_happened = true;
            break;
        }

        catch(holiday_found& ex){
            holiday_happened = true;
            temp = temp->advanceMonthByOne();
            continue;
        }
        shared_ptr<NormalEvent> new_event = make_shared<NormalEvent>(temp, start_time, duration, title, description, event_code, PERIODIC, MONTHLY);
        new_activities.push_back(new_event);
        temp = temp->advanceMonthByOne();
    }

    if ( overlap_happened )
        throw overlap();

    for ( auto activity : new_activities )
        currently_in_->addToCalendar(activity);

    if ( holiday_happened )
        throw holiday_found();

    everythingOK();
}

void System::addTask(){

    try{
        string line;
        getline(cin, line);

        if ( currently_in_ == nullptr )
            throw permission_denied();

        string re_format = "\\s+(\\w+)\\s+(?:\"([^\"]+)\"|(\\S+))";
        map<string, string> params = extractParameters(line, re_format);

        if ( params.find("date") == params.end() || params.find("time") == params.end() 
            || params.find("title") == params.end() )
            throw bad_request();

        shared_ptr<Date> date = strToDate(params["date"]);
        int time = stoi(params["time"]);
        string title = params["title"];
        string description;

        if ( params.find("description") != params.end() )
            description = params["description"];

        shared_ptr<Task> new_task = make_shared<Task>(date, time, title, description, currently_in_->getTaskCode());
        currently_in_->addTask(new_task);
        currently_in_->addToCalendar(new_task);
        everythingOK();
    }

    catch(exception& ex){
        printExeption(ex);
    }
}

void System::deleteTask(){

    try {
        string line;
        getline(cin, line);

        if ( currently_in_ == nullptr )
            throw permission_denied();

        istringstream str_stream(line);
        string word;
        str_stream >> word;
        if ( word != "task_id" )
            throw bad_request();

        int entered_id;
        str_stream >> entered_id;
        if ( !(currently_in_->taskExist(entered_id)) )
            throw not_found();
        
        currently_in_->deleteTask(entered_id);
        everythingOK();
    }

    catch(exception& ex){
        printExeption(ex);
    }
}

void System::editTask(){

    try{

        string line;
        getline(cin, line);

        if ( currently_in_ == nullptr )
            throw permission_denied();

        string re_format = "\\s+(\\w+)\\s+(?:\"([^\"]+)\"|(\\S+))";
        map<string, string> params = extractParameters(line, re_format);

        if ( params.find("task_id") == params.end() )
            throw bad_request();

        int entered_id = stoi(params["task_id"]);
        if ( !(currently_in_->taskExist(entered_id)) )
            throw not_found();
    
        if ( params.size() < 2 )
            throw bad_request();

        shared_ptr<Date> new_date = make_shared<Date>(1404,1,1);
        if ( params.find("date") != params.end() )
            new_date = strToDate(params["date"]);

        int new_time = -1;
        if ( params.find("time") != params.end() )
            new_time = stoi(params["time"]);

        string new_title, new_description;
        if ( params.find("title") != params.end() )
            new_title = params["title"];

        if ( params.find("description") != params.end() )
            new_description = params["description"];

        currently_in_->editTask(entered_id, new_date, new_time, new_title, new_description);
        everythingOK();
    }

    catch(exception& ex){
        printExeption(ex);
    }
}

void System::report(){

    try {
        string line;
        getline(cin, line);

        if ( currently_in_ == nullptr )
            throw permission_denied();

        string re_format = "\\s+(\\w+)\\s+(\\S+)";
        map<string, string> params = extractParameters(line, re_format);

        if ( params.find("to") == params.end() )
            throw bad_request();

        shared_ptr<Date> to = strToDate(params["to"]);
        shared_ptr<Date> from = make_shared<Date>();
        if ( params.find("from") != params.end() )
            from = strToDate(params["from"]);

        string type;
        if ( params.find("type") != params.end() )
            type = params["type"];

        if ( type.empty() )
            currently_in_->reportAll(from,to);

        else if ( type == EVENT )
            currently_in_->reportEvents(from, to);

        else if ( type == PERIODIC_EVENT )
            currently_in_->reportPeriodicEvents(from, to);

        else if ( type == TASK )
            currently_in_->reportTasks(from, to);

        else 
            throw bad_request();
    }

    catch(exception& ex){
        printExeption(ex);
    }
}