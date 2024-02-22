#include <stdio.h>
#include <stdlib.h>
#include "include/utility.h"
#include "include/constants.h"

void mainMenu(int);
int takeCommand(char *);

int main()
{
    //system("clear"); //Used For Clearing Screen, Only works when stdlib.h is included

    char command [COMMAND_MAX_SIZE];

    mainMenu(CLEAR_SCREEN);
    
    /*
    scanf(" %s", command);

    UpperCase(command);
    int result = ParseCommand(command);
    */
    switch (takeCommand(command))
    {
    case USER:
        printf("User !!!!!!\n");
        break;
    case BOOK:
        printf("Book !!!!!!\n");
        break;
    case EXIT:
        exit(0);
    default:
        printf("Boring Default :)");
        break;
    }
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

}
int takeCommand(char *command)
{
    printf("\nCommand : ");
    scanf(" %s", command);

    UpperCase(command);
    return ParseCommand(command);
}