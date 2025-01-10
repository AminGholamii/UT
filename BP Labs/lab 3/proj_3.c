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

    /*No error while compiling.
    Infinite loop if update is i-- */

    return 0;
}