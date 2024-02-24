//This File Can Be used For Testing Various Functions
#include <stdio.h>
#include "include/utility.h"
#include "include/constants.h"

typedef struct
{
    char name[50];
    char author[50];
    int age;
    int roll;
    char test[20];
} bookTest;

void save()
{

    Index in = {0};
    int n;
    printf("Enter Number Of Books\n");

    scanf("%d", &n);

    loadData(&in, sizeof(Index),1,INDEX);

    bookTest book [] = {0};
    printf("Stash - bookCount - %d\nuserCount - %d\n", in.bookCount, in.userCount);
    for(int i = 0; i < n; i++)
    {
        printf("Enter Age\n");
        scanf("%d", &book[i].age);
        printf("Enter Roll\n");
        scanf("%d", &book[i].roll);
        in.bookCount++;
    }
    saveData(&in, sizeof(Index),1,INDEX);
    saveData(&book,sizeof(bookTest), n ,BOOK);
    printf("Saved Data!\n\n");
}
void load()
{

    Index in = {0};
    loadData(&in, sizeof(Index),1,INDEX);


    bookTest book [in.bookCount];
    loadData(&book,sizeof(bookTest), in.bookCount ,BOOK);
    printf("Details Loaded!\n");
    printf("Stash :\nbookCount - %d\nuserCount - %d\n\n", in.bookCount, in.userCount);
    for(int i = 0; i < in.bookCount; i++)
    {
        printf("Detail - %d\n", i+1);
        printf("Age - %d\n", book[i].age);
        printf("Roll - %d\n\n", book[i].roll);
    }
}

int main()
{
    int n = 0;
    printf("Enter Number\n");
    scanf(" %d", &n);
    switch (n)
    {
    case 0:
        save();
        break;
    case 1:
        load();
        break;
    case 3:
        wipeOut();
        break;
    default:
        break;
    }
    return 0;
}


