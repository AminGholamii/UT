#include <stdio.h>

int main(){

    int a;

    printf("please enter a number: ");

    scanf("%d", &a);

    for(int i=1 ; i<=a ; i++){  /* i=1 (j=1,j=2,...,j=a) , i=2 (j=1,j=2,...,j=a) ,...,i=a (j=1,j=2,...,j=a) */

        for(int j=1 ; j<=a ; j++){

            printf("#");
        }
        
        printf("\n"); /*After each row we need an enter(\n) to go to next row.*/
    }

    return 0;
}