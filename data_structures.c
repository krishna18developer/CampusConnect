#include <stdlib.h>
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

LinkedList* createLinkedList()
{
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) 
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}
void append(LinkedList *list, void *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) 
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL)
    {
        list->head = newNode;
    }
    else 
    {
        Node *current = list->head;
        while (current->next != NULL) 
        {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

// Function to free memory allocated for the linked list
void freeLinkedList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}
