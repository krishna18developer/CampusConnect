#include "include/utility.h"
#include "include/constants.h"
#include "include/book.h"
#include <stdio.h>

// DATA CREATION TOOL

typedef struct 
{
    int id;
    int salary;
}
User;

void userload()
{
    Index in = {0};

    loadData(&in, sizeof(Index), 1, INDEX);

    printf("User Count : %d\n" , in.userCount);


    User u[in.userCount];

    for(int i = 0; i < in.userCount; i++)
    {
        loadData(&u[i],sizeof(User),i, USER);
        printf("Loaded Successfully!\n");
        printf("Details For User - %d\n", i+1);
        printf("ID : %d\n", u[i].id);
        printf("Salary : %d\n", u[i].salary);
    }
}


void usersave()
{
    Index in = {0};

    loadData(&in, sizeof(Index), 1, INDEX);

    printf("Total Number of Users Present : %d\n", in.userCount);
    int n;
    printf("Enter Additonal Number of Users Required : ");
    scanf("%d", &n);
    int total = in.userCount + n;   // USER COUNT - 0 + 3  total = 3

    if(total <= 0)
    {
        in.userCount = 0;
        saveData(&in, sizeof(Index), 1, INDEX);
        return;
    }
    User u[total];

    for(int i = in.userCount; i < total; i++)  // 0 1 2
    {
        printf("Enter Details For User - %d\n", i+1);
        printf("Enter ID : ");
        scanf("%d", &u[i].id);
        printf("Enter Salary : ");
        scanf("%d", &u[i].salary);
        saveData(&u[i],sizeof(User),i, USER);
        printf("Saved Successfully!\n");
        in.userCount++;
        saveData(&in, sizeof(Index), 1, INDEX);
    }
}

void bookload()
{
    Index in = {0};

    loadData(&in, sizeof(Index), 1, INDEX);

    printf("Book Count : %d\n" , in.bookCount);


    Book u[in.bookCount];

    for(int i = 0; i < in.bookCount; i++)
    {
        loadData(&u[i],sizeof(Book),i, BOOK);
        printf("Loaded Successfully!\n");
        printf("Details For Book - %d\n", i+1);
        printf("ID : %d\n", u[i].id);
        printf("Cost : %d\n", u[i].cost);
    }
}


void booksave()
{
    Index in = {0};

    loadData(&in, sizeof(Index), 1, INDEX);

    printf("Total Number of Books Present : %d\n", in.bookCount);
    int n;
    printf("Enter Additonal Number of Books Required : ");
    scanf("%d", &n);
    int total = in.bookCount + n;   // BOOK COUNT - 0 + 3  total = 3

    if(total <= 0)
    {
        in.bookCount = 0;
        saveData(&in, sizeof(Index), 1, INDEX);
        return;
    }
    Book u[total];

    for(int i = in.bookCount; i < total; i++)  // 0 1 2
    {
        printf("Enter Details For Book - %d\n", i+1);
        printf("Enter ID : ");
        scanf("%d", &u[i].id);
        printf("Enter Cost : ");
        scanf("%d", &u[i].cost);
        saveData(&u[i],sizeof(Book),i, BOOK);
        printf("Saved Successfully!\n");
        in.bookCount++;
        saveData(&in, sizeof(Index), 1, INDEX);
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
        usersave();
        break;
    case 1:
        userload();
        break;
    case 2:
        booksave();
        break;
    case 3:
        bookload();
        break;
    default:
        break;
    }
    return 0;
}


