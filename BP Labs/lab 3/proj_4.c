#include <stdio.h>

int main(){

    for(int i=1;i<=10;i++){

        printf("%d ",i);

        if(i%2==0){

        printf("is even!\n");
        }

        else{

        printf("is odd!\n");
        }

    }

    /*If condition is not entered you will face an infinite loop 
    which evaluate every number from 1 until infinite . 
    
    If update is not entered,condition is always true so program
    will rapidly(again a no-ending loop) prints (1 is odd!)  */

    return 0;
}