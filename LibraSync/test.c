#include <stdio.h>
#include "include/library_book.h"


int main()
{

    printf("Enter The Book Number : ");
    int bookNumber;
    scanf("%d", &bookNumber);

    displaybook(bookNumber);

    return 0;
}
