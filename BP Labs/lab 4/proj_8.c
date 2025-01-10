#include <stdio.h>

int function(float cal, float phy, float lab){

    float sum = (cal*3)+(phy*2)+(lab*1);
    float average = sum/6;

    return average;
}

int main(){

    float cal=18 , phy=17 , lab=19;

    printf("average= %f\n",function(cal , phy , lab ));

    /* Result will be 0.000000 bcz we declared the output type of the function as an integer 
    while the output is a float number .*/

    return 0;
}