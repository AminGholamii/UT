#include <stdio.h>

int main() {

    int z = 4;

    if (z - 4) {  /* z-4 = 0 (False) so this statement will not be executed .*/

        int i = 1;
        z = z + i;
        printf("i=%d , z=%d\n", i,z);
    }
    
    else { /* This will be executed.*/

        int i = 0;
        z = i + 1;  /* here z = 1 */
        {
            int i = 1;
            z = i + 1;      /*  z will change into 2 */
            printf("i=%d , z=%d\n", i,z);         /* i=1 , z=2 */
        }
        printf("i=%d , z=%d\n", i,z);      /* i=0 , z=2 */
    }

    return 0;
}