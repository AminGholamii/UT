#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <map>
#include <string>
#include <algorithm>
#include "../server/server.hpp"

const string OK = "OK";
const string NO_ONE_LOGGED_IN = "";
const string TASK_ID = "taskId";
const string INVITATION_ID = "invitationId";
const string DATE = "date";
const string START_DATE = "startdate";
const string END_DATE = "enddate";
const string START_TIME = "starttime";
const string END_TIME = "endtime";
const string DURATION = "duration";
const string GUESTS = "guests";
const string TITLE = "title";
const string DESCRIPTION = "description";


typedef map<string, string> CONTEXT;

class SignUpHandler : public TemplateHandler {
public:
    SignUpHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

class LoginHandler : public TemplateHandler {
public:
    LoginHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

class LogoutHandler : public RequestHandler {
public:
    LogoutHandler(shared_ptr<System> general_system) { system_ = general_system; }
    Response* callback(Request*) override;
};

class dashboardHandler : public TemplateHandler {
public:
    dashboardHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

class AddTaskHandler : public TemplateHandler {
public:
    AddTaskHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

class EditTaskHandler : public TemplateHandler {
public:
    EditTaskHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

class DeleteTaskHandler : public TemplateHandler {
public:
    DeleteTaskHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

class AddNormalEventHandler : public TemplateHandler {
public:
    AddNormalEventHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

class AddPeriodicEventHandler : public TemplateHandler {
public:
    AddPeriodicEventHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

class AddJoinEventHandler : public TemplateHandler {
public:
    AddJoinEventHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

class GetInvitationsHandler : public TemplateHandler {
public:
    GetInvitationsHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

class RejectInvitationsHandler : public TemplateHandler {
public:
    RejectInvitationsHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

class ConfirmInvitationsHandler : public TemplateHandler {
public:
    ConfirmInvitationsHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

class ReportHandler : public TemplateHandler {
public:
    ReportHandler(string file_path, shared_ptr<System> general_system);
    Response* callback(Request*) override;
    CONTEXT handle(Request* req) override;
};

#endif
