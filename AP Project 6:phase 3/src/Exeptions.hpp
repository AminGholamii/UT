#ifndef EXEPTIONS_HPP
#define EXEPTIONS_HPP

#include "main.hpp"

class bad_request : public runtime_error {
public:
    bad_request()
        : runtime_error("Bad Request") {}
};

class not_found : public runtime_error {
public:
    not_found()
        : runtime_error("Not Found") {}  
};

class permission_denied : public runtime_error {
public: 
    permission_denied()
        : runtime_error("Permission Denied") {}
};

class overlap : public runtime_error {
public:
    overlap()
        : runtime_error("Overlap") {}
};

class holiday_found : public runtime_error {
public:
    holiday_found()
        : runtime_error("Holiday Found") {}
};

class empty_ : public runtime_error {
public:
    empty_()
        : runtime_error("Empty") {}
};

#endif