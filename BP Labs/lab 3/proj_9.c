#include <stdio.h>

int main(){

    int a,b;

    printf("please enter length (a): ");

    scanf("%d", &a);

    printf("please enter width (b): ");

    scanf("%d", &b);

    for(int i=1 ; i<=b ; i++){

        for(int j=1 ; j<=a ; j++){

            printf("#");
        }
        
        printf("\n"); 
    }

    return 0;
}