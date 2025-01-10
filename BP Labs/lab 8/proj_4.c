#include <stdio.h>
#include <stdlib.h>
#define INPUT_FILE_ADDRESS "Input.txt"
#define OUTPUT_FILE_ADDRESS "output.txt"

int length_of_file(){

    FILE *input = fopen(INPUT_FILE_ADDRESS, "r");

    char temp;
    int length=0;

    while (1){

        temp = getc(input);  

        if (feof(input)){
            break;
        }

        length++;
    }

    fclose(input);

    return length;
}

char *read_input_file(){

    int length = length_of_file();

    char *in_order_array = (char *) malloc(length * sizeof(char));

    FILE *input = fopen(INPUT_FILE_ADDRESS, "r");
    fread(in_order_array , sizeof(char) , length , input);
    fclose(input);

    return in_order_array;
}

char *reverse_and_swap(char *in_order_array){

    int length = length_of_file();

    char *reversed_array = (char *)malloc( length * sizeof(char));
    
    for (int i = 0, j = length-1 ; i < length; i++, j--){

        if ( *(in_order_array + j) >= 65 && *(in_order_array + j) <= 90 ){
        
            *(reversed_array + i) = *(in_order_array + j) + 32;
        }

        else if( *(in_order_array + j) >= 97 && *(in_order_array + j) <= 122 ){

            *(reversed_array + i) = *(in_order_array + j) - 32;
        }

        else{

            *(reversed_array + i) = *(in_order_array + j);
        }
    }

    return reversed_array;
}

void write_reversed_array_in_file(char *in_order_array){

    int length = length_of_file();

    char *reversed_array = reverse_and_swap(in_order_array);

    FILE *output;
    output = fopen(OUTPUT_FILE_ADDRESS, "w" );
    fwrite( reversed_array , sizeof(char) , length , output);
    fclose(output);

}

int main(){

    char* in_order_array = read_input_file();

    write_reversed_array_in_file(in_order_array);

    return 0;
}