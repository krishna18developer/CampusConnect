#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/constants.h"
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

char *getFileName(int n, int fileType)
{
    char fileName[100];
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
    snprintf(fileName, sizeof(fileName), "%s%d%s", prefix, n, ".bin");
    return fileName;
}
char *getFolderName(int folderType)
{
    switch (folderType)
    {
    case USER:
        return "users";
    case BOOK:
        return "books";
    default:
        break;
    }
    return "blank";
}
typedef struct
{
    int bookCount;
    int userCount;
} Index;


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
    n = DEFAULT;

    char filepath[100];
    char *fileName = getFileName(n, dataType);
    char *folderName = getFolderName(dataType);
    snprintf(filepath, sizeof(filepath), "%s/%s/%s", "data", folderName,fileName);
    FILE *file = fopen(filepath, "wb");
    if (file == NULL) 
    {
        perror("Error opening file");
        return;
    }
    fwrite(data, size, 1, file);
}
void loadData(void *data, size_t size,int n,int dataType) 
{
    if (n <= 0)
    n = DEFAULT;

    char filepath[100];
    char *fileName = getFileName(n, dataType);
    char *folderName = getFolderName(dataType);
    snprintf(filepath, sizeof(filepath), "%s/%s/%s", "data", folderName,fileName);
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) 
    {
        perror("Error opening file");
        return;
    }
    fwrite(data, size, 1, file);
}

int ParseCommand(char *command)
{
    int k = DEFAULT;
    if(strcmp(command, "BOOK") == 0)
    {
        k = BOOK;
    }
    else if(strcmp(command, "USER") == 0)
    {
        k = USER;
    }
    else if(strcmp(command, "EXIT") == 0)
    {
        k = EXIT;
    }
    return k;
}

void UpperCase(char *input)
{
    for (int i = 0; *(input+i) !='\0' ; i++) 
    {
      if(*(input+i) >= 'a' && *(input+i) <= 'z') 
      {
        *(input+i) = *(input+i) -32;
      }
   }
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