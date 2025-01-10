#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#define POSITION 3
#define VALUE 55

int main(){

    int *array;
    array = (int*)malloc(SIZE * sizeof(int));
    
    // Assigning values
    for (int i=0; i<SIZE; i++){
        *(array+i)=i+1;
    }
    
    // Printing the array
    for (int i=0; i<SIZE; i++){
        printf("%d\n",*(array+i));
    }

    printf("********\n");

    // Reallocating memory
    array = realloc(array , (SIZE+1)*sizeof(int) );

    // Shifting
    int temp1 , temp2;
    for (int i=1 ; i<SIZE+2 ; i++){

        if (POSITION == i){

            temp1 = array[i-1];
            array[i-1] = VALUE;

            for (int j=i+1 ; j<SIZE+2 ; j++){

                temp2 = array[j-1];
                array[j-1] = temp1;
                temp1 = temp2;

            }
        }
    }

    // Assigning value
    for (int i=0 ; i<SIZE+1; i++){

        if ( i+1 == POSITION ){
            continue;
        }

        else{
            array[i] = i;
        }
    }

    // Printing the array again
    for (int i=0; i<SIZE+1; i++){
        printf("%d\n",*(array+i));
    }

    free(array);

    return 0;
}