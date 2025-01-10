#include <stdio.h>

int main() {

    int x= 25;
    int *ptr;
    int **ptr2;

    ptr = &x;
    ptr2 = &ptr;

    /* print the values of x , &x , *ptr , ptr , &ptr ,
    **ptr2 , *ptr2 , ptr2 and compare them! */

   printf("\nx = %d , &x = 0x%p\n*ptr = %d , ptr = 0x%p , &ptr = 0x%p\n**ptr2 = %d , *ptr2 = 0x%p , ptr2 = 0x%p",
   x , &x , *ptr , ptr , &ptr , **ptr2 , *ptr2 , ptr2 );


    *ptr = 2 * **ptr2;  // x = 2 * x 

    /* Now check the values of x , *ptr , **ptr2 */

    printf("\n\nx = %d\n*ptr = %d\n**ptr2 = %d\n\n" , x , *ptr , **ptr2);

    return 0;
}