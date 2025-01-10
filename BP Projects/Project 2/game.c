#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 4
#define ZERO 0
#define TRUE 1

void applyCommand(char com, int game_page[SIZE][SIZE] , int last_game[SIZE][SIZE]);
void makeCopy(int last_game[SIZE][SIZE], int game_page[SIZE][SIZE]);
int ifChanged(int game_page[SIZE][SIZE], int last_game[SIZE][SIZE]);

char printBoard(int game_page[SIZE][SIZE]);
void addRandom(int game_page[SIZE][SIZE]);
void initializeBoard(int game_page[SIZE][SIZE]);
int calculateScore(int game_page[SIZE][SIZE]);
int moveLeft(int game_page[SIZE][SIZE], int test[SIZE][SIZE]);
int moveRight (int game_page[SIZE][SIZE], int test[SIZE][SIZE]);
int moveUp(int game_page[SIZE][SIZE], int test[SIZE][SIZE]);
int moveDown(int game_page[SIZE][SIZE], int test[SIZE][SIZE]);
int ifLoose(int game_page[SIZE][SIZE]);
int ifWin(int game_page[SIZE][SIZE]);


int main(){

    int game_page[SIZE][SIZE];
    int last_game[SIZE][SIZE] = {0};
    int last_game2[SIZE][SIZE] = {0};
    int test[SIZE][SIZE] = {0};

    srand(time(ZERO));   // initialize srand with time(0)

    initializeBoard(game_page);

    char command = '\0';

    while (TRUE) {

        if (ifLoose(game_page)){
            
            printBoard(game_page);
            printf("Game Over!\n");
            break;
        }

        if (ifWin(game_page)){

            printBoard(game_page);
            printf("You Won!\n");
            break;
        }

        if (command == 'Q') {
            break;
        }

        command = printBoard(game_page);
 
        applyCommand(command, game_page, last_game);
    }
    
    return 0;
}


char printBoard(int game_page[SIZE][SIZE]){

    char com;  // Move commands or Quit or Back or New start
    int Score = calculateScore(game_page);

    printf("\n*************************************\n");
    printf("Your Score: %d\n", Score );
    printf("--------------------\n");

    for ( int i = 0 ; i < SIZE ; i++){

        for ( int j = 0 ; j < SIZE ; j++){

            if ( game_page[i][j] != 0 ){

                if (game_page[i][j] > 1000)
                    printf("|%d", game_page[i][j] );
                
                else if (game_page[i][j] > 100)
                    printf("| %d",game_page[i][j]);
                
                else if (game_page[i][j] > 10)
                    printf("|  %d",game_page[i][j]);

                else
                    printf("|   %d", game_page[i][j]);
            }

            else{
                printf("|    ");
            }
        }

        printf("|\n");
    } 

    printf("--------------------\n");

    if ( !ifLoose(game_page) && !ifWin(game_page)){

        printf("Move (L/R/U/D) or Quit, Back, New Start(Q, B, N): ");
        
        com = getchar();

        while ( getchar() != '\n' );
        
        return com;
    }
}

void applyCommand(char com, int game_page[SIZE][SIZE] , int last_game[SIZE][SIZE]){

        int test[SIZE][SIZE] = {0};
        
        if ( !ifLoose(game_page) && !ifWin(game_page) && com != 'Q' )

            switch ( com ) {

                case 'N':
                    initializeBoard(game_page);
                    break;
                
                case 'B':  
                    printBoard(last_game);
                    break;
                
                case 'L': 

                    makeCopy(last_game, game_page);  // Making copy from moment page

                    while ( moveLeft(game_page,test) );

                    if ( ifChanged(game_page,last_game) )
                        
                        addRandom(game_page);   // Only adds random when board is changed

                    break;

                case 'R' :

                    makeCopy(last_game, game_page);  // Making copy from moment page

                    while ( moveRight(game_page,test) );

                    if ( ifChanged(game_page,last_game) )
                        
                        addRandom(game_page);   // Only adds random when board is changed
                    
                    break;
                
                case 'U':

                    makeCopy(last_game, game_page);  // Making copy from moment page

                    while ( moveUp(game_page,test) );

                    if ( ifChanged(game_page,last_game) )

                        addRandom(game_page); // Only adds random when board is changed

                    break;
                
                case 'D':

                    makeCopy(last_game, game_page);  // Making copy from moment page

                    while ( moveDown(game_page,test) );

                    if ( ifChanged(game_page,last_game) )

                        addRandom(game_page); // Only adds random when board is changed

                    break;
                
                default:
                    makeCopy(last_game, game_page);
                    printf("\n\nInvalid move\n");
                    break;
            }
}

void makeCopy(int last_game[SIZE][SIZE],int game_page[SIZE][SIZE]){

    for ( int i = 0 ; i < SIZE ; i++)

        for ( int j = 0 ; j < SIZE ; j++)

            last_game[i][j] = game_page[i][j];

}

int ifChanged(int game_page[SIZE][SIZE], int last_game[SIZE][SIZE]){

        for (int i = 0 ; i < SIZE ; i++) {

            for (int j = 0 ; j < SIZE ; j++) {

                if (game_page[i][j] != last_game[i][j]) {

                    return 1 ;  // changed
                }
            }
        }

        return 0;  // Without change 
}


void addRandom(int game_page[SIZE][SIZE]){

    int num = rand() % 2 ;

    ( num == 0 ) ? ( num = 2 ) : ( num = 4 ) ;  // exchanging the random number to 2 or 4

    int element1 = rand() % SIZE ;  // a random number as i ( game_page[i][j] )
    int element2 = rand() % SIZE ;  // a random number as j ( game_page[i][j] )


    if ( game_page[element1][element2] == 0 ){

        game_page[element1][element2] = num ;
    }

    else addRandom(game_page);

}


void initializeBoard(int game_page[SIZE][SIZE]){

    for ( int i = 0 ; i < SIZE ; i++){

        for ( int j = 0 ; j < SIZE ; j++){

            game_page[i][j] = 0 ;
        }
    }

    addRandom(game_page);
    addRandom(game_page);
}

int calculateScore(int game_page[SIZE][SIZE]){

    int Score = 0;

    for ( int i = 0 ; i < SIZE ; i ++){

        for ( int j = 0 ; j < SIZE ; j++){

            Score += game_page[i][j] ;
        }
    }

    return Score;
}

int moveLeft(int game_page[SIZE][SIZE], int test[SIZE][SIZE]){

    int count = 0 ;

    for ( int i = 0 ; i < SIZE ; i++){

        for ( int j = 0 ; j < SIZE ; j++){

            if ( game_page[i][j] != 0 ){

                if ( j >= 1 ){

                    if ( game_page[i][j-1] == game_page[i][j] ){

                        if ( test[i][j] != 1 ){  // Avoids multiple changes

                            game_page[i][j-1] += game_page[i][j] ;
                            test[i][j] = 1;
                            test[i][j-1] = 1;
                            game_page[i][j] = 0;
                            
                            count++ ;
                        }
                    }

                    else if ( game_page[i][j-1] == 0 ) {

                        game_page[i][j-1] = game_page[i][j];
                        game_page[i][j] = 0;
                        
                        count++ ;
                   }
                }
            }

        }
    }

    if ( count == 0 ) return 0;
    else return 1;
}

int moveRight (int game_page[SIZE][SIZE], int test[SIZE][SIZE]){

    int count = 0;

    for ( int i = 0 ; i < SIZE ; i++){

        for ( int j = 0 ; j < SIZE ; j++ ){

            if ( game_page[i][j] != 0 ){

                if ( j < SIZE-1 ){

                    if ( game_page[i][j+1] == game_page[i][j] ){

                        if ( test[i][j] != 1 ){ // Avoids multiple changes
                        
                            game_page[i][j+1] += game_page[i][j];
                            test[i][j+1] = 1;
                            test[i][j] = 1;
                            game_page[i][j] = 0;

                            count++ ;
                        }
                    }

                    else if ( game_page[i][j+1] == 0 ){

                        game_page[i][j+1] = game_page[i][j];
                        game_page[i][j] = 0;

                        count++ ;
                    }
                }
            }
        }
    }

    if ( count == 0 ) return 0;
    else return 1;
}

int moveUp(int game_page[SIZE][SIZE], int test[SIZE][SIZE]){

    int count = 0 ;

    for ( int j = 0 ; j < SIZE ; j++ ){

        for ( int i = 0 ; i < SIZE ; i++){

            if ( game_page[i][j] != 0 ){

                if ( i >= 1 ){

                    if ( game_page[i-1][j] == game_page[i][j] ){

                        if ( test[i][j] != 1 ){  // Avoids multiple changes

                            game_page[i-1][j] += game_page[i][j];
                            test[i-1][j] = 1;
                            test[i][j] = 1;
                            game_page[i][j] = 0;

                            count++ ;
                        }
                    }

                    else if ( game_page[i-1][j] == 0 ){

                        game_page[i-1][j] = game_page[i][j];
                        game_page[i][j] = 0;

                        count++ ;
                    }
                }
            }
        }
    }

    if ( count == 0 ) return 0;
    else return 1;
}

int moveDown(int game_page[SIZE][SIZE], int test[SIZE][SIZE]){

    int count = 0;

    for ( int j = 0 ; j < SIZE ; j++){

        for ( int i = 0 ; i < SIZE ; i++){

            if ( game_page[i][j] != 0 ){

                if ( i < SIZE-1 ){

                    if ( game_page[i+1][j] == game_page[i][j] ){

                        if ( test[i][j] != 1 ){ // Avoids multiple changes

                            game_page[i+1][j] += game_page[i][j];
                            test[i+1][j] = 1;
                            test[i][j] = 1;
                            game_page[i][j] = 0;

                            count++ ;
                        }
                    }

                    else if ( game_page[i+1][j] == 0 ){

                        game_page[i+1][j] = game_page[i][j];
                        game_page[i][j] = 0;

                        count++ ;
                    }
                }
            }
        }
    }

    if ( count == 0 ) return 0;
    else return 1;
}

int ifLoose(int game_page[SIZE][SIZE]){

        int empty = 0;

        for ( int i = 0 ; i < SIZE ; i++)

            for ( int j = 0 ; j < SIZE ; j++)

                if ( game_page[i][j] == 0 ) 

                    empty++ ;

        
        if (empty == 0) return 1;
        
        else return 0;
}

int ifWin(int game_page[SIZE][SIZE]){

    for ( int i = 0 ; i < SIZE ; i++)

        for ( int j = 0 ; j < SIZE ; j++)

            if ( game_page[i][j] == 2048 )

                return 1;

    return 0;
}

// END





