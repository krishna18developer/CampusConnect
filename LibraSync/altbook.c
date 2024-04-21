#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/utility.h"
#include "include/constants.h"

Book* TotalBooks;
char *fileOutputFormat = "{Name : %s\n },{Author : %s\n },{Genre : %s\n },{Price : %f },{PublishedYear : %d };\n";
char *fileInputFormat = "{Name : %[^\n] },{Author : %[^\n] },{Genre : %[^\n] },{Price : %f },{PublishedYear : %d };\n";

int totalNumberOfBooks = 0;

void AddBook(Book bookToBeAdded)
{
    if(TotalBooks == NULL)
    {
        Book* NewBook = (Book*) calloc(1,sizeof(Book));
        *NewBook = bookToBeAdded;
        TotalBooks = NewBook;
        totalNumberOfBooks = 1;
        return;
    }
    Book* NewBooks = (Book*) calloc((totalNumberOfBooks+1) ,sizeof(Book));
    if(NewBooks == NULL)
    {
        printf("Unable To Allocate Memory For Books.\n");
        return;
    }
    for(int i = 0 ; i < totalNumberOfBooks; i++)
    {
        *(NewBooks + i) = *(TotalBooks + i);
    }
    
    *(NewBooks + ++totalNumberOfBooks) = bookToBeAdded;
    free(TotalBooks);
    TotalBooks = NewBooks;
}

void UpdateBooks()
{
    if(TotalBooks == NULL)
    {
        printf("Unable To Update The Books.\nPlease Try Again.");
        return;
    }
    FILE* file;
    file = fopen("bookstest.txt","w");
    if(file == NULL)
    {
        printf("Unable To Update The Books.\nPlease Try Again.");
        return;
    }
    char* bookFormat;
    for(int i = 0; i < totalNumberOfBooks; i++)
    {
        fprintf(file, fileOutputFormat,(TotalBooks+i)->name,(TotalBooks+i)->author,(TotalBooks+i)->genre,(TotalBooks+i)->price,(TotalBooks+i)->publishedYear);
    }
}
void printBooksList()
{
    if(TotalBooks == NULL)
    {
        printf("No Books Loaded To Display.\n");
        return;
    }
    printf("Number of Books : %d\n\n", totalNumberOfBooks);
    for(int i = 0; i < totalNumberOfBooks; i++)
    {
        printf("Book Name : %s\n", (TotalBooks + i)->name);
        printf("Book Author : %s\n", (TotalBooks + i)->author);
        printf("Book Genre : %s\n", (TotalBooks + i)->genre);
        printf("Book Price : %f\n", (TotalBooks + i)->price);
        printf("Book Published Year : %d\n\n", (TotalBooks + i)->publishedYear);
    }
}

int CompareBooks(Book b1, Book b2)
{
    int nameCheck = (strcmp(b1.name,b2.name) == 0) ? TRUE: FALSE;
    int authorCheck = (strcmp(b1.author,b2.author) == 0) ? TRUE: FALSE;
    int genreCheck = (strcmp(b1.genre,b2.genre) == 0) ? TRUE: FALSE;
    int priceCheck = b1.price == b2.price ? TRUE : FALSE;
    int publishedCheck = b1.publishedYear == b2.publishedYear ? TRUE : FALSE;

    return nameCheck && authorCheck && genreCheck && priceCheck && publishedCheck;
}

void RemoveBook(Book bookToBeRemoved)
{
    Book* NewBooks = (Book*) malloc((totalNumberOfBooks-1) * sizeof(Book));
    int check = 0;
    for(int i = 0, k = 0 ; k < totalNumberOfBooks; i++)
    {
        if(CompareBooks(*(NewBooks + i), bookToBeRemoved))
        {
            check = 1;
            continue;
        }
        *(NewBooks + k++) = *(TotalBooks + i);       
    }

    //*(NewBooks + totalNumberOfBooks) = bookToBeRemoved;
    if(check)
    totalNumberOfBooks--;

    free(TotalBooks);
    TotalBooks = NewBooks;    
}

void alt1()
{
    Book btest = {"Edoka Book!", "Nene", "Testing", 99, 2024};
    TotalBooks = (Book*) malloc(sizeof(Book));
    totalNumberOfBooks++;
    *TotalBooks = btest;

    UpdateBooks();
}
void alt2()
{
    Book btest1 = {"Edoka Book!", "Nene", "Testing", 99, 2024};
    Book btest2 = {"HElosa Book!", "Nene", "Testing", 99, 2024};
    TotalBooks = (Book*) malloc(2 * sizeof(Book));
    totalNumberOfBooks += 2;
    *(TotalBooks + 0) = btest1;
    *(TotalBooks + 1) = btest2;
    UpdateBooks();
}
void alt3()
{
    Book btest1 = {"Edoka Book!", "Nene", "Testing", 99.0f, 2024};
    Book btest2 = {"HElosa Book!", "Nene", "Testing", 99.0f, 2024};

    printf("Before Adding\n");
    printBooksList();
    AddBook(btest1);
    printf("After Adding 1\n");
    printBooksList();
    //UpdateBooks();
    AddBook(btest2);
    printf("After Adding 2\n");
    printBooksList();
    //UpdateBooks();

}
void alt4()
{
    Book btest1 = {"Edoka Book!", "Nene", "Testing", 99.0, 2024};
    Book btest2 = {"HElosa Book!", "iuttr", "Testing", 85.0, 212024};
    Book btest3 = {"dsafsaok!", "dsf", "Testing", 43.0, 6743};

    AddBook(btest1);
    AddBook(btest2);
    AddBook(btest3);
    
    UpdateBooks();
    printBooksList();

    printf("Now delete\n");
    RemoveBook(btest2);
    UpdateBooks();

    printBooksList();
    

}
void main()
{
    alt3();
}
