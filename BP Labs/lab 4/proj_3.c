#include <stdio.h>

int function (int n){      /* n is just an entry argument of the function . */

    if(n%2 == 0){

        return 1;
    }

    printf("ODD (FARD)!\n");
}

int main(){

    int a;
    
    scanf("%d",&a);

    if (function(a)){   /* function can be called with any favourite argument.*/

        printf("EVEN (ZOJ)!\n");
    }

    return 0;
}