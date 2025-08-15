#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const double TAX_RATE = 1.1;
enum TypeIndex{NUM=0 , DISC=1 , LEAST=2 , MAX=3};

struct FoodsWithPrices{

    string name;
    int price;
};
typedef vector<FoodsWithPrices> FWP;
typedef vector<string> Scenario;
typedef vector<vector<string> > Scenarios;

////////////////////////////////////////////////////////////////////////////////////////////////////

void getInput(FWP& foods_with_prices, vector<int>& rules);
int findPrice(FWP foods_prices, string food_name, int i=0);
int priceCalculator(FWP foods_prices, Scenario sce, int& price, int i=0);
bool canBuy(FWP foods_prices, Scenario sce, vector<int> rules);
void allFoods(FWP foods_prices, vector<string>& all_foods, int i=0);
void findSubsets(vector<string>::iterator first, vector<string>::iterator last,
    Scenarios& all_subs, vector<string> subset={});
void findallScenarios(Scenarios& all_sce, Scenarios all_subs, FWP foods_prices, vector<int> rules);
void ScenariosPrices(FWP foods_prices, Scenarios all_sce, vector<int>& prices);
int findIdx(vector<int> prices, int max_price, int i=0);
Scenario findBestScenario(FWP foods_prices, Scenarios all_sce);
void printResult(Scenario result);

////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

    FWP foods_prices;
    vector<int> rules;
    getInput(foods_prices,rules);

    vector<string> all_foods;
    allFoods(foods_prices, all_foods);
    Scenarios all_subs, all_sce;
    findSubsets(all_foods.begin(), all_foods.end(), all_subs);
    findallScenarios(all_sce, all_subs, foods_prices, rules);

    Scenario best_scenario = findBestScenario(foods_prices, all_sce);
    printResult(best_scenario);

    return 0;
}

void getInput(FWP& foods_with_prices, vector<int>& rules){

    int num_of_foods, discount_per, least_purchase, max_discount;
    cin >> num_of_foods >> discount_per >> least_purchase >> max_discount;
    getchar();
    rules.push_back(num_of_foods);
    rules.push_back(discount_per);
    rules.push_back(least_purchase);
    rules.push_back(max_discount);

    for ( int i=0 ; i<num_of_foods ; i++ ){

        string line;
        getline(cin, line);
        istringstream strstream(line);
        string food_name;
        strstream >> food_name;
        int price;
        strstream >> price;
        foods_with_prices.push_back({food_name,price});
    }
}

int findPrice(FWP foods_prices, string food_name, int i){

    if ( foods_prices[i].name == food_name ) 
        return foods_prices[i].price;
    
    return findPrice(foods_prices, food_name, ++i);
}

int priceCalculator(FWP foods_prices, Scenario sce, int& price, int i){

    if ( i == sce.size() ) 
        return price;
    
    price += findPrice(foods_prices, sce[i]);
    return priceCalculator(foods_prices, sce, price, ++i);
}

bool canBuy(FWP foods_prices, Scenario sce, vector<int> rules){

    int price = 0;
    float main_price = priceCalculator(foods_prices, sce, price) * TAX_RATE;
    bool cond1 = ( main_price >= rules[LEAST] );
    bool cond2 = ( (main_price*(rules[DISC]/100.0)) <= rules[MAX] );
    if ( cond1 && cond2 )
        return true;
    return false;
}

void allFoods(FWP foods_prices, vector<string>& all_foods, int i){

    if ( i == foods_prices.size() )
        return;
    
    all_foods.push_back(foods_prices[i].name);
    allFoods(foods_prices, all_foods, ++i);
}

void findSubsets(vector<string>::iterator first, vector<string>::iterator last,
    Scenarios& all_subs, vector<string> subset) {

    if (first == last){
        all_subs.push_back(subset);
        return;
    }
    subset.push_back(*first);
    findSubsets(next(first), last, all_subs, subset);
    subset.pop_back();
    findSubsets(next(first), last, all_subs, subset);
}

void findallScenarios(Scenarios& all_sce, Scenarios all_subs, FWP foods_prices, vector<int> rules){

    if ( all_subs.empty() ) return;

    else if ( all_subs.front().empty() ) ;
    
    else if ( canBuy(foods_prices, all_subs.front(), rules) )
        all_sce.push_back(all_subs.front());

    all_subs.erase(all_subs.begin());
    return findallScenarios(all_sce, all_subs, foods_prices, rules);
}

void ScenariosPrices(FWP foods_prices, Scenarios all_sce, vector<int>& prices){

    if ( all_sce.empty() ) return;
    
    int price = 0;
    priceCalculator(foods_prices, all_sce.front(), price);
    prices.push_back(price);
    all_sce.erase(all_sce.begin());
    return ScenariosPrices(foods_prices, all_sce, prices);
}

int findIdx(vector<int> prices, int max_price, int i){

    if ( prices[i] == max_price )
        return i;
    
    return findIdx(prices, max_price, ++i);
}

Scenario findBestScenario(FWP foods_prices, Scenarios all_sce){

    if ( all_sce.empty() ) 
        return {};

    vector<int> prices;
    ScenariosPrices(foods_prices, all_sce, prices);
    vector<int>::iterator max_it = max_element(prices.begin(), prices.end());
    int max_idx = findIdx(prices, *max_it);
    return all_sce[max_idx];
}

void printResult(Scenario result){

    if ( result.empty() )
        return;

    cout << result.front() << endl;
    result.erase(result.begin());
    return printResult(result);
}


