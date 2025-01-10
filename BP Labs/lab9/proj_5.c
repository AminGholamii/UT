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
    temp = head;

    for(int i=0; i<NUM_OF_NODES; i++){

        temp -> next = CreateNode();

        temp = temp -> next;

    }

    return 0;
}
