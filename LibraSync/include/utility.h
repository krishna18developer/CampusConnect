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
    char *UUID;
    char *privilege;
    char *name;
    char *password;
}
User;

typedef struct
{
    char *UUID;
    char *name;
    char *author;
    char *genre;
    float price;
    int publishedYear;
    int numberOfCopies;
    int numberOfPeopleBorrowed;
    User* borrowedPeople;
}
Book;


#endif 



int ParseCommand(char *command);
void UpperCase(char *input);
int takeCommand(char *command);
char* LowerCase(char *in);
char* generate_uuid_v4();
void memallocBook(Book*);
//char* generate_uuid_v4(char*);