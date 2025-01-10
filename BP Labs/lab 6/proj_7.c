#include <stdio.h>

int main() {

    char str[] = "University of tehran";
    char* str_copy;

    str_copy = str;

    *( str_copy + 14 ) = 'T';  //conversion

    /* Two strings will be changed bcz str_copy is not actually a copy of str ; It is a pointer
    to where str is stored . */

    printf("str= %s\nstr_copy= %s\n",str , str_copy );

    return 0;
}
