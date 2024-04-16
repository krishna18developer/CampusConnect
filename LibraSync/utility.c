#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/constants.h"
#include "include/utility.h"

void loadData(int dataType, void *in)
{
    Book *data;
    if(dataType == BOOK)
    {
        data = (Book*) malloc(sizeof(Book));
    }
    data->k = 10;
    printf("k : %d\n", data->k);
    
}