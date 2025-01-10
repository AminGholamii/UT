#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int* p = (int*)malloc(10 * sizeof(int));
    int i;

    printf("P = 0x%p\n", p);
    printf("****************\n");
    
    for (i = 0; i < 10; i++){

        printf("p%d = %d\n",i, *(p+i));
        /* As we just demanded for 10 places in memory , compiler 
        will search which place of the memory is free and take that for us;
        As a result the output values are some randoms(garbages) */
    }

    printf("p15 = %d\n",p[15]);

    free(p);    /* Address of the pointer will not change as we are 
                just making the pointer free and we're not putting another varriables
                in that memory. */

    printf("****************\n");
    printf("P = 0x%p\n", p);

    return 0;
}