#include "table.hpp"

void SimpleTable::insertElement(element& elem){
    elements.push_back(elem);
}

void EnhancedTable::insertElement(element& elem){
    string key = elem[main_column];
    if (elements.count(key))
        throw duplicate_main_column_value();
    elements[key] = elem; 
}

bool validValue(string value, string cond_value, string op){

    bool valid = false;
    if (op == "=")
        valid = (stoi(value) == stoi(cond_value));
    else if (op == "<")
        valid = (stoi(value) < stoi(cond_value));
    else if (op == "!=")
        valid = (stoi(value) != stoi(cond_value));

    return valid;
}

void SimpleTable::updateElement(string cond_field, string op, string cond_value, string update_field, string new_value){

    for (auto& row : elements) {
        string value = row[cond_field];
        bool valid = validValue(value, cond_value, op);
        if (valid)
            row[update_field] = new_value;
    }
}

void EnhancedTable::updateElement(string cond_field, string op, string cond_value, string update_field, string new_value){

    for (auto& [key, row] : elements) {
        string value = row[main_column];
        bool valid = validValue(value, cond_value, op);
        if (valid)
            row[update_field] = new_value;
    }
}

vector<pair<string, vector<string>>> SimpleTable::selectElements(vector<string>& requested_fields, string cond_field, string op, string cond_value){

    vector<pair<string, vector<string>>> result;
    for (auto& row : elements) {
        string value = row[cond_field];
        bool valid = validValue(value, cond_value, op);
        if (valid) {
            vector<string> req_values;
            for (auto& req : requested_fields){
                req_values.push_back(row[req]);
            }
            result.push_back({value, req_values});
        }
    }
    return result;
}

vector<pair<string, vector<string>>> EnhancedTable::selectElements(vector<string>& requested_fields, string cond_field, string op, string cond_value){

    vector<pair<string, vector<string>>> result;
    for (auto& [key, row] : elements) {
        string value = row[main_column];
        bool valid = validValue(value, cond_value, op);
        if (valid) {
            vector<string> req_values;
            for (auto& req : requested_fields){
                req_values.push_back(row[req]);
            }
            result.push_back({value, req_values});
        }
    }
    return result;
}
