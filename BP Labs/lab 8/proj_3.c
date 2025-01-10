#include <stdio.h>
#define INPUT_FILE_ADDRESS "Input.txt"

int main() {

    FILE *input = fopen(INPUT_FILE_ADDRESS, "r");

    char temp;
    int length=0;

    while (1){

        temp = getc(input);  // We use this to move the curser.

        if (feof(input)){
            break;
        }

        length++;
    }

    fclose(input);

    printf("%d\n", length);
}
