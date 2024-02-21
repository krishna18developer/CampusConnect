#include <stdio.h>
#include <stdlib.h>
#include "include/utility.h"
#include "include/constants.h"

void mainMenu();

int main()
{
    system("clear"); //Used For Clearing Screen, Only works when stdlib.h is included

    char command [COMMAND_MAX_SIZE];
    mainMenu();
    
    scanf(" %s", command);

    UpperCase(command);
    int result = ParseCommand(command);
    switch (result)
    {
    case USER:
        printf("User !!!!!!\n");
        break;
    case BOOK:
        printf("Book !!!!!!\n");
        break;
    default:
        printf("Boring Default :)");
        break;
    }
    return 0;
}

void mainMenu()
{
    printf("Welcome To LibraSync\n");
    printf("\tCODE\t\t\tFUNCTION\n");
    printf("\tBOOK\t\t\tBook Management\n");
    printf("\tUSER\t\t\tUser Management\n");
    printf("\n Waiting For The Command ......\n\n");
}