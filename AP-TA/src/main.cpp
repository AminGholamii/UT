#include "main.hpp"
#include "command.hpp"

int main(){

    string line;
    string result;
    vector<shared_ptr<Table>> tables;
    while(true){

        if (!getline(cin, line))
            break;

        else if (line.empty())
            continue;

        try{
            result = applyCommand(tables,line);
            if(result.empty())
                continue;
            cout << result << endl;
        }
        catch(exception& ex){
            cout << ex.what() << endl;
        }
        
    }
    return 0;
}