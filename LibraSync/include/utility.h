#include "constants.h"
#include <stddef.h>

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
    int k;
}
Book;

typedef struct
{
    /* data */
    int k;
}
User;


void loadData(int dataType, void *in); 
void saveData(void *data, size_t size, int n, int dataType);
int ParseCommand(char *command);
void UpperCase(char *input);
void wipeOut();
