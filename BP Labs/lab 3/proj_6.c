#include <stdio.h>

int main(){

    int num;
    int result = 0 ;

    do {
        scanf("%d", &num);
        result += num ;
    }
    while( num != 0);

    printf("%d\n", result);

    return 0;

}