#include <stdio.h>
#include <stdlib.h>

typedef struct information{  

    float weight;
    float height;

}Information;

int main(){

    Information* person_ptr = (Information*) malloc(sizeof(Information));

    printf("Please enter weight: \n");
    scanf("%f", &person_ptr->weight);   

    printf("Please enter height: \n");
    scanf("%f", &person_ptr->height); 

    free(person_ptr);

    return 0;
}