#include <stdio.h>
#include <stdlib.h>
#define SIZE_OF_ARRAY 20
#define OUTPUT_FILE_ADDRESS "MyArray.txt"

char* array_producer(){

    char *array = (char *)calloc( SIZE_OF_ARRAY , sizeof(char));

    for(int i=0 ; i<10 ; i++){

        array[2*i] = 'A'+ i;
        array[2*i + 1] = ' ';
    }

    return array;
}


int main() 
{
    char* the_array = array_producer();
    FILE *output;
    output = fopen( OUTPUT_FILE_ADDRESS  , "w");
    fwrite(the_array , sizeof(char) , SIZE_OF_ARRAY , output );
    fclose(output);
    return 0;
}
