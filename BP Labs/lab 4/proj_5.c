#include <stdio.h>

int function (int n){      

    if(n%2 == 0){

        return 1;
    }

    printf("ODD (FARD)!\n");
    
}

int main(){

    int a;
    
    scanf("%d",&a);

    if (function(a)){   
    
    /* If an even number is entered , it will go through the declared func so the func returns 1 .
    As a result this statement will change to if(1) and as it's always true the next printf command 
    will be executed. */

        printf("EVEN (ZOJ)!\n");
    }

    return 0;
}