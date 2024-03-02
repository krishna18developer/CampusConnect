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


void test()
{
    Index in = {0};

    int n;
    printf("Enter Number Of Books\n");
    scanf("%d", &n);

    loadData(&in, sizeof(Index), 1, INDEX);

    int total = in.bookCount + n;
    bookTest book[total];
    for(int i = in.bookCount; i < total; i++)
    {
        printf("Enter Detail of %d\n" , i);
        printf("Enter Age\n");
        scanf("%d", &book[i].age);
        printf("Enter Roll\n");
        scanf("%d", &book[i].roll);
        in.bookCount++;
        printf("\n\n");
    }

    for(int i = 0; i < total; i++)
    {
        saveData(&book[i], sizeof(book[i]), i, BOOK);
    }
    saveData(&in, sizeof(Index), 0, INDEX);
}







void save()
{

    Index in = {0};
    int n;
    printf("Enter Number Of Books\n");

    scanf("%d", &n);

    loadData(&in, sizeof(Index),0, INDEX);
    
    int total = in.bookCount + n; // 2 + 3 = 5  || 0 1 + 2 3 4  || 0 + 3 
    bookTest book [total];

    for(int i = 0; i < in.bookCount; i++)
    saveData(&book, sizeof(bookTest), i, BOOK);

    printf("Index - bookCount - %d\nuserCount - %d\n", in.bookCount, in.userCount);
    int st = in.bookCount;
    if(in.bookCount <=0)
    st = 0;
    for(int i = st; i < total; i++)
    {
        printf("Detail - %d\n", i+1);
        printf("Enter Age\n");
        scanf("%d", &book[i].age);
        printf("Enter Roll\n");
        scanf("%d", &book[i].roll);
        in.bookCount++;
        printf("\n\n");
    }
    saveData(&in, sizeof(Index), 0, INDEX);
    saveData(&book,sizeof(bookTest), n, BOOK);
    printf("Saved Data!\n\n");
}
void load()
{

    Index in = {0};
    loadData(&in, sizeof(Index),0, INDEX);

    bookTest book [in.bookCount];
    for(int i = 0; i < in.bookCount; i++)
    loadData(&book, sizeof(bookTest), i, BOOK);

    printf("Details Loaded!\n");
    printf("Index :\nbookCount - %d\nuserCount - %d\n\n", in.bookCount, in.userCount);


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


