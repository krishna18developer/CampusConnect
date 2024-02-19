//This File Can Be used For Testing Various Functions
#include <stdio.h>
#include "include/utility.h"
#include "include/constants.h"

typedef struct
{
    char name[50];
    char author[50];

} bookTest;

void save()
{
    bookTest ptr = {"Name","I am Author"};
    saveData(&ptr,sizeof(bookTest),BOOK);
}
void load()
{
    bookTest ptr;
    loadData(&ptr,sizeof(bookTest),BOOK);
    printf("Name - %s\n", ptr.name);
}

int main()
{
    switch (0)
    {
    case 0:
        save();
        break;
    case 1:
        load();
    default:
        break;
    }
    return 0;
}

