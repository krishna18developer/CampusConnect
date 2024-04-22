#include "constants.h"
#include <stddef.h>


#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
typedef struct
{
    char *data;
}
Index;


typedef struct
{
    char UUID[MAXINPUTSIZE];
    char privilege[MAXINPUTSIZE];
    char name[MAXINPUTSIZE];
    char password[MAXINPUTSIZE];
}
User;

typedef struct
{
    char UUID[MAXINPUTSIZE];
    char name[MAXINPUTSIZE];
    char author [MAXINPUTSIZE];
    char genre[MAXINPUTSIZE];
    float price;
    int publishedYear;
    int numberOfCopies;
    int numberOfPeopleBorrowed;
    User* borrowedPeople;
}
Book;


#endif 



//void loadData(int dataType, void *in); 
int loadData(void *data, size_t size,int n,int dataType);
void saveData(void *data, size_t size,int n,int dataType);
int ParseCommand(char *command);
void UpperCase(char *input);
void wipeOut();
int takeCommand(char *command);
char* LowerCase(char *in);
