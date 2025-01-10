#include<stdio.h>
int main() {

    int input;

    scanf("%d", &input);

    if (input == 5){   /*Wrongly used assignment operator(=) rather than comparative operator(==)*/

        printf("Your number was 5\n", input);
    }
    else if (input > 5) {

        printf("Your number was greater than 5\n");
    }
    else {

        printf("Your number was less than 5\n");
    }

    printf("Entered number was %d",input);

    return 0;
}