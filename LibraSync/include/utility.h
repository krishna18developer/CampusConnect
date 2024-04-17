#include "constants.h"
#include <stddef.h>


#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
typedef struct
{
    int bookCount;
    int userCount;

    int *books;
    size_t bookSize;

    int *users;
    size_t userSize;

}
Index;

typedef struct
{
    /* data */
    char name[MAXINPUTSIZE];
    char author [MAXINPUTSIZE];
    char genre[MAXINPUTSIZE];
    float price;
    int publishedYear;
}
Book;

typedef struct
{
    /* data */
    int k;
}
User;

#endif 



//void loadData(int dataType, void *in); 
int loadData(void *data, size_t size,int n,int dataType);
void saveData(void *data, size_t size,int n,int dataType);
int ParseCommand(char *command);
void UpperCase(char *input);
void wipeOut();
int takeCommand(char *command);
char* LowerCase(char *in);
