#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum TYPE_BONUS{ WINDOW_BONUS = 6 , DOOR_BONUS = 4 , MIDDLE_BONUS = 2};
#define WINDOW "window"
#define DOOR "door"
#define MIDDLE "middle"

#define SHOW_TABLE_INFO "show_table_info"
#define ENTER "enter"
#define RESERVE_TABLE "reserve_table"
#define EXIT "exit"
#define SWITCH "switch"

struct tableSpecs{

    int ID;
    int X;
    int Y;
    int Capacity;
    string Type;
    vector<string> people_at_table;
    vector<int> people_at_queue;
    int remaining_capacity;
};

struct stdsSpecs{

    int ID;
    string Name;
    int Friend_ID;
    int Enemy_ID;
    tableSpecs *currently_in;
};

typedef vector<tableSpecs> TABLES;
typedef vector<stdsSpecs> STDS;

/////////////////////////////////////////////////////////////////////////////////

void readTablesFile(string path_to_tables_file, TABLES& tables_specs);
void readStdsFile(string path_to_stds_file, STDS& stds_specs);
pair<string,string> asciiCmp(string first, string second);
void bubbleSort(vector<string>& vec);
void showTableInfo(TABLES& tables_specs, int id);
stdsSpecs* findStd(int std_id, STDS& stds_specs);
tableSpecs* findTable(int table_id, TABLES& tables_specs);
int scoreCalculator(tableSpecs table, int std_id, STDS& stds_specs);
vector<pair<tableSpecs, int> > sortByScore(const TABLES& table_specs, STDS& stds_specs, int std_id);
void enterStd(const TABLES& table_specs, STDS& stds_specs, int std_id);
void reserveTable(TABLES& table_specs, STDS& stds_specs, int std_id);
void exitStd(TABLES& tables_specs, STDS& stds_specs, int std_id);
void switchStd(TABLES& tables_specs,STDS& stds_specs, int std_id);
bool getAndApplyCommand(TABLES& tables_specs,STDS& stds_specs);

//////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {

    TABLES tables_specs;
    STDS stds_specs;

    readTablesFile(argv[1], tables_specs);
    readStdsFile(argv[2], stds_specs);

    while( getAndApplyCommand(tables_specs, stds_specs) ) ;

    return 0;
}

bool getAndApplyCommand(TABLES& tables_specs,STDS& stds_specs){

    string command;
    cin >> command;

    if ( cin.eof() )
        return false;

    if ( command == SHOW_TABLE_INFO ){

        int table_id;
        cin >> table_id;
        showTableInfo(tables_specs, table_id);
    }

    else if ( command == ENTER ){

        int std_id;
        cin >> std_id;
        enterStd(tables_specs, stds_specs, std_id);
    }

    else if ( command == RESERVE_TABLE ){

        int std_id;
        cin >> std_id;
        reserveTable(tables_specs, stds_specs, std_id);
    }

    else if ( command == EXIT ){

        int std_id;
        cin >> std_id;
        exitStd(tables_specs, stds_specs, std_id);
    }

    else if ( command == SWITCH ){

        int std_id;
        cin >> std_id;
        switchStd(tables_specs, stds_specs, std_id);
    }

    return true;
}

void readTablesFile(string path_to_tables_file, TABLES& tables_specs){

    ifstream tables_file(path_to_tables_file);
    string each_line , element;
    getline(tables_file, each_line);

    while ( getline(tables_file, each_line) ){

        tableSpecs new_table;
        istringstream strstream(each_line);
        int i=0;
        while ( getline(strstream, element, ',') ){

            switch(i){
                case 0:
                    new_table.ID = stoi(element);
                    break;

                case 1:
                    new_table.X = stoi(element);
                    break;
                
                case 2:
                    new_table.Y = stoi(element);
                    break;
                
                case 3:
                    new_table.Capacity = stoi(element);
                    new_table.remaining_capacity = new_table.Capacity;
                    break;
                
                case 4:
                    new_table.Type = element;
                    break;
            }
            i++;
        }
        tables_specs.push_back(new_table);
    }
}

void readStdsFile(string path_to_stds_file, STDS& stds_specs){

    ifstream stds_file(path_to_stds_file);
    string each_line , element;
    getline(stds_file, each_line);

    while ( getline(stds_file, each_line) ){

        stdsSpecs new_std;
        istringstream strstream(each_line);
        int j=0;
        while ( getline(strstream, element, ',') ){

            switch(j){

                case 0:
                    new_std.ID = stoi(element);
                    break;
                
                case 1:
                    new_std.Name = element;
                    break;
                
                case 2:
                    new_std.Friend_ID = stoi(element);
                    break;
                
                case 3:
                    new_std.Enemy_ID = stoi(element);
                    break;
            }
            j++;
        }
        new_std.currently_in = NULL;
        stds_specs.push_back(new_std);
    }
}

pair<string,string> asciiCmp(string first, string second){

    if ( first.length() >= second.length() ){

        for ( int i=0 ; i<second.length() ; i++ ){

            if ( first[i] < second[i] )
                return {first,second};

            else if ( second[i] < first[i] )
                return {second,first};
        }
        return {second,first};
    }

    else{

        for ( int i=0 ; i<first.length() ; i++ ){

            if ( first[i] < second[i] )
                return {first,second};
            
            else if ( second[i] < first[i] )
                return {second,first};
        }
        return {first,second};
    }
}

void bubbleSort(vector<string>& vec){

    int size = vec.size();
    for ( int i=0 ; i<size-1 ; i++ ){

        for ( int j=0 ; j<size-i-1 ; j++ ){

            pair<string,string> cmp_result = asciiCmp(vec[j],vec[j+1]);
            vec[j] = cmp_result.first;
            vec[j+1] = cmp_result.second;
        }
    }
}

void showTableInfo(TABLES& tables_specs, int id){

    for ( auto table : tables_specs ){
        if ( table.ID == id ){
            cout << "Table ID: " << id << '\n';
            cout << "People at the table: ";

            if ( table.people_at_table.size() != 0 ) {

                bubbleSort(table.people_at_table);
                int i;
                for ( i=0 ; i<(table.people_at_table.size())-1 ; i++){
                    cout << table.people_at_table[i] << ", ";
                }
                cout << table.people_at_table[i];
            }
            cout << "\nTable remaining capacity: " << table.remaining_capacity << '\n';
            cout << "Waiting queue length: " << table.people_at_queue.size() << endl;
            return;
        }
    }
}

stdsSpecs* findStd(int std_id, STDS& stds_specs){

    int i;
    for (i=0 ; i<stds_specs.size() ; i++){

        if ( stds_specs[i].ID == std_id )
            return &stds_specs[i];
    }
    return &stds_specs[i];
}

tableSpecs* findTable(int table_id, TABLES& tables_specs){

    int i;
    for ( i=0 ; i < tables_specs.size() ; i++ ){

        if ( tables_specs[i].ID == table_id )
            return &tables_specs[i];
    }
    return &tables_specs[i];
}

int scoreCalculator(tableSpecs table, int std_id, STDS& stds_specs){

    int score = 0, distance_to_enemy = 0, distance_to_friend = 0;

    stdsSpecs* curr_std = findStd(std_id, stds_specs);
    stdsSpecs* std_enemy = findStd(curr_std->Enemy_ID, stds_specs);
    stdsSpecs* std_friend = findStd(curr_std->Friend_ID, stds_specs);

    if ( std_enemy->currently_in != NULL ){

        int delta_x = abs(table.X - (std_enemy->currently_in->X));
        int delta_y = abs(table.Y - (std_enemy->currently_in->Y));
        distance_to_enemy = delta_x + delta_y;
    }

    if ( std_friend->currently_in != NULL ){

        int delta_x = abs(table.X - (std_friend->currently_in->X));
        int delta_y = abs(table.Y - (std_friend->currently_in->Y));
        distance_to_friend = delta_x + delta_y;
    }

    score += distance_to_enemy - distance_to_friend;
    if ( table.Type == WINDOW ){
        score += WINDOW_BONUS;
    }
    else if ( table.Type == DOOR ){
        score += DOOR_BONUS;
    }
    else if ( table.Type == MIDDLE ){
        score += MIDDLE_BONUS;
    }
    return score;
}

vector<pair<tableSpecs, int> > sortByScore(const TABLES& table_specs, STDS& stds_specs,
    int std_id) { 

    vector< pair<tableSpecs, int> > wanna_sort; 
    for ( auto table : table_specs ){
        pair<tableSpecs, int> temp_pair = {table, scoreCalculator(table, std_id, stds_specs)};
        wanna_sort.push_back(temp_pair);
    }

    sort( wanna_sort.begin(), wanna_sort.end(),
        [](pair<tableSpecs, int> a, pair<tableSpecs, int> b) {return b.second < a.second;} ); 

    
    for ( int i=0 ; i<wanna_sort.size() ; i++ ){

        if ( wanna_sort[i].second == wanna_sort[i+1].second ){

            if(wanna_sort[i].first.ID > wanna_sort[i+1].first.ID){
                pair<tableSpecs, int> temp;
                temp = wanna_sort[i];
                wanna_sort[i] = wanna_sort[i+1];
                wanna_sort[i+1] = temp;
            }
        }
    }
    return wanna_sort;
} 

void enterStd(const TABLES& table_specs, STDS& stds_specs, int std_id){

    vector< pair<tableSpecs, int> > sorted_tables = sortByScore(table_specs, stds_specs, std_id);

    for ( auto each_pair : sorted_tables ){
        
        tableSpecs table = each_pair.first;
        int score = each_pair.second;
        cout << "Table " << table.ID << ": " << table.remaining_capacity 
             << ' ' << table.people_at_queue.size() << endl ;
    }
}

void reserveTable(TABLES& table_specs, STDS& stds_specs, int std_id){

    stdsSpecs* curr_std = findStd(std_id, stds_specs);
    char anything_else = getchar();

    if ( anything_else != '\n' ){

        int table_id;
        cin >> table_id;
        tableSpecs* curr_table = findTable(table_id, table_specs);

        if ( curr_table->remaining_capacity > 0 ){

            (curr_table->people_at_table).push_back(curr_std->Name);
            curr_table->remaining_capacity--;
            curr_std->currently_in = curr_table;
            cout << curr_std->Name << " sits at table " << table_id << endl;
        }

        else{
            (curr_table->people_at_queue).push_back(std_id);
            cout << curr_std->Name << " enters the waiting queue of table " << table_id << endl;
        }
    }

    else if (anything_else == '\n'){

        tableSpecs _best_table = sortByScore(table_specs, stds_specs, std_id)[0].first;
        tableSpecs* best_table = findTable(_best_table.ID, table_specs);

        if ( best_table->remaining_capacity > 0 ){

            (best_table->people_at_table).push_back(curr_std->Name);
            best_table->remaining_capacity--;
            curr_std->currently_in = best_table;
            cout << curr_std->Name << " sits at table " << best_table->ID << endl;
        }

        else{
            (best_table->people_at_queue).push_back(std_id);
            cout << curr_std->Name << " enters the waiting queue of table " << best_table->ID << endl;
        }
    }
}

void exitStd(TABLES& tables_specs, STDS& stds_specs, int std_id){

    stdsSpecs* curr_std = findStd(std_id, stds_specs);
    tableSpecs* curr_table = curr_std->currently_in;

    vector<string>::iterator pos = find(curr_table->people_at_table.begin(),curr_table->people_at_table.end(),curr_std->Name);
    curr_table->people_at_table.erase(pos);
    int remained_cap = 1;

    if ( curr_table->people_at_queue.size() != 0 ){

        stdsSpecs* from_queue;

        vector<int>::iterator friend_it = find(curr_table->people_at_queue.begin(),
                        curr_table->people_at_queue.end(),curr_std->Friend_ID);
        
        bool is_friend_in = (friend_it != curr_table->people_at_queue.end());

        if (is_friend_in){
            from_queue = findStd(curr_std->Friend_ID, stds_specs);
            curr_table->people_at_table.push_back(from_queue->Name);
            from_queue->currently_in = curr_table;
            curr_table->people_at_queue.erase(friend_it);
        }
        else{
            from_queue = findStd(curr_table->people_at_queue[0], stds_specs);
            curr_table->people_at_table.push_back(from_queue->Name);
            from_queue->currently_in = curr_table;
            curr_table->people_at_queue.erase(curr_table->people_at_queue.begin());
        }
        remained_cap = 0;
    }

    if ( remained_cap ){
        curr_table->remaining_capacity++;
    }
    curr_std->currently_in = NULL;
    cout << curr_std->Name << " exits!" << endl;
}

void switchStd(TABLES& tables_specs,STDS& stds_specs, int std_id){

    stdsSpecs* curr_std = findStd(std_id,stds_specs);
    tableSpecs* curr_table = curr_std->currently_in;
    stdsSpecs* friend_of_curr = findStd(curr_std->Friend_ID, stds_specs);
    tableSpecs* friend_table = friend_of_curr->currently_in;

    vector<string>::iterator pos_curr = find(curr_table->people_at_table.begin(),
                    curr_table->people_at_table.end(), curr_std->Name);
    vector<string>::iterator pos_friend = find(friend_table->people_at_table.begin(),
                    friend_table->people_at_table.end(), friend_of_curr->Name);

    curr_table->people_at_table.erase(pos_curr);
    friend_table->people_at_table.erase(pos_friend);

    curr_table->people_at_table.push_back(friend_of_curr->Name);
    friend_of_curr->currently_in = curr_table;
    friend_table->people_at_table.push_back(curr_std->Name);
    curr_std->currently_in = friend_table;

    cout << curr_std->Name << " switches seats with " << friend_of_curr->Name << "!" << endl;
}


