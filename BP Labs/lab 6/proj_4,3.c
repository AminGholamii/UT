#include <stdio.h>

int main() {

    int x = 30 , y = 80 , *ptr1 , *ptr2;

    ptr1=&x;
    ptr2=&y;

    x = y ; // but &x != &y

    printf("x=%d , address_x=0x%p\ny=%d , address_y=0x%p\n*ptr1=%d , ptr1=0x%p\n*ptr2=%d , ptr2=0x%p\n",
    x , &x , y , &y , *ptr1 , ptr1 , *ptr2 , ptr2);

    return 0;
}