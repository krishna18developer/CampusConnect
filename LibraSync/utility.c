#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/constants.h"

char *getFileName(int k)
{
    switch (k)
    {
    case USER:
        return strcat("book",strcat("s",".bin"));
    case BOOK:
        return "books.bin";
        break;
    default:
        break;
    }
    return "blank.bin";
}

// When Saving Structure Array, Multiply The Size With Number of Elements
void saveData(void *data, size_t size,int dataType) 
{
    char filepath[100];
    char *fileName = getFileName(dataType);
    snprintf(filepath, sizeof(filepath), "%s/%s", "data", fileName);
    FILE *file = fopen(filepath, "wb");
    if (file == NULL) 
    {
        perror("Error opening file");
        return;
    }
    fwrite(data, size, 1, file);
}

void loadData(void *data, size_t size,int dataType) 
{
    char filepath[100];
    char *fileName = getFileName(dataType);
    snprintf(filepath, sizeof(filepath), "%s/%s", "data", fileName);
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) 
    {
        perror("Error opening file");
        return;
    }
    fread(data, size, 1, file);
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