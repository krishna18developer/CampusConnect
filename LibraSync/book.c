#include "include/utility.h"
#include "include/constants.h"
#include "include/book.h"

void add()
{

}

void removeBook()
{

}

Book getBook(int n)
{
    Book b = {0};

    loadData(&b,sizeof(Book),(n-1), BOOK);

    return b;
}