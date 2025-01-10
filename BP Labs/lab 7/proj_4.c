#include <stdio.h>
#include <stdlib.h>

void main() {

    int i;
    char* s;
    int* p = (int*)malloc(10*sizeof(int));

    for(i=0;i<10;i++)
        p[i] = i+48;

    s = (char*) p; // Cast the int* to char*
     
    printf("%c %c %c %c %c\n",s[4],s[5],s[6],s[7],s[8]);  // Every char is 1 byte and every int is at least 4 bytes.

    for(i=0; i<40; i++)  // 4 bytes for each integer and 1 byte for each char.

        printf("%c", s[i]);  // 48 is equal to ASCII number of char '0' and 57 is equal to '9'

    printf("\n");
    printf("p[0] is %d\n",*p);

    free(p);

    free(s); // we also took a space for representing character format of those .
}