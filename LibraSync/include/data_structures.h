typedef struct
{
    void *data;
    Node *next;
} Node;

typedef struct 
{
    Node *head;    
    int size;
} LinkedList;

LinkedList* createLinkedList();

void append(LinkedList *list, void *data);

void freeLinkedList(LinkedList *list);