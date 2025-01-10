#include<stdio.h>
int main(){

    int x=1 , y=0 , z=4;

    int a =x && ++y; 

    /* x is equal to 1 which is non-zero number so it's logically True.
     y is equal to 1 which is logically True .
     Eventually (x&&y) is equal to (True && True) and the result is True 
     which is equal to a nun-zero number.*/

    printf("x= %d\ny= %d\nz= %d\na= %d\n",x,y,z,a); /* x=1 y=1 z=4 a=1 */

    return 0;
}