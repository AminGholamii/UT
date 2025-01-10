#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int* p = (int*)calloc( 10 , sizeof(int)) ;
    int i;

    printf("P = 0x%p\n", p);
    printf("****************\n");
    
    for (i = 0; i < 10; i++){

        printf("p%d = %d\n",i, *(p+i));

        // All of the values are initialized by 0
        
    }

    free(p);
    printf("p15 = %d\n", *(p+15) ) ; 

    /* As all of previous values are initialized by 0 , They actually
    consumed less bytes so it will be more space for p15 */ 
      
    printf("****************\n");
    printf("P = 0x%p\n", p);

    return 0;
}