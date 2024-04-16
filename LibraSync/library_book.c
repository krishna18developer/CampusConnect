#include "include/utility.h"
#include "include/constants.h"
#include <stdio.h>
#include <stdlib.h>

//int exitClearance = FALSE

void bookMenu()
{
    int k = 0;
    char command [COMMAND_MAX_SIZE];
    system("clear");
    do
    {
        printf("\n\n");
        printf("\t     CODE\t\t\tFUNCTION\n");
        printf("\t     MAINMENU\t\t\tMain Menu\n");
        printf("\t     ADDBOOK\t\t\tAdd Book\n");
        printf("\t     REMOVEBOOK\t\t\tRemove Book\n");
        printf("\t     SEARCHBOOK\t\t\tSearch Book\n");
        switch (takeCommand(command))
        {
            case ADDBOOK:
            //exitClearance = TRUE;
            break;

            case REMOVEBOOK:
            printf("Remove !!!!!!\n");
            break;

            case SEARCHBOOK:
            printf("search !!!!!!\n");
            break;

            case CLEAR:
            system("clear");
            break;

            case MAINMENU:
            k=1;
            break;

            default:
            printf("Unknown Command\n");
            break;
        }

        if(k==1)
        {
            break;
        }
    }
    while (1);
}

void addBook()
{
    Book book;
    printf("\nEnter Details of The Book\n");
    printf("Name : ");
    scanf("%s", book.name);
    getchar();
    printf("Author : ");
    scanf("%s", book.author);
    getchar();
    printf("Name : ");
    scanf("%s", book.name);
    getchar();
    printf("Name : ");
    scanf("%s", book.name);
    getchar();
    printf("Name : ");
    scanf("%s", book.name);
    getchar();
}
