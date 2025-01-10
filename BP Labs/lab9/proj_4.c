#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int data;
    struct node *next;

}node;

node* CreateNode(){

    node *the_node;

    // Allocating memory
    the_node= (node*) malloc(sizeof(node));
    the_node->next=NULL;
    return the_node;
}

int main(){

    node *first_node , *second_node , *third_node , *head;

    // Allocating and connecting nodes
    head = CreateNode();
    head -> next = first_node;
    first_node = CreateNode();
    first_node -> next = second_node;
    second_node = CreateNode();
    second_node -> next = third_node;
    third_node = CreateNode();

    // Assigning data values
    first_node->data = 1;
    second_node->data = 2;
    third_node->data = 3;


    free(head);
    free(first_node);
    free(second_node);
    free(third_node);

    return 0;
}



