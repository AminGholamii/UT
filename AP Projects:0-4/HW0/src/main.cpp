#include <iostream>
#include <string>
#define MAX_LEN 100
using namespace std;

string encryptText(string text, int k){

    char result[MAX_LEN];
    int i;

    for(i=0 ; text[i] != '\0' ; i++){

        int temp = (int)text[i];   // temp is the ASCII code of text[i]

        if ( temp == 32 ){  // if text[i] == ' ' 

            result[i] = ' ';
            continue;
        }

        if ( temp >= 65 && temp <= 90 ){ 

            if ( (temp + k) <= 90 ){
                
                result[i] = (char)temp+k ;
                continue;
            }
            else{

                result[i] = (char)(64 + (temp+k-90));
                continue;
            }
        }

        if ( temp >= 97 && temp <= 122 ){

            if ( (temp+k) <= 122 ){

                result[i] = (char)temp+k ;
                continue;
            }
            else{

                result[i] = (char)(96 + (temp+k-122));
                continue;
            }
        }
    }
    result[i] = '\0';
    return result;
}

string decryptText(string text, int k){

    char result[MAX_LEN];
    int i;

    for(i=0 ; text[i] != '\0' ; i++){

        int temp = (int)text[i];

        if ( temp == 32 ){   

            result[i] = ' ';
            continue;
        }

        if ( temp >= 65 && temp <= 90 ){

            if ( (temp-k) >= 65 ){

                result[i] = (char)temp-k ;
                continue;
            }
            else{
                
                result[i] = (char)( 91 - (65-(temp-k)) );
                continue;
            }
        }

        if ( temp >= 97 && temp <= 122 ){

            if ( (temp-k) >= 97 ){

                result[i] = (char)temp-k ;
                continue;
            }
            else{

                result[i] = (char)( 123 - (97-(temp-k)) );
                continue;
            }
        }
    }
    result[i] = '\0';
    return result;
}


int main(){

    char text[MAX_LEN];
    cin.getline(text, MAX_LEN);  // Using getline beacuse may space exist in the text 

    int key; 
    string command;
    cin >> key;
    cin >> command;

    if (command == "Encrypt"){

        cout << encryptText(text, key) << endl;
    }

    else if(command == "Decrypt"){

        cout << decryptText(text, key) << endl;
    }
    
    return 0;
}