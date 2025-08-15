#include "main.hpp"
#include "Date.hpp"
#include "Functions.hpp"
#include "System.hpp"
#include "../server/server.hpp"
#include "handlers.hpp"

void mapServerPaths(Server& server, shared_ptr<System> general_system) {

    server.get("/css/404.css", new ShowPage("css/404.css"));
    server.get("/css/home.css", new ShowPage("css/home.css"));
    server.get("/css/signup.css", new ShowPage("css/signup.css"));
    server.get("/css/login.css", new ShowPage("css/login.css"));
    server.get("/css/dashboard.css", new ShowPage("css/dashboard.css"));
    server.get("/css/task.css", new ShowPage("css/task.css"));
    server.get("/css/event.css", new ShowPage("css/event.css"));
    server.get("/css/get-invitations.css", new ShowPage("css/get-invitations.css"));
    server.get("/css/confirm-reject.css", new ShowPage("css/confirm-reject.css"));
    server.get("/css/report.css", new ShowPage("css/report.css"));

    server.setNotFoundErrPage("html/404.html");
    server.get("/", new ShowPage("html/home.html"));
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get("/signup", new ShowPage("html/signup.html"));
    server.get("/login", new ShowPage("html/login.html"));
    server.get("/dashboard", new dashboardHandler("template/dashboard.html", general_system));
    server.get("/add-task", new ShowPage("html/add-task.html"));
    server.get("/edit-task", new ShowPage("html/edit-task.html"));
    server.get("/delete-task", new ShowPage("html/delete-task.html"));
    server.get("/normal-event", new ShowPage("html/normal-event.html"));
    server.get("/weekly-event", new ShowPage("html/weekly-event.html"));
    server.get("/add-join-event", new ShowPage("html/add-join-event.html"));
    server.get("/get-invitations", new GetInvitationsHandler("template/get-invitations.html", general_system));
    server.get("/reject-invitation", new ShowPage("html/reject-invitation.html"));
    server.get("/confirm-invitation", new ShowPage("html/confirm-invitation.html"));
    server.get("/report", new ShowPage("html/report.html"));
    
    server.post("/signup", new SignUpHandler("template/signup.html", general_system));
    server.post("/login", new LoginHandler("template/login.html", general_system));
    server.post("/logout", new LogoutHandler(general_system));
    server.post("/add-task", new AddTaskHandler("template/add-task.html", general_system));
    server.post("/edit-task", new EditTaskHandler("template/edit-task.html", general_system));
    server.post("/delete-task", new DeleteTaskHandler("template/delete-task.html", general_system));
    server.post("/normal-event", new AddNormalEventHandler("template/normal-event.html", general_system));
    server.post("/weekly-event", new AddPeriodicEventHandler("template/weekly-event.html", general_system));
    server.post("/add-join-event", new AddJoinEventHandler("template/add-join-event.html", general_system));
    server.post("/reject-invitation", new RejectInvitationsHandler("template/reject-invitation.html", general_system));
    server.post("/confirm-invitation", new ConfirmInvitationsHandler("template/confirm-invitation.html", general_system));
    server.post("/report", new ReportHandler("template/report.html", general_system));
}

int main(int argc, char* argv[]) {

    try {

        vector<shared_ptr<Date> > holidays;
        int port = 5000;
        if ( argc == 3 ){
            port = stoi(argv[1]);
            readHolidays(holidays, argv[2]);
        }
        else{
            readHolidays(holidays, argv[1]);
        }

        shared_ptr<System> general_system = make_shared<System>();
        general_system->setHolidays(holidays);
        Server server(port);
        mapServerPaths(server, general_system);
        cout << "Server running on port: " << port << endl;
        server.run();
    }

    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }

    catch (const Server::Exception& e) {
        cout << e.getMessage() << endl;
    }
    
    return 0;
}
