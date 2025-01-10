#include <stdio.h>

int main(){

    int rows,chairs;
    int Absent_numbers = 0, Positive_votes = 0, Negative_votes = 0 ;
    float Positive_percent,Negative_percent;

    scanf("%d %d",&rows,&chairs);

    char vote[chairs+1];       /*declare a string input*/

    for ( int i=1 ; i <= rows ; i++ ){

        scanf("%s", vote); 

        for ( int j = 0 ; j < chairs ; j++){

            switch (vote[j]){ 

                case 'A':
                    Absent_numbers++;
                    break;
                
                case 'P':
                    Positive_votes++;
                    break;
                
                case 'N':
                    Negative_votes++;
                    break;
                
                default:
                    break;
            }

        }

    }

    printf("Positive: %d\n",Positive_votes);
    printf("Negative: %d\n",Negative_votes);
    printf("Absent: %d\n",Absent_numbers);

    Positive_percent = ( (float)Positive_votes / (Positive_votes + Negative_votes) ) * 100;
    Negative_percent = ( (float)Negative_votes / (Positive_votes + Negative_votes) ) * 100;

    printf("P: %.2f %%\n", Positive_percent);
    printf("N: %.2f %%\n", Negative_percent);

    if ( Positive_votes > Negative_votes ){

        printf("Result: P");
    }

    else if ( Negative_votes > Positive_votes ){

        printf("Result: N");
    }

    else {

        printf("Result: A");
    }

    return 0;
}