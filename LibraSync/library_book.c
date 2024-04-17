#include "include/utility.h"
#include "include/constants.h"
#include "include/library_book.h"
#include "include/book.h"
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
            InputAddBook();
            break;

            case REMOVEBOOK:
            printf("Remove !!!!!!\n");
            break;

            case SEARCHBOOK:
            InputSearchBook();
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

void InputAddBook()
{
    Book book;
    printf("\nEnter Details of The Book\n");
    printf("Name : ");
    scanf(" %s", book.name);
    printf("Author : ");
    scanf(" %s", book.author);
    printf("Price : ");
    scanf(" %f", &book.price);
    printf("Published Year : ");
    scanf(" %d", &book.publishedYear);
    printf("Genre : ");
    scanf(" %s", book.genre);

    AddBook(&book);

}
void byName()
{
    char *in;
    printf("Enter Name : ");
    scanf(" %[^\n]%*c", in);
    SearchBookByName(in);
}
void byAuthor()
{
    char *in;
    printf("Enter Author : ");
    scanf(" %[^\n]%*c", in);
    SearchBookByAuthor(in);
}
void byGenre()
{
    char *in;
    printf("Enter Genre : ");
    scanf(" %[^\n]%*c", in);
    SearchBookByGenre(in);
}
void InputSearchBook()
{
    printf("Search By\n1)Name\t\t2)Author\t\t3)Genre\n");
    int option;
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        byName();
        break;
    case 2:
        byAuthor();
        break;
    case 3:
        byGenre();
        break;
    default:
        break;
    }
    
}
