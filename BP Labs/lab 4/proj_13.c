#include <stdio.h>

int sum = 0; //global variable

int DigitSum(int n){

    if(n!=0){

        sum += n%10;

        DigitSum(n/10);

    }

    return sum;
}

int main(){

    int n;

    scanf("%d", &n);
    printf("digits sum = %d\n", DigitSum(n));

    return 0;
}