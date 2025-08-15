#include "Functions.hpp"

void readHolidays(vector<shared_ptr<Date> >& holidays, string path_to_file){
    
    ifstream file_stream(path_to_file);
    string line;
    int day, month, year;

    getline(file_stream, line);
    while ( getline(file_stream, line) ){
        
        istringstream strstream(line);
        string temp;
        getline(strstream, temp, ',');
        day = stoi(temp);
        getline(strstream, temp, ',');
        month = stoi(temp);
        strstream >> year;
        holidays.push_back(make_shared<Date>(year, month, day));
    }
}

void validateMainCommand(string command){

    if ( all_commands.find(command) == all_commands.end() )
        throw bad_request();
}

void validateSecondCommand(string main_command, string second_command){

    vector<string> sub_main_command = all_commands[main_command];

    auto it = find(sub_main_command.begin(), sub_main_command.end(), second_command);
    if ( it == sub_main_command.end() )
        throw not_found();
}

map<string, string> extractParameters(string input, string format){

    map<string, string> params;
    regex re(format);

    auto begin = sregex_iterator(input.begin(), input.end(), re);
    auto end = sregex_iterator();

    for ( auto it = begin ; it != end ; it++ ){

        smatch match = *it;
        string value = match[2].matched ? match[2].str() : match[3].str();
        params[match[1].str()] = value;
    }
    
    return params;
}

void clearBuffer(){
    string temp;
    getline(cin, temp);
}

void everythingOK(){
    cout << "OK" << endl;
}

void printExeption(exception& ex){ 
    cout << ex.what() << endl;
}

shared_ptr<Date> strToDate(string date_str){

    istringstream str_stream(date_str);
    string year_str, month_str;
    int year, month, day;
    getline(str_stream, year_str, '/');
    getline(str_stream, month_str, '/');
    str_stream >> day;
    year = stoi(year_str);
    month = stoi(month_str);
    return make_shared<Date>(year, month, day);
}

int getPriorityForType(string type){

    if ( type == PERIODIC )
        return 1;

    if ( type == NORMAL )
        return 2;

    return 3;
}

void sortResult(vector<shared_ptr<Activity> >& result){

    sort(result.begin(), result.end(), [](auto& a, auto& b){

        shared_ptr<Date> date_a = a->getDate();
        shared_ptr<Date> date_b = b->getDate();
        int start_time_a = a->getStartTime();
        int start_time_b = b->getStartTime();
        int priority_a = getPriorityForType(a->getType());
        int priority_b = getPriorityForType(b->getType());

        if ( date_a->isEqual(date_b) ){

            if ( start_time_a == start_time_b ){

                if ( priority_a == priority_b )
                    return a->getID() < b->getID();

                return priority_a < priority_b;
            }

            return start_time_a < start_time_b;
        }

        return date_b->isAfter(date_a);
    });
}

void printReport(vector<shared_ptr<Activity> >& result){
    
    for ( auto activity : result ){

        string year = to_string(activity->getDate()->getYear());
        string month = to_string(activity->getDate()->getMonth());
        string day = to_string(activity->getDate()->getDay());
        string description = activity->getDescription();

        if ( stoi(month) < 10 )
            month = "0" + month;

        if ( stoi(day) < 10 )
            day = "0" + day;

        if ( activity->getType() == NORMAL ){

            cout << EVENT << " \"" << activity->getTitle() << "\" on " << year << "/" << month << "/" << day 
                << " from " << activity->getStartTime() << " for " << activity->getEndTime()-activity->getStartTime()
                << " hours: ";

            if ( !description.empty() )
                cout << "\"" << description << "\"";

            cout << endl;
        }

        else if ( activity->getType() == PERIODIC ){

            cout << PERIODIC_EVENT << " \"" << activity->getTitle() << "\" on " << year << "/"<< month << "/" << day
                 << " from " << activity->getStartTime() << " for " << activity->getEndTime()-activity->getStartTime() 
                << " hours " << activity->getPeriodicType() << ": ";

            if ( !description.empty() )
                cout << "\"" << description << "\"";

            cout << endl;
        }

        else {

            cout << TASK << " \"" << activity->getTitle() << "\" on " << year << "/" << month << "/" << day 
                << " at " << activity->getStartTime() << ": ";

            if ( !description.empty() )
                cout << "\"" << description << "\"";

            cout << endl;
        }
    }
}

