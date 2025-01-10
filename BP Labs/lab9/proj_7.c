#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_PARTICIPANTS 3

typedef struct information{  

    float weight;
    float height;
    struct information *next;

}node;

void getInformation (node *person_ptr){

    node* temp = person_ptr->next;

    for(int i=1; i<=NUM_OF_PARTICIPANTS; i++){

        printf("Please enter weight for participant %d: \n", i);
        scanf("%f", &temp -> weight );

        printf("Please enter height for participant %d: \n", i);
        scanf("%f", &temp -> height) ;

        temp = temp -> next;
    }
}

void printInformation (node *person_ptr){

    node* temp = person_ptr->next;

    for(int i=1; i<=NUM_OF_PARTICIPANTS; i++){

        printf("participant %d\'s information:\n", i);
        printf("weight: %f\n", temp -> weight );
        printf("height: %f\n", temp -> height );

        temp = temp->next;
    }
}

node* CreateNode(){

    node *the_node;

    the_node= (node*) malloc(sizeof(node));
    the_node->next=NULL;
    return the_node;

}

void freenode(node* head){

    node* temp = head;

    for ( int i=0 ; i<=NUM_OF_PARTICIPANTS ; i++){

        node* temp2 = temp;

        free(temp);

        temp = temp2->next;

    }
    
}

int main(){

    node* head,*temp;

    head = CreateNode();

    temp = head;

    for(int i=1; i<=NUM_OF_PARTICIPANTS ; i++){

        temp->next = CreateNode();

        temp = temp->next;
    }
    getInformation(head);
    printInformation(head);

    freenode(head);

    return 0;
}