#include <stdio.h>

int function(float cal, float phy, float lab){

    float sum= (cal*3)+(phy*2)+(lab*1);
    float average = sum/6;

    return average;
}

int main(){

    float cal=18 , phy=17 , lab=19;

    printf("average= %f\n",function(cal , phy , lab ));

    /* If (lab) has not entered above , you will recieve error while compiling this program .
    The reason is too few arguments are given to function comparing to declared one.*/

    return 0;
}