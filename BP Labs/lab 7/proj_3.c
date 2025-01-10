#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
void printer(int* array, int size);

void printer(int* array, int size){

    for(int i=0;i<size;i++)
        printf("%d ", array[i]);

    printf("\n");
}

int main() {

    int* array=(int*)malloc(SIZE*sizeof(int)); //creating a dynamic array

    for(int i=0;i<SIZE;i++)
        array[i]=(i+1);

    printer(array,SIZE);

    array = (int*)realloc(array,(SIZE+1)*sizeof(int)) ;  // first : array=(int*)realloc(array,(SIZE+1)*sizeof(int));
    array[4]=5;

    printer(array , (SIZE+1));

    free(array);

    return 0;
}
