#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>

using namespace std;

#define ADD_TASK "add_task"
#define ADD_EMPLOYEE "add_employee"
#define ASSIGN_EMPLOYEE "assign_employee"
#define FINISH_TASK "finish_task"
#define REPORT "report"

///////////////////////////////////////////////////////////////////////////////////////

// List of prototypes : 

void addTask(map<string, string> &situations , map<string, int> &priorities);
void addEmployee(map <string, vector<string> > &employees);
void assignEmployee(map<string, string> &situations, map<string, vector<string> > &employees, map<string, vector<string>> &employees_tasks);
void finishTask(map<string, string> &situations);
void reportAll(map<string, string> situations);
bool cmp(const pair<string, int> &a, const pair<string, int> &b);
vector< pair<string, int> > sortByValue(map<string, int> &priorities);
void reportOnGoing(map<string, int> priorities, map<string, string> situations, map< string,vector<string> > employees_tasks);
void reportEmployeeDoneTasks(string employee_name, map<string, string> situations, map< string,vector<string> > employees);
void reportEmployeeCurrTasks(string employee_name, map<string, string> situations, map< string,vector<string> > employees);

///////////////////////////////////////////////////////////////////////////////////////


int main(){

    map <string, string> situations;  
    map <string, int> priorities;    
    map <string, vector<string> > employees;     
    map<string, vector<string> > employees_tasks;   

    string command;

    while (cin >> command){

        if ( command == ADD_TASK ){

            addTask(situations, priorities);
        }

        else if ( command == ADD_EMPLOYEE ){
            
            addEmployee(employees);
        }

        else if ( command == ASSIGN_EMPLOYEE ){

            assignEmployee(situations, employees, employees_tasks);
        }

        else if ( command == FINISH_TASK ){

            finishTask(situations);
        }

        else if ( command == REPORT ){

            string report_what;
            cin >> report_what;

            if ( report_what == "all" ){

                reportAll(situations);
            }

            else if ( report_what == "ongoing" ){

                reportOnGoing(priorities, situations, employees_tasks);
            }

            else if ( report_what == "employee" ){

                string employee_name;
                cin >> employee_name;
                reportEmployeeDoneTasks(employee_name, situations, employees);
                reportEmployeeCurrTasks(employee_name, situations, employees);
            }
        }
    }
    return 0;
}

void addTask(map<string, string> &situations , map<string, int> &priorities){

    string task_name;
    int priority;
    cin >> task_name;
    cin >> priority;
    situations[task_name] = "TODO";
    priorities[task_name] = priority;
}

void addEmployee(map <string, vector<string> > &employees){

    string employee_name;
    cin >> employee_name;
    employees[employee_name];  
    
}

void assignEmployee(map<string, string> &situations, map<string, vector<string> > &employees, map<string, vector<string>> &employees_tasks){

    string task_name;
    string employee_name;
    cin >> task_name;
    cin >> employee_name;
    situations[task_name] = "ONGOING";
    employees_tasks[task_name].push_back(employee_name);
    
    // sorts employees' names who are working on task task_name
    sort(employees_tasks[task_name].begin(), employees_tasks[task_name].end()); 
    employees[employee_name].push_back(task_name);
}

void finishTask(map<string, string> &situations){
 
    string task_name;
    cin >> task_name;
    situations[task_name] = "DONE";
}

void reportAll(map<string, string> situations){

    int num_of_todo_tasks = 0, num_of_ongoing_tasks = 0, num_of_done_tasks = 0;

    for ( auto [key, value] : situations ){

        if ( value == "TODO" ){
            num_of_todo_tasks++;
        }

        else if ( value == "ONGOING" ){
            num_of_ongoing_tasks++;
        }

        else if ( value == "DONE" ){
            num_of_done_tasks++;
        }
    }

    cout << "TODO: " << num_of_todo_tasks << '\n'
         << "ONGOING: " << num_of_ongoing_tasks << '\n'
         << "DONE: " << num_of_done_tasks << endl;
}

bool cmp(const pair<string, int> &a, const pair<string, int> &b){
    return a.second < b.second;
}

vector< pair<string, int> > sortByValue(map<string, int> &priorities){

    vector<pair<string, int> > A; 
 
    // copy key-value pair from Map to vector of pairs 
    for (auto& it : priorities) { 
        A.push_back(it); 
    } 
 
    // sort using comparator function 
    sort(A.begin(), A.end(), cmp); 
    return A;
}

void reportOnGoing(map<string, int> priorities, map<string, string> situations, map< string,vector<string> > employees_tasks){

    auto sorted_vector = sortByValue(priorities);

    for ( auto item : sorted_vector ){

        string key = item.first;
        int value = item.second;

        if ( situations[key] != "ONGOING" ) continue;

        cout << key <<  " " << "(" << value << ")" << ": " ;

        int i;

        for ( i=0 ; i < (employees_tasks[key].size())-1 ; i++ ){

            cout << (employees_tasks[key])[i] << ", ";
        }
        cout << (employees_tasks[key])[i] << endl;
    }
}

void reportEmployeeDoneTasks(string employee_name, map<string, string> situations, map< string,vector<string> > employees){

    int num_of_done_tasks = 0;

    for ( auto task : employees[employee_name] ){

        if ( situations[task] == "DONE" ){
                
                num_of_done_tasks++;
        }
    }

    cout << employee_name << " has done " << num_of_done_tasks << " tasks." << endl;
}

void reportEmployeeCurrTasks(string employee_name, map<string, string> situations, map< string,vector<string> > employees){

    vector <string> curr_employee_tasks;

    for ( int i=0 ; i < employees[employee_name].size() ; i++ ){

        string task = employees[employee_name][i];

        if ( situations[task] == "ONGOING" ){
            
            curr_employee_tasks.push_back(task);
        } 
    }

    if ( curr_employee_tasks.size() == 0 ){

        cout << employee_name << " is currently not working on any tasks." << endl;
    }

    else{

        cout << employee_name << " is currently working on these tasks:\n";

        for ( int i=0 ; i < curr_employee_tasks.size() ; i++ ){

            cout << i+1 << ". " << curr_employee_tasks[i] << '\n';
        }
    }
}
