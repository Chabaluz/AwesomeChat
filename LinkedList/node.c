#include <stdio.h>
#include "node.h"

/**
 * @brief nodeItr   Iterate through a list of nodes
 * @param n         The iterating node
 * @return          Current node
 */
struct Node* nodeItr(struct Node** n){
    struct Node* pre = (*n);
    if ((*n)!=0) {
        (*n) = (*n)->next;
        return pre;
    }
    return NULL;
}

/**
 * @brief nodeInsert    Add a new Node to the list
 * @param node          Pointer to the first element in the list
 * @return              New Node
 */
struct Node* nodeInsert(struct Node** node){
    if ((*node) == NULL){
        (*node) = (struct Node*)malloc(sizeof(struct Node));    //Allocate memory for a new node
        (*node)->next = 0;
        return (*node);
    }else{
        struct Node *tmpnode = (*node);
        if ( tmpnode != 0 ){

            while (tmpnode->next != 0)                  //Loop until next is 0/NULL (last element in list)
                tmpnode = tmpnode->next;                //Proceed
        }

        tmpnode->next = malloc(sizeof(struct Node));    //Om vi er på slutten legger vi til en ny node neders i lista
        tmpnode = tmpnode->next;                        //Sett så tmpnode til å peke på den siste vi lagde
        tmpnode->next = NULL;                           //Sett tmpnodes next til 0
        return tmpnode;
    }

}
