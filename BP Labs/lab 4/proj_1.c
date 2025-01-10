#include <stdio.h>

int fact (int n){

    int result = 1;

    for( int i=1 ; i <= n ; i++){

        result *= i ;
    }

    return result;
}

int main(){

    int n;

    scanf("%d",&n);
    printf("%d\n", fact(n) );

    return 0;
}
