#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/constants.h"
#include "include/utility.h"
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stddef.h>
#include <ctype.h>
#include <stdint.h>
#include <time.h>



void clearScreen()
{
    char *clearcommand;
#ifdef _WIN32 
    clearcommand = "cls";
  
// Checking for mac OS with 
// __APPLE__ macro 
#elif __APPLE__ 
    clearcommand = "clear";
  
// Checking for linux OS with 
// __linux__ macro 
#elif __linux__ 
    clearcommand = "clear";

#endif
    system(clearcommand);
}

// Generate a random number between 0 and 255
uint8_t generate_random_byte()
{
    return (uint8_t)rand();
}
// Generate a UUID version 4
char* generate_uuid_v4() 
{
    //srand((unsigned int)time(NULL));
    char *uuid_str = (char*) calloc(UUIDSIZE, sizeof(char));
    //static char uuid_str[UUIDSIZE];
    // Set version (4) and variant (10xx)
    sprintf(uuid_str, "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
            generate_random_byte(), generate_random_byte(), generate_random_byte(), generate_random_byte(),
            generate_random_byte(), generate_random_byte(),
            0x40 | (generate_random_byte() & 0x0F), generate_random_byte() & 0x3F,
            generate_random_byte(), generate_random_byte(),
            generate_random_byte(), generate_random_byte(), generate_random_byte(), generate_random_byte(), generate_random_byte(), generate_random_byte());

    return uuid_str;
}

char locfileName[100];
char *getFileName(int n, int fileType)
{
    
    char *prefix;
    switch (fileType)
    {
    case USER:
        prefix = "users-";
        break;
    case BOOK:
        prefix = "books-";
        break;
    case INDEX:
        return "index.bin";
    default:
        return "blank.bin";
    }
    snprintf(locfileName, sizeof(locfileName), "%s%d%s", prefix, n, ".bin");
    return locfileName;
}
char *getFolderName(int folderType)
{
    switch (folderType)
    {
    case USER:
        return "users";
    case BOOK:
        return "books";
    case INDEX:
        return "index";
    default:
        break;
    }
    return "blank";
}
void checkDestination(char *folder)
{
    #if defined(_WIN32) || defined(_WIN64)
        if (_mkdir(folder) != 0) {
    #else
        if (mkdir(folder, 0777) != 0) { // 0777 is the permission mode for the directory
    #endif
        perror("Error creating directory");
        return;
    }
}
int directoryExists(const char *path) {
    DIR *dir = opendir(path);
    if (dir != NULL) {
        closedir(dir);
        return 1; // Directory exists
    } else {
        if (errno == ENOENT)
            return 0; // Directory does not exist
        else {
            perror("Error opening directory");
            exit(EXIT_FAILURE);
        }
    }
}
int ParseCommand(char *command)
{
    int k = DEFAULT;
    if(strcmp(command, "BOOK") == 0 || strcmp(command, "BK") == 0)
    {
        k = BOOK;
    }
    else if(strcmp(command, "USER") == 0)
    {
        k = USER;
    }
    else if(strcmp(command, "EXIT") == 0 || strcmp(command, "BREAK") == 0)
    {
        k = EXIT;
    }
    else if(strcmp(command, "CLEAR") == 0 || strcmp(command, "CLS") == 0)
    {
        k = CLEAR;
    }
    else if(strcmp(command, "MAIN") == 0 || strcmp(command, "MAINMENU") == 0 || strcmp(command, "MENU") == 0)
    {
        k = MAINMENU;
    }
    else if(strcmp(command, "ADDBOOK") == 0 || strcmp(command, "BOOKADD") == 0 )
    {
        k = ADDBOOK;
    }
     else if(strcmp(command, "REMOVEBOOK") == 0 || strcmp(command, "BOOKREMOVE") == 0 )
    {
        k = REMOVEBOOK;
    }
     else if(strcmp(command, "SEARCHBOOK") == 0 || strcmp(command, "BOOKSEARCH") == 0 || strcmp(command, "SB") == 0 )
    {
        k = SEARCHBOOK;
    }
     else if(strcmp(command, "ALLBOOK") == 0 || strcmp(command, "BOOKALL") == 0 || strcmp(command, "AB") == 0 )
    {
        k = ALLBOOK;
    }
    else if(strcmp(command, "ADDUSER") == 0 || strcmp(command, "USERADD") == 0 )
    {
        k = ADDUSER;
    }
     else if(strcmp(command, "REMOVEUSER") == 0 || strcmp(command, "USERREMOVE") == 0 )
    {
        k = REMOVEUSER;
    }
     else if(strcmp(command, "SEARCHUSER") == 0 || strcmp(command, "USERSEARCH") == 0)
    {
        k = SEARCHUSER;
    }
     else if(strcmp(command, "ALLUSER") == 0 || strcmp(command, "USERALL") == 0)
    {
        k = ALLUSER;
    }
    return k;
}

void UpperCase(char *input)
{
    for (int i = 0; *(input+i) !='\0' ; i++) 
    {
      if(*(input+i) >= 'a' && *(input+i) <= 'z') 
      {
        *(input+i) = *(input+i) - 32;
      }
   }
}
char* LowerCase(char *in)
{
    char* output = (char*)calloc(strlen(in),sizeof(char));
    if(output == NULL)
    {
        printf("An Unknow Error Occured While String Conversion!\n");
        return NULL;
    }
    for (int i = 0; *(in+i) !='\0' ; i++) 
    {
        *(output+i) = tolower(*(in+i));
    }

    return (output);
}
int takeCommand(char *command)
{
    printf("\nCommand : ");
    scanf(" %s", command);

    UpperCase(command);
    return ParseCommand(command);
}

void memallocBook(Book *b)
{
    b->name = (char*)calloc(MAXINPUTSIZE, sizeof(char));
    b->author = (char*)calloc(MAXINPUTSIZE, sizeof(char));
    b->genre = (char*)calloc(MAXINPUTSIZE, sizeof(char));

    for(int i = 0 ; i < b->numberOfPeopleBorrowed; i++)
    {
        (b->borrowedPeople + i )->UUID = (char*)calloc(UUIDSIZE , sizeof(char));
    }
}
void memallocUser(User *b)
{
    b->name = (char*)calloc(MAXINPUTSIZE, sizeof(char));
    b->privilege = (char*)calloc(MAXINPUTSIZE, sizeof(char));
    b->password = (char*)calloc(MAXINPUTSIZE, sizeof(char));
}