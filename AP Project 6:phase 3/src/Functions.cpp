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

void validateDate(string dateStr) {

    regex pattern("^\\d{4}/\\d{2}/\\d{2}$");
    if (!regex_match(dateStr, pattern)) {
        throw bad_request();
    }
    
    int year, month, day;
    if (sscanf(dateStr.c_str(), "%d/%d/%d", &year, &month, &day) != 3) {
        throw bad_request();
    }

    if (month < 1 || month > 12) {
        throw bad_request();
    }

    if (day < 1 || day > 31) {
        throw bad_request();
    }
}

void validateGuestInput(string& guest_input){

    if (guest_input.empty()) {
        throw bad_request();
    }

    regex pattern("^\\s*[^,\\s]+(\\s*,\\s*[^,\\s]+)*\\s*$");
    if (!regex_match(guest_input, pattern)) {
        throw bad_request();
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

string dateToStr(shared_ptr<Date> date){

    string year = to_string(date->getYear());
    string month = to_string(date->getMonth());
    string day = to_string(date->getDay());

    if ( stoi(month) < 10 )
        month = "0" + month;

    if ( stoi(day) < 10 )
        day = "0" + day;

    return (year + "/" + month + "/" + day);
}

int getPriorityForType(string type){

    if ( type == JOIN_EVENT )
        return 1;

    if ( type == PERIODIC )
        return 2;

    if ( type == NORMAL )
        return 3;

    return 4;
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

string printReport(vector<shared_ptr<Activity> >& result){
    
    string res;
    for ( auto activity : result ){

        ostringstream oss;
        if ( activity->getType() == NORMAL ){

            oss << EVENT << " " << activity->getTitle() << " on " << dateToStr(activity->getDate())
                << " from " << activity->getStartTime() << " for " << activity->getEndTime()-activity->getStartTime()
                << " hours: " << activity->getDescription() << "" << "<br><br>";
        }

        else if ( activity->getType() == JOIN_EVENT ){

            shared_ptr<JoinEvent> curr_event = static_pointer_cast<JoinEvent>(activity);
            oss << JOIN_EVENT << " " << curr_event->getTitle() << " on " << dateToStr(curr_event->getDate())
                << " from " << curr_event->getStartTime() << " to " << curr_event->getEndTime() 
                << " hosted by " << curr_event->getHostName() << " : " 
                << curr_event->getDescription() << "<br><br>";
        }

        else if ( activity->getType() == PERIODIC ){

            oss << PERIODIC_EVENT << " " << activity->getTitle() << " on " << dateToStr(activity->getDate())
                 << " from " << activity->getStartTime() << " for " << activity->getEndTime()-activity->getStartTime() 
                << " hours " << activity->getPeriodicType() << ": " << activity->getDescription() << "<br><br>";
        }

        else {

            oss << TASK << " " << activity->getTitle() << " on " << dateToStr(activity->getDate())
                << " at " << activity->getStartTime() << ": " << activity->getDescription() << "<br><br>";
        }

        res += oss.str();
    }

    return res;
}