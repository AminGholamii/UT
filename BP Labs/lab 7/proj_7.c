#include<stdio.h>
#include<stdlib.h>

void main() {

    int *p = NULL;
    int i = 500000;

    for(int j=0 ; j<80 ; j++) {

        p = realloc(p , i * sizeof(int));  /*put breakpoint here*/
        i += 500000;
    }

    free(p);
}