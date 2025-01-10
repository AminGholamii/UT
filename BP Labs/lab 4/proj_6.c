#include <stdio.h>

int function (int n){      

    if(n%2 == 0){

        return 1;
    }

    /* If entered number is even , upper condition is true so it returns 1 as the output 
    and then it will break out of the function */
    
    printf("ODD (FARD)!\n");
    
}

int main(){

    int a;
    
    scanf("%d",&a);

    if (function(a)){   

        printf("EVEN (ZOJ)!\n");
    }

    return 0;
}