#include <stdio.h>
#include <stdlib.h>

// rewriting with typedef

typedef struct information{  

    float weight;
    float height;

}Information;

int main(){

    Information person_1;

    printf("Please enter weight: \n");
    scanf("%f", &person_1.weight);   // (.) will access each element in structure 
                                    // -> is a sign for accessing a structure as a pointer.

    printf("Please enter height: \n");
    scanf("%f", &person_1.height);  

    return 0;
}