#include <stdio.h>

int main(){

    char operator;
    int n , temp;
    int sum_result = 0 , multiply_result = 1;

    scanf("%c %d", &operator , &n);

    switch (operator){

    case '+':

        for ( int i=1 ; i <= n ; i++){

            scanf("%d", &temp);
            sum_result += temp ;
        }

        printf("%d", sum_result);
        break;
    
    case '*':

        for ( int i=1 ; i <= n ; i++){

            scanf("%d", &temp);
            multiply_result *= temp ;
        }

        printf("%d", multiply_result);
        break;

    default:

        printf("Wrong Symbol");
        break;
    }
    
    return 0;
}