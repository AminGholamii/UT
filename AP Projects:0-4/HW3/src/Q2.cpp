#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

const int ZERO = 0;
typedef list<pair<int,int> > PWP;

////////////////////////////////////////////////////////////////////////////////////////

void getInput(PWP& people_give_prizes, PWP& people_recieved_prizes);
vector<PWP::iterator> lastMinusOne(PWP& people_give_prizes,vector<PWP::iterator>& last_minus,
    PWP::iterator target,PWP::iterator start);
PWP::iterator findMaxAge(PWP::iterator it, PWP::iterator end);
PWP::iterator findMaxAge(PWP& people_give_prizes,PWP::iterator start, PWP::iterator end);
int prizeValue(PWP::iterator target, PWP::iterator it);
void recievePrize(PWP::iterator it, int recieved_prize, int age);
void leaveTable(PWP::iterator target, PWP::iterator it);
bool prevLeft(PWP::iterator target, PWP::iterator it);
bool nextLeft(PWP::iterator target, PWP::iterator it);
bool allLeft(PWP::iterator it, PWP::iterator end);
vector<PWP::iterator> giveToWhom(PWP& people_give_prizes,PWP& people_recieved_prizes, PWP::iterator gifter);
void givePrize(PWP& people_give_prizes,PWP& people_recieved_prizes, PWP::iterator curr);
void printResult(PWP people_recieved_prizes);

/////////////////////////////////////////////////////////////////////////////////////////

int main() {

    PWP people_give_prizes, people_recieved_prizes;
    getInput(people_give_prizes, people_recieved_prizes);
    auto max_age = findMaxAge(people_give_prizes.begin(), people_give_prizes.end());
    givePrize(people_give_prizes, people_recieved_prizes, max_age);
    printResult(people_recieved_prizes);
    return 0;
}

void getInput(PWP& people_give_prizes, PWP& people_recieved_prizes){

    string num_of_family;
    getline(cin, num_of_family);

    vector<int> ordered_ages;
    vector<int> ordered_prizes;

    string ages, person_age;
    getline(cin, ages);
    istringstream strstream(ages);
    while ( getline(strstream, person_age, ' ') )
        ordered_ages.push_back(stoi(person_age));

    string prizes, person_prize;
    getline(cin, prizes);
    istringstream strstream2(prizes);
    while ( getline(strstream2, person_prize, ' ') )
        ordered_prizes.push_back(stoi(person_prize));
    
    for ( int i=0 ; i<stoi(num_of_family) ; i++ ){
        people_give_prizes.push_back({ordered_ages[i], ordered_prizes[i]});
        people_recieved_prizes.push_back({ordered_ages[i],ZERO});
    }
}

vector<PWP::iterator> lastMinusOne(PWP& people_give_prizes,vector<PWP::iterator>& last_minus
    ,PWP::iterator target,PWP::iterator start){

    if ( start->first == target->first )
        return last_minus;
    
    else if ( start->first == -1 && start->first != people_give_prizes.rbegin()->first )
        last_minus.push_back(start);

    return lastMinusOne(people_give_prizes ,last_minus, target, next(start));
}

PWP::iterator findMaxAge(PWP::iterator it, PWP::iterator end){

    if ( it == end )
        return end;
    
    PWP::iterator max_rest = findMaxAge(next(it), end);
    if ( max_rest == end || it->first > max_rest->first )
        return it;
    else 
        return max_rest;
}

PWP::iterator findMaxAge(PWP& people_give_prizes,PWP::iterator start, PWP::iterator end){

    vector<PWP::iterator> lastminus;
    vector<PWP::iterator> last_minus = lastMinusOne(people_give_prizes,lastminus, end, start);

    if ( last_minus.size() != 0 )
        return findMaxAge(next(last_minus[last_minus.size()-1]), end);

    return findMaxAge(start, end);
}

int prizeValue(PWP::iterator target, PWP::iterator it){

    if ( it->first == target->first )
        return it->second;

    return prizeValue(target, next(it));
}

void recievePrize(PWP::iterator it, int recieved_prize, int age){

    if ( it->first == age ){
        it->second += recieved_prize;
        return;
    }
    return recievePrize(next(it), recieved_prize, age);
}

void leaveTable(PWP::iterator target, PWP::iterator it){

    if ( it->first == target->first ){
        it->first = -1;
        return;
    }
    return leaveTable(target, next(it));
}

bool prevLeft(PWP::iterator target, PWP::iterator it){

    if ( it->first == target->first ){
        if ( prev(it)->first == -1 )
            return true;
        return false;
    }
    return prevLeft(target, next(it));
}

bool nextLeft(PWP::iterator target, PWP::iterator it){

    if ( it->first == target->first ){
        if ( next(it)->first == -1 )
            return true;
        return false;
    }
    return nextLeft(target, next(it));
}

bool allLeft(PWP::iterator it, PWP::iterator end){

    if ( it == end )
        return true;
    
    if ( it->first != -1 )
        return false;
    
    return allLeft(next(it), end);
}

vector<PWP::iterator> giveToWhom(PWP& people_give_prizes,PWP& people_recieved_prizes, PWP::iterator gifter){

    PWP::iterator it = people_recieved_prizes.begin();
    PWP::iterator it2 = people_give_prizes.begin();
    vector<PWP::iterator> result;
    int prize = prizeValue(gifter, it2);

    bool cond1 = (gifter->first == people_give_prizes.rbegin()->first);
    bool cond2 = nextLeft(gifter, it2);
    bool cond3 = (gifter->first == people_give_prizes.begin()->first);
    bool cond4 = prevLeft(gifter, it2);

    if ( (cond1 || cond2) && (cond3 || cond4) ){

        recievePrize(it, prize, gifter->first);
        result.push_back(gifter);
        result.push_back(people_recieved_prizes.end());
    }

    else if ( cond1 || cond2 ){

        auto max_age_2nd = findMaxAge(people_give_prizes,people_give_prizes.begin(), gifter);
        recievePrize(it,prize, max_age_2nd->first);
        result.push_back(max_age_2nd);
    }

    else if ( cond3 || cond4 ){

        auto max_age_2nd = findMaxAge(people_give_prizes,next(gifter), people_give_prizes.end());
        recievePrize(it, prize, max_age_2nd->first);
        result.push_back(max_age_2nd);
    }

    else {

        auto max_age_right = findMaxAge(people_give_prizes,next(gifter), people_give_prizes.end());
        auto max_age_left = findMaxAge(people_give_prizes,people_give_prizes.begin(), gifter);
        recievePrize(it,prize/2,max_age_right->first);
        recievePrize(it,prize/2,max_age_left->first);
        result.push_back(max_age_right);
        result.push_back(max_age_left);
    }
    return result;
}

void givePrize(PWP& people_give_prizes,PWP& people_recieved_prizes, PWP::iterator curr){

    if ( allLeft(people_give_prizes.begin(), people_give_prizes.end()) )
        return;

    PWP::iterator it = people_give_prizes.begin();

    vector<PWP::iterator> give_prize_to = giveToWhom(people_give_prizes, people_recieved_prizes, curr);
    leaveTable(curr, it);
    if ( give_prize_to.size() == 2 ){
        if (give_prize_to[1] == people_recieved_prizes.end()) return;
        givePrize(people_give_prizes, people_recieved_prizes, give_prize_to[0]);
        givePrize(people_give_prizes, people_recieved_prizes, give_prize_to[1]);
    }
    else givePrize(people_give_prizes, people_recieved_prizes, give_prize_to[0]);
}

void printResult(PWP people_recieved_prizes){   

    if ( people_recieved_prizes.front() == *(people_recieved_prizes.rbegin()) ){
        cout << people_recieved_prizes.front().second << endl;
        return;
    }
    cout << people_recieved_prizes.front().second << ' ' ;
    people_recieved_prizes.pop_front();
    printResult(people_recieved_prizes);
}

