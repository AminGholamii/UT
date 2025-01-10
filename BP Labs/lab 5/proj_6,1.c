#include<stdio.h>

int main(){

    char str1[5]="hello";
    printf("string 1= %s\n", str1);

    char str2[6]="hello";
    printf("string 2= %s\n", str2);

    return 0;
}

/* In C, the Null character represents the conclusion of a string . In every single string
you have to consider a null character(\0) for it's termination. */

/* In the first string we have not saved a space for null so the 
program will not work properly and u may see (helloá‼↑) ! */

/* In the second one as we considered a space for null , everything will be 
alright and u will see the word (hello) */
