#include<stdio.h>

int main(){

    char str[]="hello world";

    printf("*****\n");

    puts(str);        /* This prints a (\n) itself after printing the str. */

    printf("*****\n");
 
    printf("%s", str);     /* This does'nt print a (\n) itself . It needs to be entered manually.*/

    printf("*****\n");

    return 0 ;
}