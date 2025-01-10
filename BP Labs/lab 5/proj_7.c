#include<stdio.h>

int main(){

    char str[50];

    scanf("%s", str);         /* Change this to gets(str) later and the program will work properly.*/

    printf("%s\n", str);

    return 0;
}

/* Input will be (hello world) but output will be (hello) !
The reason is that scanf func starts reading characters one by one from 
the first character until it reachs a whitespace ; As a result only the word
(hello) will be saved in varriable str and prints it back.*/