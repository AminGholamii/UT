#include <stdio.h>
#include <stdlib.h>
#define SIZE_OF_ARRAY 20
#define INPUT_FILE_ADDRESS "MyArray.txt"
#define OUTPUT_FILE_ADDRESS "output.txt"

char *read_input_file(){

    char *in_order_array = (char *)malloc(SIZE_OF_ARRAY * sizeof(char));

    FILE *input = fopen(INPUT_FILE_ADDRESS, "r");
    fread(in_order_array , sizeof(char) , SIZE_OF_ARRAY , input);
    fclose(input);

    return in_order_array;
}

char *reverse_array(char *in_order_array){

    char *reversed_array = (char *)malloc(SIZE_OF_ARRAY * sizeof(char));
    
    for (int i = 0, j = SIZE_OF_ARRAY-1 ; i < SIZE_OF_ARRAY; i++, j--){

        *(reversed_array + i) = *(in_order_array + j);
    }

    return reversed_array;
}

void write_reversed_array_in_file(char *in_order_array){

    char *reversed_array = reverse_array(in_order_array);

    FILE *output;
    output = fopen(OUTPUT_FILE_ADDRESS, "w" );
    fwrite( reversed_array , sizeof(char) , SIZE_OF_ARRAY , output);
    fclose(output);

}

int main() {

    char *in_order_array = read_input_file();

    write_reversed_array_in_file(in_order_array);

    return 0;
}
