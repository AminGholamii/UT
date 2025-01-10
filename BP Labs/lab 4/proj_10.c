#include <stdio.h>

int g(int y){

    int j = 2;

    y = j * 3;

    return y;
}

int f(int x){

    return g(x);
}

int main(){

    int a = 10;

    printf("%d", f(a));

    /* First of all the number (a) go through the f function and as the returning number of f func is g(a) 
    a will go through the g func and then in that local func it stores a = 6 and returns 6 as the result .*/

    return 0;

}