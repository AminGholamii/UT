#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int FIRST_TERR = 0;
const int LAST_TERR = 9;
const char SEA = '~';
const char MOUNTAIN = '#';
const char PORT = '%';
typedef vector<string> MAP;
typedef vector<vector<int> > VISITED;

void getInput(MAP& main_map){

    int n,m;
    cin >> n >> m;
    getchar();

    for ( int i=0 ; i<n ; i++ ){
        string line;
        getline(cin, line);
        main_map.push_back(line);
    }
}

bool isNextTo(const MAP& main_map, int i, int j, char obj){

    int n = main_map.size();
    int m = main_map[1].size();
    
    if ( i==0 ){

        if ( j==0 ){

            if (main_map[i+1][j] == obj || main_map[i][j+1] == obj){
                return true;
            }
            return false; 
        }

        else if ( j==m-1 ){

            if (main_map[i+1][j] == obj || main_map[i][j-1] == obj){
                return true;
            }
            return false;   
        }

        if (main_map[i+1][j] == obj || main_map[i][j-1] == obj || main_map[i][j+1] == obj){
            return true;
        }
        return false; 
    }

    else if ( i==n-1 ){

        if ( j==0 ){

            if (main_map[i-1][j] == obj || main_map[i][j+1] == obj){
                return true;
            }
            return false; 
        }

        else if ( j==m-1 ){

            if (main_map[i-1][j] == obj || main_map[i][j-1] == obj){
                return true;
            }
            return false;   
        }

        if (main_map[i-1][j] == obj || main_map[i][j-1] == obj || main_map[i][j+1] == obj){
            return true;
        }
        return false; 
    }

    else if ( j==0 ){

        if (main_map[i-1][j] == obj || main_map[i+1][j] == obj || main_map[i][j+1] == obj){
            return true;
        }
        return false; 
    }

    else if ( j==m-1 ){

        if (main_map[i-1][j] == obj || main_map[i][j-1] == obj || main_map[i+1][j] == obj){
            return true;
        }
        return false;   
    }

    if (main_map[i-1][j] == obj || main_map[i][j-1] == obj
         || main_map[i][j+1] == obj || main_map[i+1][j] == obj){
        return true;
    }
    return false;
}

bool isWaterWay(const MAP& main_map, int i1, int j1, int i2, int j2){

    if ( isNextTo(main_map, i1, j1, PORT) && isNextTo(main_map, i2, j2, PORT) ){

        while ( i1!=i2 && j1!=j2 ){

            if ( isNextTo(main_map, i1, j1, SEA))
        }
    }

    return false;
}

int findMaxTerr(const MAP& main_map, VISITED& visited, int empire, int i, int j){

    int n = main_map.size();
    int m = main_map[1].size();

    if ( i==n || i<0 || j==m || j<0)
        return 0;
    
    if (visited[i][j])
        return 0;
    
    char area = main_map[i][j];
    int area_num = int(area)-48;
    if ( area == MOUNTAIN )
        return 0;

    if ( area_num>=FIRST_TERR && area_num<=LAST_TERR && area_num!=empire )
        return 0;

    visited[i][j] = 1;
    int count=0;
    if (area_num == empire){
        count=1;
    }
    
    count += findMaxTerr(main_map, visited, empire, i-1, j);
    count += findMaxTerr(main_map, visited, empire, i+1, j);
    count += findMaxTerr(main_map, visited, empire, i, j+1);
    count += findMaxTerr(main_map, visited, empire, i, j-1);

    return count;
}

int BiggestEmpireTerr(const MAP& main_map, VISITED& visited, int empire, int i=0 , int j=0 ){
    
    int n = main_map.size();
    int m = main_map[1].size();

    if ( i == n )
        return 0;

    if ( j == m )
        return BiggestEmpireTerr(main_map, visited, empire, i+1, 0);

    int max_territory = 0;

    if ( main_map[i][j]==char(empire+48) && !visited[i][j] )
        max_territory = findMaxTerr(main_map, visited, empire, i, j);
    
    int next_max = BiggestEmpireTerr(main_map, visited, empire, i, j+1);
    return max(max_territory, next_max);
}

int BiggestEmpireTerr(const MAP& main_map, char empire){

    int n = main_map.size();
    int m = main_map[1].size();

    VISITED visited(n , vector<int>(m,0));
    return BiggestEmpireTerr(main_map, visited, empire);
}

void BiggestEmpiresTerrs(const MAP& main_map, vector<int>& biggest_terrs, int empire=0){

    if ( empire > LAST_TERR )
        return;
    
    biggest_terrs.push_back(BiggestEmpireTerr(main_map, empire));
    return BiggestEmpiresTerrs(main_map, biggest_terrs, ++empire);
}

void printResult(vector<int> biggest_terrs){

    if ( biggest_terrs.empty() )
        return;
    
    cout << biggest_terrs.front() << endl;
    biggest_terrs.erase(biggest_terrs.begin());
    return printResult(biggest_terrs);
}

int main() {

    MAP main_map;
    getInput(main_map);

    vector<int> biggest_terrs;
    BiggestEmpiresTerrs(main_map, biggest_terrs);

    printResult(biggest_terrs);
    return 0;
}
