#include<stdio.h>
int main(){

    int x=1 , y=0 , z=4;

    int a =--x && y || (z>>=2); /*As calculated in last code x=0 y=0 z=1 a=1*/

    !a ? printf("%d\n", z) : printf("%d\n", ++z);

    /* !a is equal to !1 or !True which is False 
    So the second command will be executed as it prints (z+1)=2 */

    return 0;
}
