#include <stdio.h>
void num_sorter(int first_num, int second_num);

void num_sorter(int first_num, int second_num){

    if (first_num < second_num){

        int temp = first_num;
        first_num = second_num;
        second_num = temp;
    }
}

int main(){

    int first_num=5, second_num=7;

    num_sorter(first_num,second_num);

    /* The program will not work properly bcz it will just change values of local 
    varriables in function num_sorter not in main function .  */

    printf("first= %d\nsecond= %d", first_num, second_num);

    return 0;
}
