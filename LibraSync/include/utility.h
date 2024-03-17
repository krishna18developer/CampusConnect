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

int loadData(void *data, size_t size, int n, int dataType); 
void saveData(void *data, size_t size, int n, int dataType);
int ParseCommand(char *command);
void UpperCase(char *input);
void wipeOut();
