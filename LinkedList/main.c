#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Lag node structen
struct Node{
    //void *value som kan holde alle typer verdier
    //bruker til å holde User noden i dette tilfellet
    void* value;

    //Holder en peker til den neste noden
    struct Node *next;
};

struct User{
    char*   name;
    int     uid;
};

//Lag en inputfunksjon for å kunne skrive inn navn med varierende lengde
char* getInput(size_t* sz){
    size_t  len      = 0;
    char*   inputs   = NULL;

    getline(&inputs,&len,stdin);
    if (sz!=NULL){
        (*sz) = len;
    }
    return inputs;
}

//Legg til en ny node i lista og returner en pointer til den nye noden
struct Node* nodeInsert(struct Node** node){
    if ((*node) == NULL){
        //Alloker en ny node
        (*node) = (struct Node*)malloc(sizeof(struct Node));
        (*node)->next = 0;
        return (*node);
    }else{ //Om first ikke er null, loop til slutten av lista
        struct Node *tmpnode = (*node);
        if ( tmpnode != 0 ){
            //Loop til next er 0
            while (tmpnode->next != 0)
            {
                //Gå videre
                tmpnode = tmpnode->next;
            }
        }

        //Om vi er på slutten legger vi til en ny node neders i lista
        tmpnode->next = malloc(sizeof(struct Node));
        //Sett så tmpnode til å peke på den siste vi lagde
        tmpnode = tmpnode->next;
        //Sett tmpnodes next til 0
        tmpnode->next = 0;
        return tmpnode;
    }

}

int main(void){
    //Sett first til å vøre null
    struct Node *users  = NULL;

    //inputbuffer
    char *input         = NULL;

    while (1){
        printf("Name: ");
        input = getInput(NULL);

        //Hopp ut av loopen om vi skriver end
        if (strcmp(input,"/end\n")==0)
            break;

        //Legg til en node i lenkelista users
        struct Node *tmp = nodeInsert(&users);
        //Alloker minne til å holde en ny User struct i void* value
        tmp->value = (struct User*)malloc(sizeof(struct User));
        //Cast void* value til struct User og sett name i User structen til input
        ((struct User*)tmp->value)->name = input;
    }

    printf("\n");

    //Sett tmpnode til å peke på det første elementet i Node users
    struct Node *tmpnode = users;

    //Sjekk om first har en verdig før vi starter å loope
    if (tmpnode != 0) {
        while (1)
        {
            //Print navnet til noden (caster på samme måte som da vi satte navnet
            printf("Names: %s",((struct User*)tmpnode->value)->name);

            //Om nodens next er null breaker vi ut av loopen og avslutter programmet
            if(tmpnode->next==NULL)
                break;

            //Om break ikke ble kjørt setter vi tmpnode til å peke må tmpnodes next
            tmpnode = tmpnode->next;
        }
    }

    return 0;
}

