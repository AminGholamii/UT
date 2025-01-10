#include<stdio.h>
int main(){

    int x=1 , y=0 , z=4;

    int a =--x && y || (z>>=2);

    /* x is equal to 0 which is logically False.
     y is equal to 0 which is logically False .
     Eventually (x&&y) is equal to (False && False) and the result is False 
     which is equal to the number 0 .
    
    Also new value of z is z/4=1 bcz (z=z>>2) means we can devide z on pow(2,2).*/

    /* At last the result will be (0 || 1) which is equal to (False || True)
    and the result will be True (a non-zero number) */

    printf("x= %d\ny= %d\nz= %d\na= %d\n",x,y,z,a); /* x=0 y=0 z=1 a=1 */

    return 0;
}