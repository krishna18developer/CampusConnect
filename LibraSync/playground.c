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
    bookTest ptr = {0};
    printf("Enter Name - ");
    //fgets(ptr.name, sizeof(ptr.name), stdin);
    //scanf("%[^\n]%*c", ptr.name);
    scanf("%[^\n]s",ptr.name);
    printf("Enter Author - ");
    //fgets(ptr.author, sizeof(ptr.author), stdin);
    scanf(" %s", ptr.author);
    printf("Enter Age\n");
    scanf("%d", &ptr.age);
    saveData(&ptr,sizeof(bookTest), 2,BOOK);
    printf("Saved Data!");
}
void load()
{
    bookTest ptr = {0};
    loadData(&ptr,sizeof(bookTest), 2,BOOK);
    printf("Details Loaded!\n");
    printf("Name - %s\n", ptr.name);
    printf("Author - %s\n", ptr.author);
    printf("Age - %d\n", ptr.age);
    printf("Roll - %d\n", ptr.roll);
    printf("Test - %s\n", ptr.test);
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
    default:
        break;
    }
    return 0;
}

