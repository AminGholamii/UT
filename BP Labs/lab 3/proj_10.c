#include <stdio.h>

int main(){

    int a,b;

    printf("please enter number of rows (a): ");

    scanf("%d", &a);

    printf("please enter number of columns (b): ");

    scanf("%d",&b);

    for(int i=1 ; i<=a ; i++){

        for(int j=1 ; j<=b ; j++){

            printf("%d ",i*j);
        }
        
        printf("\n");
    }

    return 0;
}