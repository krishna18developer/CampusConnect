#include <stdio.h>
#include <stdlib.h>
#include "include/utility.h"
#include "include/constants.h"
#include "include/book.h"
#include "include/user.h"
#include "include/librasync.h"
#include <time.h>

int exitClearance = FALSE;
char *clearcommand;

User selectedUser;

int main()
{
    srand((unsigned int)time(NULL)); 

    //clearScreen(); //Used For Clearing Screen, Only works when stdlib.h is included
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
            userMenu();
            break;

            case BOOK:
            bookMenu();
            mainMenu(CLEAR_SCREEN);
            break;

            case CLEAR:
            clearScreen();
            break;

            case SHOWSELECTEDUSER:
            printUser(getSelectedUser());
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
void greetingBook()
{
    printf("\n\n");
    printf("\t     ****************************************\n");
    printf("\t     *                                      *\n");
    printf("\t     *                                      *\n");
    printf("\t     *     ----------------------------     *\n");
    printf("\t     *            BOOKS SECTION             *\n");
    printf("\t     *     ----------------------------     *\n");
    printf("\t     *                                      *\n");
    printf("\t     *                                      *\n");
    printf("\t     ****************************************\n");
    printf("\n\n");
}
void greetingUser()
{
    printf("\n\n");
    printf("\t     ****************************************\n");
    printf("\t     *                                      *\n");
    printf("\t     *                                      *\n");
    printf("\t     *     ----------------------------     *\n");
    printf("\t     *            USERS SECTION             *\n");
    printf("\t     *     ----------------------------     *\n");
    printf("\t     *                                      *\n");
    printf("\t     *                                      *\n");
    printf("\t     ****************************************\n");
    printf("\n\n");
}
void mainMenu(int clear)
{
    if(clear == CLEAR_SCREEN)
    clearScreen();

    greeting();
    printf("\t     CODE\t\t\tFUNCTION\n");
    printf("\t     BOOK\t\t\tBook Management\n");
    printf("\t     USER\t\t\tUser Management\n");
    printf("\t     CLEAR\t\t\tClear Screen\n");
    printf("\t     SUSER\t\t\tShow Selected User\n");

}
void bookMenu()
{
    //LoadBooks();
    int k = 0;
    char command [COMMAND_MAX_SIZE];
    clearScreen();
    
    do
    {
        greetingBook();
        printf("\n\n");
        printf("\t     CODE\t\t\tFUNCTION\n");
        printf("\t     MAINMENU\t\t\tMain Menu\n");
        printf("\t     ADDBOOK\t\t\tAdd Book\n");
        printf("\t     REMOVEBOOK\t\t\tRemove Book\n");
        printf("\t     SEARCHBOOK\t\t\tSearch Book\n");
        printf("\t     ALLBOOK\t\t\tDisplay All Book\n");
        printf("\t     SUSER\t\t\tShow Selected User\n");
        switch (takeCommand(command))
        {
            case EXIT:
            exitClearance = TRUE;
            break;

            case ADDBOOK:
            AskBookDetailsForAdding();
            break;

            case REMOVEBOOK:
            AskRemoveBook(TRUE);
            break;

            case SEARCHBOOK:
            InputSearchBook();
            break;

            case SHOWSELECTEDUSER:
            printUser(getSelectedUser());
            break;

            case ALLBOOK:
            //UpdateBooks();
            printBooksList();
            getchar();
            getchar();
            clearScreen();
            break;

            case CLEAR:
            clearScreen();
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
            mainMenu(CLEAR_SCREEN);
            break;
        }
    }
    while (exitClearance == FALSE);
}

void userMenu()
{
    //LoadBooks();
    int k = 0;
    char command [COMMAND_MAX_SIZE];
    clearScreen();  
    do
    {
        greetingUser();
        printf("\n\n");
        printf("\t     CODE\t\t\tFUNCTION\n");
        printf("\t     MAINMENU\t\t\tMain Menu\n");
        printf("\t     ADDUSER\t\t\tAdd User\n");
        printf("\t     REMOVEUSER\t\t\tRemove User\n");
        printf("\t     SEARCHUSER\t\t\tSearch User\n");
        printf("\t     ALLUSER\t\t\tDisplay All Users\n");
        printf("\t     SUSER\t\t\tShow Selected User\n");
        switch (takeCommand(command))
        {
            case EXIT:
            exitClearance = TRUE;
            break;
        
            case ADDUSER:
            AskUserDetailsForAdding();
            break;

            case REMOVEUSER:
            AskRemoveUser(TRUE,&selectedUser);
            break;

            case SEARCHUSER:
            InputSearchUser();
            break;

            case SHOWSELECTEDUSER:
            printUser(getSelectedUser());
            break;

            case ALLUSER:
            //UpdateBooks();
            printUsersList();
            getchar();
            getchar();
            clearScreen();
            break;

            case CLEAR:
            clearScreen();
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
            mainMenu(CLEAR_SCREEN);
            break;
        }
    }
    while (exitClearance == FALSE);
}

void setSelectedUser(User *in)
{
    selectedUser = *in;
}

User* getSelectedUser()
{
    return &selectedUser;
}