#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/constants.h"

char *getFileName(int k)
{
    switch (k)
    {
    case USER:
        return "users.bin";
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