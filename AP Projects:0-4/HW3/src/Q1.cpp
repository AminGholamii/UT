#include <iostream>
#include <string>
using namespace std;

const string FRAC = "\\frac";
const string ONE = "1";


string laTex(int n,int before_frac){

    string result;

    int numerator = 2*before_frac ;
    int denominator = 2*before_frac+1;
    
    if ( n == 2 ){
        result = "+" + FRAC + "{" + to_string(numerator) + "}{" + to_string(denominator) + "}";
        return result;
    }
    result = "+" + FRAC + "{" + to_string(numerator) + laTex(n-1,numerator) + "}{" + to_string(denominator) + laTex(n-1,denominator) + "}"; 
    return result;
}

string laTex(int n){

    if ( n == 1 )
        return ONE;
    
    else 
        return ONE+laTex(n,1);
}

int main() {
    
    int n;
    cin >> n;

    string result = laTex(n);
    cout << result << endl;

    return 0;
}
