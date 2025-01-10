#include <stdio.h>
#include <string.h>
#define INPUT_FILE_ADDRESS "Input.txt"

int main() {

    FILE *input = fopen(INPUT_FILE_ADDRESS, "r+");

    char *text = "we love coding!!";

    fseek(input , 14 , SEEK_SET);
    fwrite(text , sizeof(char) , 16 , input);
    fclose(input);
       
    return 0;
}