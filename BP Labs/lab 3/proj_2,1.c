#include<stdio.h>
int main(){

    int x=1 , y=0 , z=4;

    int a =x && y++; 

    /* x is equal to 1 which is non-zero number so it's logically True.
     y is equal to 0 which is logically False .
     Eventually (x&&y) is equal to (True && False) and the result is False 
     which is equal to the number 0 .*/

    printf("x= %d\ny= %d\nz= %d\na= %d\n",x,y,z,a); /* x=1 y=1 z=4 a=0 */

    return 0;
}

