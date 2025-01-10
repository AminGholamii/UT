#include <stdio.h>
#include <stdlib.h>
#define True 1


int main(){

    int seed = 810103480;
    srand(seed);       /* random function is defined in stdlib.h library.*/
    int random_number = rand() % 100; /*random number is 55 .*/

    int input_number;

    while (True){

        printf("Please guess a number in range(0,100) : ");

        scanf("%d",&input_number);

        if ( input_number == random_number){

            printf("You guessed the number correctly! ");
            break;
        }

        else if ( input_number < random_number){

            printf("Input number was less than random number.\n");
        }

        else{

            printf("Input number was greater than random number.\n");
        }
    }

    /*
    Binary search is a search algorithm used to find 
    the position of a target value within a sorted array.
    It works by repeatedly dividing the search interval 
    in half until the target value is found or the interval is empty. 
    The search interval is halved by comparing
    the target element with the middle value of the search space.*/

    return 0;
}