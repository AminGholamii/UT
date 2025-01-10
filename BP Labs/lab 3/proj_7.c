#include <stdio.h>

int main(){

    int n;
    int value =1;

    while (value){

        scanf("%d",&n);

        ( n == 0) ? ( value = 0 ) : (printf("%d\n",n));

    }

    return 0;
}