#include <stdio.h>
#include <stdlib.h>

int main() {

    int size=1 , check=1 , i=0 , num;

    int* array=(int*)malloc(size*sizeof(int)); //creating a dynamic array

    while(1){ //infinite loop

        scanf("%d", &num);

        if(num != 0){

            if(num % 2 == 0){

                array[i] = num; //saving the even number in the list
                size++;
                i++;
                array = (int*)realloc( array ,  size * sizeof(int)) ; //extending the size of the array
            }
        }

        else{
            size--;
            array = (int*)realloc( array ,  size * sizeof(int));
            break; //getting out of the loop
        }
    }

    printf("Here is the list of even numbers:\n");
    
    for(int i=0;i<size;i++){

        printf("%d\n", array[i] ); //printing the list
    }

    free(array);

    return 0;
}