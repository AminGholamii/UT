#ifndef EXEPTIONS_HPP
#define EXEPTIONS_HPP

#include "main.hpp"

class table_exists : public runtime_error {
public:
    table_exists()
        : runtime_error("Error: A table with this name already exists") {}
};

class duplicate_field_name : public runtime_error {
public:
    duplicate_field_name()
        : runtime_error("Error: Duplicate field name in table definition") {}  
};

class duplicate_main_column_value : public runtime_error {
public:
    duplicate_main_column_value()
        : runtime_error("Error: Duplicate value for required field") {}  
};

class missing_required_field : public runtime_error {
public:
    missing_required_field()
        : runtime_error("Error: Missing value for required field") {}  
};

class no_matching_record : public runtime_error {
public:
    no_matching_record()
        : runtime_error("Error: No matching records found") {}  
};

#endif //exeptions.hpp