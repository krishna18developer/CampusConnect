#include <stdio.h>
#include <stdlib.h>
#include "include/utility.h"
#include "include/constants.h"
#include "include/library_book.h"

void mainMenu(int);
int takeCommand(char *);

int exitClearance = FALSE;

int main()
{
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