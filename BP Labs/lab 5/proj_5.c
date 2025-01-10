#include<stdio.h>

int main(){

    int arr[5]={1,2,3,4,5};

    int arr_copy[5];

    for ( int i=0 ; i<5 ; i++){

        arr_copy[i] = arr[i];
    }

    return 0;
}