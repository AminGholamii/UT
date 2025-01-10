/* This is related to proj_12 */

#include "fact.h"

int fact(int x){

    int result = 1;

    for( int i=1 ; i <= x ; i++){

        result *= i ;
    }

    return result;
}