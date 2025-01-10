#include <stdio.h>
#define True 1

int main(){

    int n , sum=0;
    int i=1;

    while(True){

        if ( i > 5){

            break;
        }

        printf("Enter a n%d: ", i);

        scanf("%d", &n);
        
        if(n>=0){

            sum +=n;
        }

        i++;

    }

    printf("Sum = %d\n", sum);

    return 0;
}