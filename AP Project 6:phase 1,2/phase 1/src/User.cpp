#include "User.hpp"

User::User(string username, string password){
    username_ = username;
    password_ = password;
}

void User::addToCalendar(shared_ptr<Activity> new_activity){

    calendar.push_back(new_activity);
}

void User::addNormalEvent(shared_ptr<NormalEvent> new_event){

    normal_events.push_back(new_event);
    normal_events_code++;
}

void User::addPeriodicEvent(shared_ptr<PeriodicEvent> new_event){

    periodic_events.push_back(new_event);
    periodic_events_code++;
}

void User::addTask(shared_ptr<Task> new_task){

    tasks.push_back(new_task);
    tasks_code++;
}

bool User::taskExist(int entered_id){

    for ( auto task : tasks )
        if ( task->getID() == entered_id )
            return true;

    return false;
}

void User::deleteTask(int task_id){

    for ( auto it = tasks.begin() ; it != tasks.end() ; it++ ){
        
        if ( (*it)->getID() == task_id ){
            tasks.erase(it);
            break;;
        }
    }

    for ( auto it = calendar.begin() ; it != calendar.end() ; it++){

        if ( (*it)->getType() == TASK ){
            if ( (*it)->getID() == task_id ){
                calendar.erase(it); 
                return;
            }
        }
    }
}

void User::editTask(int task_id, shared_ptr<Date> new_date, int new_time, string new_title, string new_description){

    vector<shared_ptr<Activity> >::iterator task_it;
    for ( auto it = calendar.begin() ; it != calendar.end() ; it++){

        if ( (*it)->getType() == TASK ){
            if ( (*it)->getID() == task_id ){
                calendar.erase(it);
                break;
            }
        }
    }

    for ( auto task : tasks ){

        if ( task->getID() == task_id ){

            shared_ptr<Date> default_date = make_shared<Date>(1404,1,1);
            int default_time = -1;

            if ( !(new_date->isEqual(default_date)) )
                task->setNewDate(new_date);
            
            if ( new_time != default_time )
                task->setNewTime(new_time);

            if ( !new_title.empty() )
                task->setNewTitle(new_title);

            if ( !new_description.empty() )
                task->setNewDescription(new_description);

            calendar.push_back(task);
            return;
        }
    }
}

void User::reportAll(shared_ptr<Date> from, shared_ptr<Date> to){

    vector<shared_ptr<Activity> > result;
    for ( auto activity : calendar ){
        if ( activity->getDate()->isBetween(from, to) )
            result.push_back(activity); 
    }

    if ( result.empty() )
        throw empty_();

    sortResult(result);
    printReport(result);
}

void User::reportEvents(shared_ptr<Date> from, shared_ptr<Date> to){

    vector<shared_ptr<Activity> > result;
    for ( auto norm_event : normal_events ){
        if ( norm_event->getDate()->isBetween(from, to) )
            result.push_back(norm_event);
    }

    if ( result.empty() )
        throw empty_();

    sortResult(result);
    printReport(result);
}

void User::reportPeriodicEvents(shared_ptr<Date> from, shared_ptr<Date> to){

    vector<shared_ptr<Activity> > result;
    for ( auto activity : calendar ){
        if ( activity->getType() == PERIODIC && activity->getDate()->isBetween(from, to) )
            result.push_back(activity);
    }

    if ( result.empty() )
        throw empty_();

    sortResult(result);
    printReport(result);
}

void User::reportTasks(shared_ptr<Date> from, shared_ptr<Date> to){

    vector<shared_ptr<Activity> > result;
    for ( auto task : tasks ){
        if ( task->getDate()->isBetween(from, to) )
            result.push_back(task);
    }

    if ( result.empty() )
        throw empty_();

    sortResult(result);
    printReport(result);
}



