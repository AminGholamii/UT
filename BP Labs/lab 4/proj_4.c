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
    
    /* As we have a returning integer in function , It is permissable to call the function in the if-condition
    In this case , compiler will call the declared function in the condition ; If the function returns sth it will go
    through the condition . */

        printf("EVEN (ZOJ)!\n");
    }

    return 0;
}