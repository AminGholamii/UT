#include <stdio.h>

int main(){

    int *ptr = 5; 

    printf("%d\n", ptr); // This will be executed and prints the address of integer null (0)
    printf("%d\n", *ptr); // This will not be executed and may crash bcz we are willing to access null in memory.

    return 0;
}
