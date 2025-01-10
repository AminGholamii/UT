#include <stdio.h>

long fib(long n){

    if (n <= 2)
    return 1;
    return fib(n - 1) + fib (n - 2);
}

int main(){

    int n;

    printf("Please enter n: ");
    scanf("%d",&n);

    printf("n'th series of the fibo is %d.",fib(n));

    return 0;
}
