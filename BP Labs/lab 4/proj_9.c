#include <stdio.h>

int function(float cal, float phy, float lab){

    float sum = (cal*3)+(phy*2)+(lab*1);
    float average = sum/6;

    return average;
}

int main(){

    float cal=18 , phy=17 , lab=19;

    printf("average= %f\n",function(phy , lab , cal ));

    /* Still if we haven't fixed the output type of the function , Eventhough we changed 
    the arrangement of the entry , the result will be the same (0.000000) .*/

    return 0;
}