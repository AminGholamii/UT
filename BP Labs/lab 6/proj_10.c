#include <stdio.h>
#define SIZE 10
void function(float arr[10]);


void function(float arr[10]){

    for ( int i = 0 ; i < SIZE ; i++){

        arr[i] = (int)arr[i] % 2;
    }
}

int main(){

    float arr[SIZE]={1,2,3,4,5,6,7,8,9,10};

    function(arr);
    
    for(int j=0;j<SIZE;j++){

        printf("%f ",arr[j]);
    }

    return 0;
}