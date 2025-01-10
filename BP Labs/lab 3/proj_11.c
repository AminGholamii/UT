#include <stdio.h>

int main(){

    int n , sum=0;

    for(int i=1;i<=5;i++){

        printf("Enter a n%d: ", i);

        scanf("%d", &n);

        if(n<0){

            continue;
        }

        sum += n ;

    }

    printf("Sum = %d\n", sum);

    return 0;
}