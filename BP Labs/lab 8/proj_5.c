#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT_FILE_ADDRESS "Input.txt"
int main() {

    FILE *input = fopen(INPUT_FILE_ADDRESS, "a");

    char *text = " we love coding!! ";

    // fwrite( text , sizeof(char) , 19 , input)

    fprintf(input , text);

    fclose(input);

    return 0;
}