#include <stdio.h>

void fact (int n){

    int result = 1;

    for( int i=1 ; i <= n ; i++){

        result *= i ;
    }

    printf("%d\n", result);
}

int main(){

    int n;

    scanf("%d",&n);
    
    fact(n) ;

    return 0;
}
