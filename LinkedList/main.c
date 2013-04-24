#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

struct User{
    char*   name;
    int     uid;
};

/* Create a random input function
 * returns input with \n removed from the end of the string.
 */
char* getInput(){
    size_t  len      = 0;
    char*   inputs   = NULL;

    getline(&inputs,&len,stdin);
    inputs[strlen(inputs)-1] = 0;

    return inputs;
}

int main(void){
    struct Node *users  = NULL;     //Set first to NULL
    char *input         = NULL;     //inputbuffer

    printf("Names:\n");
    while (1){ 
        printf("  ");
        input = getInput();


        if (strcmp(input,"/end")==0)
            break;

        struct Node *tmp = nodeInsert(&users);          //Add a new element to the list
        tmp->value = malloc(sizeof(struct User));       //Allocate memory to the value of the new node
        struct User *usr = ((struct User*)tmp->value);  //Cast value to the given type

        usr->name = input;
        usr->uid = rand();
    }

    printf("\n");

    struct Node *nodeitr = users; //Set nodeitr to point to the first element i the list
    struct User *usr;

    /* Iterate through the list of users */
    while(nodeitr!=NULL){
        usr = (struct User*)(nodeItr(&nodeitr)->value);
        printf("User: %d | %s\n",usr->uid,usr->name);
    }

    return 0;
}

