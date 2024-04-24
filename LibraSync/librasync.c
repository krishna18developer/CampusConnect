#include <stdio.h>
#include <stdlib.h>
#include "include/utility.h"
#include "include/constants.h"
#include "include/book.h"
#include <time.h>

void mainMenu(int);
void bookMenu();
int takeCommand(char *);

int exitClearance = FALSE;

int main()
{
    srand((unsigned int)time(NULL)); 

    //system("clear"); //Used For Clearing Screen, Only works when stdlib.h is included

    char command [COMMAND_MAX_SIZE];

    mainMenu(CLEAR_SCREEN);
    do
    {
        switch (takeCommand(command))
        {
            case EXIT:
            exitClearance = TRUE;
            break;

            case USER:
            printf("User !!!!!!\n");
            break;

            case BOOK:
            bookMenu();
            mainMenu(CLEAR_SCREEN);
            break;

            case CLEAR:
            system("clear");
            break;

            case MAINMENU:
            mainMenu(CLEAR_SCREEN);
            break;

            default:
            printf("Unknown Command\n");
            break;
        }
    }
    while (exitClearance == FALSE);
    
    return 0;
}

void greeting()
{
    printf("\n\n");
    printf("\t     ****************************************\n");
    printf("\t     *                                      *\n");
    printf("\t     *                                      *\n");
    printf("\t     *     ----------------------------     *\n");
    printf("\t     *         WELCOME TO LIBRASYNC         *\n");
    printf("\t     *     ----------------------------     *\n");
    printf("\t     *                                      *\n");
    printf("\t     *                                      *\n");
    printf("\t     ****************************************\n");
    printf("\n\n");
}

void mainMenu(int clear)
{
    if(clear == CLEAR_SCREEN)
    system("clear");

    greeting();
    printf("\t     CODE\t\t\tFUNCTION\n");
    printf("\t     BOOK\t\t\tBook Management\n");
    printf("\t     USER\t\t\tUser Management\n");
    printf("\t     CLEAR\t\t\tClear Screen\n");

}
void bookMenu()
{
    //LoadBooks();
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
        printf("\t     ALLBOOK\t\t\tDisplay All Book\n");
        switch (takeCommand(command))
        {
            case ADDBOOK:
            AskBookDetailsForAdding();
            break;

            case REMOVEBOOK:
            printf("Remove !!!!!!\n");
            break;

            case SEARCHBOOK:
            InputSearchBook();
            break;

            case ALLBOOK:
            //UpdateBooks();
            printBooksList();
            getchar();
            getchar();
            system("clear");
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