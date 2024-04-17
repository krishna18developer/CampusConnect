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
// When Saving Structure Array, Multiply The Size With Number of Elements
void saveData(void *data, size_t size,int n,int dataType)
{
    if (n <= 0)
    n = 0;

    char filepath[100];
    char *fileName = getFileName(n, dataType);
    char *folderName = getFolderName(dataType);
    snprintf(filepath, sizeof(filepath), "%s/%s/%s", "data", folderName,fileName);
    FILE *file = fopen(filepath, "wb");
    if (file == NULL) 
    {
        perror("Error opening file ");
        printf("%s\n", filepath);
        return;
    }
    fwrite(data, size, 1, file);
    fclose(file);
}
int loadData(void *data, size_t size,int n,int dataType) 
{
    if (n <= 0)
    n = 0;

    char filepath[100];
    char *fileName = getFileName(n, dataType);
    char *folderName = getFolderName(dataType);
    snprintf(filepath, sizeof(filepath), "%s/%s/%s", "data", folderName,fileName);
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) 
    {
        perror("Error opening file");
        printf("%s\n", filepath);
        return -1;
    }
    if(dataType == TEST)
    {
        Index *in = (Index*) data;
        fwrite(&in->books, sizeof(in->bookSize), 1, file);
        fwrite(&in->users, sizeof(in->userSize), 1, file);
        fwrite(in->books, sizeof(int), in->bookSize, file);
        return 0;
    }
    fread(data, size, 1, file);
    fclose(file);
    return 0;
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

void wipeOut()
{
    printf("ENTER CONFIRM TO REMOVE ALL THE USER DATA AND CREATE BLANK FILES\n");

    char confirm[8];
    scanf("%s", confirm);

    UpperCase(confirm);
    if(strcmp(confirm,"CONFIRM") != 0)
    {
        printf("INVALID COMMAND\n");
        return;
    }

    Index i = {0};

    saveData(&i, sizeof(Index), 1, INDEX);
    printf("DESTROYED\n");
}


int takeCommand(char *command)
{
    printf("\nCommand : ");
    scanf(" %s", command);

    UpperCase(command);
    return ParseCommand(command);
}