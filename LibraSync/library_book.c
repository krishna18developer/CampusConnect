#include "include/book.h"
#include <stdio.h>


void displaybook(int n)
{
    Book boo = getBook(n);
    printf("Details of The Book Are : \n");
    printf("ID : %d\n", boo.id);
    printf("Cost : %d\n", boo.cost);
}

