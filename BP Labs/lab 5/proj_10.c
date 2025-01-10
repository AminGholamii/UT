#include<stdio.h>
#define SIZE 5

int main(){

    int i,j;

    int table[SIZE][SIZE]= {{1,2,3,4,5},
    {6,7,8,9,10},
    {11,12,13,14,15},
    {16,17,18,19,20},
    {21,22,23,24,25}};

    int second_table[SIZE][SIZE];

    for(int i=0;i<SIZE;i++){
        
        for(int j=0; j<SIZE;j++){
            
            second_table[j][i] = table[i][j] ;

        }

    } // transposing

    for(int i=0;i<SIZE;i++){

        for(int j=0;j<SIZE;j++){
            
            printf("%d ", second_table[i][j]);

        }

        printf("\n");

    }// printing the result

    return 0;
}
