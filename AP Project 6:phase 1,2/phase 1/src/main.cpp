#include "main.hpp"
#include "Date.hpp"
#include "Functions.hpp"
#include "System.hpp"

int main(int argc, char* argv[]) {

    vector<shared_ptr<Date> > holidays;
    readHolidays(holidays, argv[1]);

    System general_system;
    general_system.setHolidays(holidays);
    general_system.run();
    
    return 0;
}
