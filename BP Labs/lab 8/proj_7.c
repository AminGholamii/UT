#include <stdio.h>
#define INPUT_FILE_ADDRESS "Input.txt"

int main(){

    FILE* Input = fopen( INPUT_FILE_ADDRESS , "r+");

    fseek( Input , 0 ,SEEK_END );

    fprintf(Input,"\nNow we know how to use files in c :) ");

    fclose(Input);

    return 0;
}