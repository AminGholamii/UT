#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_PARTICIPANTS 3

typedef struct information{  

    float weight;
    float height;

}Information;

void getInformation (Information *person_ptr);
void printInformation (Information *person_ptr);


int main(){

    Information* person_ptr = (Information*) malloc(NUM_OF_PARTICIPANTS * sizeof(Information));

    getInformation(person_ptr);
    printInformation(person_ptr);

    free(person_ptr);

    return 0;
}

void getInformation (Information *person_ptr){

    for(int i=0; i<NUM_OF_PARTICIPANTS; i++){

        printf("Please enter weight for participant %d: \n", i+1);
        scanf("%f", &((person_ptr+i) -> weight) );

        printf("Please enter height for participant %d: \n", i+1);
        scanf("%f", &((person_ptr+i) -> height) );
    }
}

void printInformation (Information *person_ptr){

    for(int i=0; i<NUM_OF_PARTICIPANTS; i++){

        printf("participant %d\'s information:\n", i+1);
        printf("weight: %f\n", (person_ptr+i) -> weight );
        printf("height: %f\n", (person_ptr+i) -> height );
    }
}
