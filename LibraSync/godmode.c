#include "include/utility.h"
#include "include/constants.h"
#include "include/book.h"
#include <stdio.h>
#include <stdlib.h>
// DATA CREATION TOOL

typedef struct 
{
    int id;
    int salary;
}
User;

void userLoadAll()
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


void usersaveAdditional()
{
    Index in = {0};

    loadData(&in, sizeof(Index), 1, INDEX);
    in.books = calloc(in.bookCount, sizeof(int));
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

void bookloadAll()
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


void bookSaveAdditional()
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

void bookAddSpecific()
{
    int n;
    Index in = {0};
    loadData(&in, sizeof(Index),1,INDEX);
    printf("Enter Number of The Book : ");
    scanf(" %d", &n);

    Book u;
    printf("Enter Details For Book - %d\n", n);
    printf("Enter ID : ");
    scanf("%d", &u.id);
    printf("Enter Cost : ");
    scanf("%d", &u.cost);
    saveData(&u, sizeof(Book), n-1, BOOK);
    printf("Saved Successfully!\n");
    in.bookCount++;
    saveData(&in, sizeof(Index), 1, INDEX);
}

void userAddSpecific()
{
    int n;
    Index in = {0};
    loadData(&in, sizeof(Index),1,INDEX);
    printf("Enter Number of The User : ");
    scanf(" %d", &n);

    User u;
    printf("Enter Details For User - %d\n", n);
    printf("Enter ID : ");
    scanf("%d", &u.id);
    printf("Enter Salary : ");
    scanf("%d", &u.salary);
    saveData(&u, sizeof(User), n-1 , USER);
    printf("Saved Successfully!\n");
    in.userCount++;
    saveData(&in, sizeof(Index), 1, INDEX);
}







void datacreator()
{
    int n = 0,godNumber;
    printf("Enter God Number : ");
    scanf(" %d", &godNumber);
    if(godNumber != 17)
    {
        return;
    }
    while (TRUE)
    {
        
        printf("WELCOME TO GOD MODE\n");
        printf("1 - USER SAVE ADDITIONAL\n");
        printf("2 - USER LOAD ALL\n");
        printf("3 - USER ADD SPECIFIC\n");
        printf("4 - BOOK SAVE ADDITIONAL\n");
        printf("5 - BOOK LOAD ALL\n");
        printf("6 - BOOK ADD SPECIFIC\n");
        printf("7 - EXIT\n\n");
        printf("Enter Number\n");
        scanf(" %d", &n);
        switch (n)
        {
        case 1:
            usersaveAdditional();
            break;
        case 2:
            userLoadAll();
            break;
        case 3:
            userAddSpecific();
            break;
        case 4:
            bookSaveAdditional();
            break;
        case 5:
            bookloadAll();
            break;
        case 6:
            bookAddSpecific();
            break;
        case 7:
            return;
        default:
            break;
        }
        getchar();
        getchar();
        system("clear");
    }
    
}


