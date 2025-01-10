#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_NODES 3

typedef struct node{

    int data;
    struct node *next;

}node;

node* CreateNode(){

    node *the_node;

    the_node= (node*) malloc(sizeof(node));
    the_node->next=NULL;
    return the_node;

}

int main(){

    node *head , *temp;

    // Allocating memory
    head = CreateNode();
    temp = head->next;

    for(int i=1; i<=NUM_OF_NODES; i++){

        temp -> data = i;

        printf("data for node %d = %d\n", i, i);

        temp -> next = CreateNode();

        temp = temp -> next;

    }

    temp = head;

    for ( int i=0 ; i<=NUM_OF_NODES ; i++){

        node* temp2 = temp;

        free(temp);

        temp = temp2->next;

    }

    return 0;
}