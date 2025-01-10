#include<stdio.h>

int main(){

    int arr[5];

    for(int i=0 ; i<5 ;i++){
        
        scanf("%d", &arr[i]);
    }

    for(int j=4 ; j>=0 ; j--){
        
        printf("%d\n", arr[j] );
    }

    return 0;
}
