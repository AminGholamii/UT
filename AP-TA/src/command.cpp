#include "command.hpp"

string applyCommand(vector<shared_ptr<Table>>& tables, string line){
    if (line.rfind(CREATE_TABLE, 0) == 0){
        return createTable(tables, line);
    }
    else if (line.rfind(CREATE_ENHANCED_TABLE, 0) == 0){
        return createEnhancedTable(tables, line);
    }
    else if (line.rfind(DROP_TABLE, 0)== 0){
        return dropTable(tables, line);
    }
    else if (line.rfind(INSERT_INTO, 0) == 0){ 
        return insertRecord(tables, line); 
    }
    else if (line.rfind(UPDATE, 0) == 0){ 
        return updateRecord(tables, line); 
    }
    else if (line.rfind(SELECT, 0) == 0){ 
        return selectRecord(tables, line); 
    }
    else{
        return "";
    }
}

shared_ptr<Table> findTable(const vector<shared_ptr<Table>>& tables, string name){
    for (auto table : tables) 
        if (table->getName() == name)
            return table; 
    return nullptr; 
}

string createTable(vector<shared_ptr<Table>>& tables, string line){

    string result;
    regex main_pattern(R"(create_table\s+(\S+)\s+(.+))");
    smatch match;
    regex_match(line, match, main_pattern);
    string table_name = match[1];
    string fields = match[2];

    if (findTable(tables, table_name) != nullptr){
        throw table_exists();
    }

    vector<string> field_tokens;
    regex field_regex(R"([^;]+)");
    auto begin = std::sregex_iterator(fields.begin(), fields.end(), field_regex);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; it++) {
        field_tokens.push_back(it->str());
    }

    vector<shared_ptr<Column>> columns;
    set<string> names;
    regex col_pattern(R"(\s*(\S+)\s+(\S+)\s+(required|optional)\s*)");
    for (auto& tok : field_tokens) {
        smatch cm;
        regex_match(tok, cm, col_pattern);
        string fname = cm[1];
        string ftype = cm[2];
        string freq = cm[3];

        if (names.count(fname)==1) {
            throw duplicate_field_name();
        }
        names.insert(fname);

        auto col = make_shared<Column>();
        col->name = fname;
        col->type = ftype;
        col->required = (freq == "required");
        columns.push_back(col);
    }

    tables.push_back(make_shared<SimpleTable>(table_name, columns));
    result = "Success: Table " + table_name + " created successfully";
    return result;
}

string createEnhancedTable(vector<shared_ptr<Table>>& tables, string line){

    string result;
    regex main_pattern(R"(create_enhanced_table\s+(\S+)\s+(.+))");
    smatch match;
    regex_match(line, match, main_pattern);

    string table_name = match[1];
    string fields = match[2];

    if (findTable(tables, table_name) != nullptr){
        throw table_exists();
    }

    vector<string> field_tokens;
    regex field_regex(R"([^;]+)");
    auto begin = sregex_iterator(fields.begin(), fields.end(), field_regex);
    auto end = sregex_iterator();
    for (auto it = begin; it != end; it++) {
        field_tokens.push_back(it->str());
    }

    vector<shared_ptr<Column>> columns;
    set<string> names;

    regex col_pattern(R"(\s*(\S+)\s+(\S+)\s+(required|optional)\s*)");
    string main_column;

    for (auto& tok : field_tokens) {
        smatch cm;
        regex_match(tok, cm, col_pattern);

        string fname = cm[1];
        string ftype = cm[2];
        string freq = cm[3];

        if (names.count(fname) == 1) {
            throw duplicate_field_name();
        }
        names.insert(fname);

        auto col = make_shared<Column>();
        col->name = fname;
        col->type = ftype;
        col->required = (freq == "required");
        if (col->required) {
            main_column = fname;  // Assuming only one required field is entered as input
        }
        columns.push_back(col);
    }

    tables.push_back(make_shared<EnhancedTable>(table_name, main_column, columns));
    result = "Success: Table " + table_name + " created successfully";
    return result;
}

string dropTable(vector<shared_ptr<Table>>& tables, string line){

    string result;
    regex pattern(R"(drop_table\s+(\S+))");
    smatch match;
    regex_match(line, match, pattern);

    string table_name = match[1];

    for (auto it = tables.begin(); it != tables.end(); it++) {
        if ((*it)->getName() == table_name) {
            tables.erase(it);
            result = "Success: Table " + table_name + " deleted successfully";
            return result;
        }
    }
    string error = "Error: Table " + table_name + " does not exist";
    throw runtime_error(error);
}

string insertRecord(vector<shared_ptr<Table>>& tables, string line){

    string result;
    regex pattern(R"(insert\s+into\s+(\S+)\s+(.+))");
    smatch match;
    regex_match(line, match, pattern);

    string table_name = match[1];
    string fields_part = match[2];
    auto target = findTable(tables, table_name);
    if(target == nullptr){
        string error = "Error: Table " + table_name + " does not exist";
        throw runtime_error(error);
    }

    vector<string> tokens;
    regex field_regex(R"([^;]+)");
    auto begin = sregex_iterator(fields_part.begin(), fields_part.end(), field_regex);
    auto end = sregex_iterator();
    for (auto it = begin; it != end; ++it)
        tokens.push_back(it->str());

    element row;
    regex assign_pattern(R"(\s*(\S+)\s*:\s*(\S+)\s*)");
    for (auto& tok : tokens){
        smatch m;
        regex_match(tok, m, assign_pattern);
        string fname = m[1];
        string fvalue = m[2];
        row[fname] = fvalue;
    }

    for (auto col : target->getColumns()) {
        if (col->required && row.count(col->name) == 0)
            throw missing_required_field();
    }

    target->insertElement(row);
    result = "Success: Record inserted into table successfully";
    return result;
}

string updateRecord(vector<shared_ptr<Table>>& tables, string line){

    regex pattern(R"(update\s+(\S+)\s+where\s+(\S+)\s*(=|<|!=)\s*(\S+)\s+set\s+(\S+)\s+(\S+))");
    smatch match;
    regex_match(line, match, pattern);

    string table_name = match[1];
    string cond_field = match[2];
    string op = match[3];
    string cond_value = match[4];
    string update_field = match[5];
    string new_value = match[6];

    auto target = findTable(tables, table_name);
    target->updateElement(cond_field, op, cond_value, update_field, new_value);

    string result = "Success: Records updated in table";
    return result;
}

string selectRecord(vector<shared_ptr<Table>>& tables, string line){

    regex pattern(R"(select\s+(\S+)\s+from\s+(\S+)\s+where\s+(\S+)\s*(=|<|!=)\s*(\S+))");
    smatch match;
    regex_match(line, match, pattern);

    string requested = match[1];
    string table_name = match[2];
    string cond_field = match[3];
    string op = match[4];
    string cond_value = match[5];

    vector<string> requested_fields;
    regex field_split(R"([^;]+)");
    auto begin = sregex_iterator(requested.begin(), requested.end(), field_split);
    auto end = sregex_iterator();
    for (auto it = begin; it != end; ++it)
        requested_fields.push_back(it->str());

    auto target = findTable(tables, table_name);
    if (target == nullptr){
        string error = "Error: Table " + table_name + " does not exist";
        throw runtime_error(error);
    }

    auto results = target->selectElements(requested_fields, cond_field, op, cond_value);
    if (results.empty())
        throw no_matching_record();

    ostringstream oss;
    int i=1;
    for (auto [search_value, requested_values] : results){

        oss << i << ". " << requested_values[0];
        if(requested_fields.size()>1){
            for (int j=1 ; j<requested_values.size() ; j++)
                oss << " : " << requested_values[j];
        }
        if (i != results.size())
            oss << '\n';
        i++;
    }

    return oss.str();
}
