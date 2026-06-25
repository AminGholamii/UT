#ifndef TABLE_HPP
#define TABLE_HPP

#include "main.hpp"
#include "exceptions.hpp"
using namespace std;

typedef map<string, string> element;

struct Column{
    string name;
    string type;
    bool required;
};

class Table{
protected:
    string name;
    vector<shared_ptr<Column>> columns;

public:
    Table(string name, const vector<shared_ptr<Column>>& columns) 
        : name(name), columns(columns) {}

    string getName() const { return name; }
    vector<shared_ptr<Column>> getColumns() const { return columns; }

    virtual bool isEnhanced() const = 0;
    virtual void insertElement (element& elem) = 0;
    virtual void updateElement(string cond_field, string op, string cond_value, string update_field, string new_value) = 0;
    virtual vector<pair<string, vector<string>>> selectElements(vector<string>& requested_fields, string cond_field, string op, string cond_value) = 0;
};

class SimpleTable : public Table{
private:
    vector<element> elements;
public:
    SimpleTable(string name, const vector<shared_ptr<Column>>& columns) 
        : Table(name, columns) {}
    bool isEnhanced() const override { return false; }
    void insertElement(element& elem) override;
    void updateElement(string cond_field, string op, string cond_value, string update_field, string new_value) override;
    vector<pair<string, vector<string>>> selectElements(vector<string>& requested_fields, string cond_field, string op, string cond_value) override;
};

class EnhancedTable : public Table{
private:
    string main_column;
    map<string, element> elements;

public:
    EnhancedTable(string name, string main_column, const vector<shared_ptr<Column>>& columns)
        : Table(name, columns), main_column(main_column) {}

    bool isEnhanced() const override { return true; }
    void insertElement(element& elem) override;
    void updateElement(string cond_field, string op, string cond_value, string update_field, string new_value) override;
    vector<pair<string, vector<string>>> selectElements(vector<string>& requested_fields, string cond_field, string op, string cond_value) override;
};

bool validValue(string value, string cond_value, string op);

#endif //table.hpp