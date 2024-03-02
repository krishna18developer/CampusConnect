#include "include/utility.h"
#include "include/constants.h"
#include <stdio.h>

typedef struct 
{
    int id;
    int salary;
}
User;

void load()
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


void save()
{
    Index in = {0};

    loadData(&in, sizeof(Index), 1, INDEX);

    printf("Total Number of Users Present : %d\n", in.userCount);
    int n;
    printf("Enter Additonal Number of Users Required : ");
    scanf("%d", &n);
    int total = in.userCount + n;   // USER COUNT - 10

    User u[total];

    for(int i = in.userCount; i < total; i++)
    {
        printf("Enter Details For User - %d\n", i+1);
        printf("Enter ID : ");
        scanf("%d", &u[i].id);
        printf("Enter Salary : ");
        scanf("%d", &u[i].salary);
        saveData(&u[i],sizeof(User),i, USER);
        printf("Saved Successfully!\n");
        in.userCount++;
    }
    saveData(&in, sizeof(Index), 1, INDEX);

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
    default:
        break;
    }
    return 0;
}


