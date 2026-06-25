#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "main.hpp"
#include "table.hpp"
#include "exceptions.hpp"
using namespace std;

const string CREATE_TABLE = "create_table";
const string CREATE_ENHANCED_TABLE = "create_enhanced_table";
const string DROP_TABLE = "drop_table";
const string INSERT_INTO = "insert into";
const string UPDATE = "update";
const string SELECT = "select";

string applyCommand(vector<shared_ptr<Table>>& tables, string line);
shared_ptr<Table> findTable(const vector<shared_ptr<Table>>& tables, string name);
string createTable(vector<shared_ptr<Table>>& tables, string line);
string createEnhancedTable(vector<shared_ptr<Table>>& tables, string line);
string dropTable(vector<shared_ptr<Table>>& tables, string line);
string insertRecord(vector<shared_ptr<Table>>& tables, string line);
string updateRecord(vector<shared_ptr<Table>>& tables, string line);
string selectRecord(vector<shared_ptr<Table>>& tables, string line);

#endif //command.hpp