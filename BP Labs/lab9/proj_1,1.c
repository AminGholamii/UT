#include <stdio.h>
#include <stdlib.h>

struct information{

    float weight;
    float height;
};

int main(){

    struct information person_1;

    printf("Please enter weight: \n");
    scanf("%f", &person_1.weight);   // added an &

    printf("Please enter height: \n");
    scanf("%f", &person_1.height);  // added an &

    return 0;
}
