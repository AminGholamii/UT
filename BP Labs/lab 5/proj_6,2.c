#include<stdio.h>

int main(){

    char str1[]={'h','e','l','l','o'};
    printf("string 1= %s\n", str1);

    char str2[]={'h','e','l','l','o','\0'};
    printf("string 2= %s\n", str2);

    return 0;
}

/* In this case we are not declaring sizeof the array */

/* In first string at first a 5-char string will be saved in 
memory but when printing it into string , it actually needs null 
at the end which does not exist so the output will be the same 
weird one (helloá‼⌐)*/

/* In the second string as we defined a 6-char string with a null
at the end , it will be no issue executing it and it will work properly.*/
