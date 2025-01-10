#include<stdio.h>

int main(){

    int num = 5;

    int arr[/*num*/ 5] = {1, 2, 3, 5};    /* int arr[num]*/

    return 0;
}

/* You will recieve error while compiling this . That's bcz you 
cannot initialize a varriable-sized array(obj) while defining it.
Even after changing type of the varriable num to const int , you will 
face the same error as before . It is somehow a restriction in C. */