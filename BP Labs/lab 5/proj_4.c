#include<stdio.h>

int main(){

    int arr[5]={1,2,3,4,5};

    int arr_copy[5];

    // arr_copy = arr;

    return 0;
}

/* Expression must be a modifiable value error . That's bcz when u 
equal two arrays u actually equal the starting address of the arrays and this 
means that if u change one array , other one will be changed too ; But is C 
arrays are not modifiable . Whereas you were willing to make a copy from ur array. */