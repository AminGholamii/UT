#include "handlers.hpp"

#include <cstdlib>
#include <iostream>

SignUpHandler::SignUpHandler(string file_path, shared_ptr<System> general_system) 
    : TemplateHandler(file_path){
    system_ = general_system;
}

Response* SignUpHandler::callback(Request* req) {

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);
    
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    if (context["message"] == "OK") {
        res->setSessionId(context["username"]);
    }
    return res;
}

CONTEXT SignUpHandler::handle(Request* req) {
    CONTEXT context;
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");

    if (username.empty() || password.empty()) {
        context["message"] = "Bad Request";
        context["username"] = username;
        return context;
    }

    if (username == "root") {
        throw Server::Exception("Remote root access has been disabled.");
    }

    string message;
    try {
        system_->signUp(username, password);
        message = OK;
    }
    catch (const exception& ex) {
        message = ex.what();
    }

    context["username"] = username;
    context["message"] = message;
    return context;
}

LoginHandler::LoginHandler(string file_path, shared_ptr<System> general_system) 
    : TemplateHandler(file_path){
    system_ = general_system;
}

Response* LoginHandler::callback(Request* req) {

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);
    
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    if (context["message"] == OK) {
        res->setSessionId(context["username"]);
    }
    return res;
}

CONTEXT LoginHandler::handle(Request* req) {
    CONTEXT context;
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");

    if (username.empty() || password.empty()) {
        context["message"] = "Bad Request";
        return context;
    }

    if (username == "root") {
        throw Server::Exception("Remote root access has been disabled.");
    }

    string message;
    try {
        system_->logIn(username, password);
        message = OK;
    }
    catch (const exception& ex) {
        message = ex.what();
    }

    context["username"] = username;
    context["message"] = message;
    return context;
}

Response* LogoutHandler::callback(Request* req){

    try {
        system_->logOut();
    }

    catch(...){}
    
    Response* res = Response::redirect("/");
    res->setSessionId(NO_ONE_LOGGED_IN);
    return res;
}

dashboardHandler::dashboardHandler(string file_path, shared_ptr<System> general_system) 
    : TemplateHandler(file_path){
    system_ = general_system;
}

Response* dashboardHandler::callback(Request* req){

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);

    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    
    if ( req->getSessionId() == NO_ONE_LOGGED_IN ){
        res = Response::redirect("/404.html");
    }

    return res;
}

CONTEXT dashboardHandler::handle(Request* req) {

    string username = req->getSessionId();
    CONTEXT context;

    context["username"] = username;
    return context;
}

AddTaskHandler::AddTaskHandler(string file_path, shared_ptr<System> general_system)
    : TemplateHandler(file_path){
        system_ = general_system;
}

Response* AddTaskHandler::callback(Request* req){

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);
    
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    return res;
}

CONTEXT AddTaskHandler::handle(Request* req){

    string date_str = req->getBodyParam(DATE);
    int time = stoi(req->getBodyParam(START_TIME));
    string title = req->getBodyParam(TITLE);
    string description = req->getBodyParam(DESCRIPTION);

    CONTEXT context;
    string message;
    try {
        system_->addTask(date_str, time, title, description);
        message = OK;
    }
    catch (exception& ex) {
        message = ex.what();
    }

    context["message"] = message;
    return context;
}

EditTaskHandler::EditTaskHandler(string file_path, shared_ptr<System> general_system)
    : TemplateHandler(file_path){
        system_ = general_system;
}

Response* EditTaskHandler::callback(Request* req){

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);
    
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    return res;
}

CONTEXT EditTaskHandler::handle(Request* req){

    int task_id = stoi(req->getBodyParam(TASK_ID));
    string date_str = req->getBodyParam(DATE);
    int time = stoi(req->getBodyParam(START_TIME));
    string title = req->getBodyParam(TITLE);
    string description = req->getBodyParam(DESCRIPTION);

    CONTEXT context;
    string message;
    try {
        system_->editTask(task_id, date_str, time, title, description);
        message = OK;
    }
    catch (exception& ex) {
        message = ex.what();
    }

    context["message"] = message;
    return context;
}

DeleteTaskHandler::DeleteTaskHandler(string file_path, shared_ptr<System> general_system)
    : TemplateHandler(file_path){
        system_ = general_system;
}

Response* DeleteTaskHandler::callback(Request* req){

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);
    
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    return res;
}

CONTEXT DeleteTaskHandler::handle(Request* req){

    int task_id = stoi(req->getBodyParam(TASK_ID));

    CONTEXT context;
    string message;
    try {
        system_->deleteTask(task_id);
        message = OK;
    }
    catch (exception& ex) {
        message = ex.what();
    }

    context["message"] = message;
    return context;
}

AddNormalEventHandler::AddNormalEventHandler(string file_path, shared_ptr<System> general_system)
    : TemplateHandler(file_path){
        system_ = general_system;
}

Response* AddNormalEventHandler::callback(Request* req){

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);
    
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    return res;
}

CONTEXT AddNormalEventHandler::handle(Request* req){

    string date_str = req->getBodyParam(DATE);
    int start_time = stoi(req->getBodyParam(START_TIME));
    int duration = stoi(req->getBodyParam(DURATION));
    string title = req->getBodyParam(TITLE);
    string description = req->getBodyParam(DESCRIPTION);

    CONTEXT context;
    string message;
    try {
        system_->addNormalEvent(date_str, start_time, duration, title, description);
        message = OK;
    }
    catch (exception& ex) {
        message = ex.what();
    }

    context["message"] = message;
    return context;
}

AddPeriodicEventHandler::AddPeriodicEventHandler(string file_path, shared_ptr<System> general_system)
    : TemplateHandler(file_path){
        system_ = general_system;
}

Response* AddPeriodicEventHandler::callback(Request* req){

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);
    
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    return res;
}

CONTEXT AddPeriodicEventHandler::handle(Request* req){

    string start_date_str = req->getBodyParam(START_DATE);
    string end_date_str = req->getBodyParam(END_DATE);
    int start_time = stoi(req->getBodyParam(START_TIME));
    int duration = stoi(req->getBodyParam(DURATION));
    string title = req->getBodyParam(TITLE);
    string description = req->getBodyParam(DESCRIPTION);

    vector<string> week_days;
    if (!req->getBodyParam("weekday_Saturday").empty())
        week_days.push_back("Saturday");
    if (!req->getBodyParam("weekday_Sunday").empty())
        week_days.push_back("Sunday");
    if (!req->getBodyParam("weekday_Monday").empty())
        week_days.push_back("Monday");
    if (!req->getBodyParam("weekday_Tuesday").empty())
        week_days.push_back("Tuesday");
    if (!req->getBodyParam("weekday_Wednesday").empty())
        week_days.push_back("Wednesday");
    if (!req->getBodyParam("weekday_Thursday").empty())
        week_days.push_back("Thursday");
    if (!req->getBodyParam("weekday_Friday").empty())
        week_days.push_back("Friday");

    CONTEXT context;
    string message;
    try {
        system_->addPeriodicEvent(start_date_str, end_date_str, start_time, duration, week_days, title, description);
        message = OK;
    }
    catch (exception& ex) {
        message = ex.what();
    }

    context["message"] = message;
    return context;
}

AddJoinEventHandler::AddJoinEventHandler(string file_path, shared_ptr<System> general_system)
    : TemplateHandler(file_path){
        system_ = general_system;
}

Response* AddJoinEventHandler::callback(Request* req){

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);
    
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    return res;
}

CONTEXT AddJoinEventHandler::handle(Request* req){

    string date_str = req->getBodyParam(DATE);
    int start_time = stoi(req->getBodyParam(START_TIME));
    int end_time = stoi(req->getBodyParam(END_TIME));
    string guests_str = req->getBodyParam(GUESTS);
    string title = req->getBodyParam(TITLE);
    string description = req->getBodyParam(DESCRIPTION);

    CONTEXT context;
    string message;
    try {
        system_->addJoinEvent(date_str, start_time, end_time, guests_str, title, description);
        message = OK;
    }
    catch (exception& ex) {
        message = ex.what();
    }

    context["message"] = message;
    return context;
}

GetInvitationsHandler::GetInvitationsHandler(string file_path, shared_ptr<System> general_system)
    : TemplateHandler(file_path){
        system_ = general_system;
}

Response* GetInvitationsHandler::callback(Request* req){

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    return res;
}

CONTEXT GetInvitationsHandler::handle(Request* req){

    CONTEXT context;
    string message;
    string invitations;
    try {
        invitations = system_->getInvitations();
        message = OK;
    }
    catch (exception& ex) {
        message = ex.what();
    }

    context["message"] = message;
    context["invitations_info"] = invitations;
    return context;
}

RejectInvitationsHandler::RejectInvitationsHandler(string file_path, shared_ptr<System> general_system)
    : TemplateHandler(file_path){
        system_ = general_system;
}

Response* RejectInvitationsHandler::callback(Request* req){

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    return res;
}

CONTEXT RejectInvitationsHandler::handle(Request* req){

    int invitation_id = stoi(req->getBodyParam(INVITATION_ID));

    CONTEXT context;
    string message;
    try {
        system_->rejectInvitation(invitation_id);
        message = OK;
    }
    catch (exception& ex) {
        message = ex.what();
    }

    context["message"] = message;
    return context;
}

ConfirmInvitationsHandler::ConfirmInvitationsHandler(string file_path, shared_ptr<System> general_system)
    : TemplateHandler(file_path){
        system_ = general_system;
}

Response* ConfirmInvitationsHandler::callback(Request* req){

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    return res;
}

CONTEXT ConfirmInvitationsHandler::handle(Request* req){

    int invitation_id = stoi(req->getBodyParam(INVITATION_ID));

    CONTEXT context;
    string message;
    try {
        system_->confirmInvitation(invitation_id);
        message = OK;
    }
    catch (exception& ex) {
        message = ex.what();
    }

    context["message"] = message;
    return context;
}

ReportHandler::ReportHandler(string file_path, shared_ptr<System> general_system)
    : TemplateHandler(file_path){
        system_ = general_system;
}

Response* ReportHandler::callback(Request* req){

    CONTEXT context = handle(req);
    string html_content = getParser()->getHtml(context);
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    res->setBody(html_content);
    return res;
}

CONTEXT ReportHandler::handle(Request* req){

    string start_date_str = req->getBodyParam(START_DATE);
    string end_date_str = req->getBodyParam(END_DATE);

    CONTEXT context;
    string message;
    string report;
    try {
        report = system_->report(start_date_str, end_date_str);
        message = OK;
    }
    catch (exception& ex) {
        message = ex.what();
    }

    context["message"] = message;
    context["report"] = report;
    return context;
}