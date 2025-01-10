#include <stdio.h>
#include <math.h>
#define True 1

int main(){

    float initmass_a ,initmass_b;
    float growthrate_a ,growthrate_b;
    float mass_a , mass_b;
    int t = 1;

    scanf("%f %f", &initmass_a , &initmass_b);
    scanf("%f %f", &growthrate_a , &growthrate_b);

    if ( (initmass_a <= initmass_b) && (growthrate_a <= growthrate_b) ){

        printf("-1");
    }

    else if ( initmass_a > initmass_b){

        printf("0");
    }

    else{

        while (True){

            mass_a = initmass_a * pow(growthrate_a , t) ; /*Used pow function from math.h library.*/
            mass_b = initmass_b * pow(growthrate_b , t) ;

            if ( mass_a > mass_b ){

                printf("%d",t);
                break;
            }

            else {
                t++ ;
            } 
                
        }
    
    }

    return 0;
}