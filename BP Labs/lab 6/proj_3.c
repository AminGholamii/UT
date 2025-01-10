#include <stdio.h>

int main(){

    float x,y;
    float *ptr ;      // ( int * )

    x = 12.34;

    ptr = &x;  /*You will recieve a warning while compiling this because u defined ptr as a pointer to an integer
               But it is actually a pointer to a float .*/

    y = *ptr;

    printf("y= %f\n",y); 

    return 0;
}