#include <stdio.h>

int main(){

    int *ptr ;
    *ptr = 20; // equaling an int* to int !

    /* You will recieve a warning while compiling this program . bcz ur intend to
    access a memory space which is not urs so system will stop it.*/ 
    

    printf("x= %d\n",*ptr);

    return 0;
}