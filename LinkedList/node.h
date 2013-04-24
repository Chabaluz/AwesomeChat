struct Node{
    void* value;                //void *value som kan holde alle typer verdier
    struct Node *next;          //Holder en peker til den neste noden
};

struct Node* nodeItr(struct Node** n);
struct Node* nodeInsert(struct Node** node);
