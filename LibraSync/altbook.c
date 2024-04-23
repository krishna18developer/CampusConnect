#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/utility.h"
#include "include/constants.h"
#include <time.h>

Book* TotalBooks;
char *fileOutputFormat = "{Name : %s\n },{Author : %s\n },{Genre : %s\n },{Price : %f },{PublishedYear : %d };\n";
char *fileInputFormat = "{Name : %[^\n] },{Author : %[^\n] },{Genre : %[^\n] },{Price : %f },{PublishedYear : %d };\n";

int totalNumberOfBooks = 0;

void AddBook(Book bookToBeAdded)
{
    bookToBeAdded.UUID = generate_uuid_v4();
    if(TotalBooks == NULL || totalNumberOfBooks == 0)
    {
        printf("AddBook() -> First book.\n");
        Book* NewBook = (Book*) malloc(1 * sizeof(Book));
        *NewBook = bookToBeAdded;
        TotalBooks = NewBook;
        totalNumberOfBooks = 1;
        printf("AddBook with UUID : %s\n", bookToBeAdded.UUID);
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
    *(NewBooks + totalNumberOfBooks++) = bookToBeAdded;
    printf("AddBook with UUID : %s\n", bookToBeAdded.UUID);
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
    for(int i = 0; i < totalNumberOfBooks; i++)
    {
        FILE* file;
        char fileName[UUIDSIZE+6];
        sprintf(fileName, "B-%s.txt", (TotalBooks + i)->UUID);
        file = fopen(fileName, "w");
        if(file == NULL)
        {
            printf("Unable To Update The Book with UUID : %s.\nPlease Try Again.", (TotalBooks + i)->UUID);
            return;
        }
        fprintf(file, "%s\n", (TotalBooks+i)->UUID);
        fprintf(file, "%s\n", (TotalBooks+i)->name);
        fprintf(file, "%s\n", (TotalBooks+i)->author);
        fprintf(file, "%s\n", (TotalBooks+i)->genre);
        fprintf(file, "%f\n", (TotalBooks+i)->price);
        fprintf(file, "%d\n", (TotalBooks+i)->publishedYear);
        fprintf(file, "%d\n", (TotalBooks+i)->numberOfCopies);
        fprintf(file, "%d\n", (TotalBooks+i)->numberOfPeopleBorrowed);
        for(int j = 0; j < (TotalBooks+i)->numberOfPeopleBorrowed; j++)
        {
            fprintf(file, "%s\n", ((TotalBooks+i)->borrowedPeople + j)->UUID);
        }
        fclose(file);
    }
}
void printBook(Book *book)
{
    printf("Book UUID : %s\n", book->UUID);
    printf("Book Name : %s\n", book->name);
    printf("Book Author : %s\n", book->author);
    printf("Book Genre : %s\n", book->genre);
    printf("Book Price : %f\n", book->price);
    printf("Book Copies : %d\n", book->numberOfCopies);
    printf("Book Borrowed Number : %d\n", book->numberOfPeopleBorrowed);
    printf("Book Published Year : %d\n", book->publishedYear);
    for (int j = 0; j < book->numberOfPeopleBorrowed; j++)
    {
        printf("Book Borrowed by : %s\n", (book->borrowedPeople + j)->UUID);
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
        printBook(TotalBooks + i);
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
    Book* NewBooks = (Book*) calloc((totalNumberOfBooks-1), sizeof(Book));
    int check = 0;
    for(int i = 0, k = 0 ; i < totalNumberOfBooks; i++)
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
void alt5()
{
    printf("alt5\n");
    Book btest1;
    btest1.name = "Edokati";
    btest1.author = "author";
    btest1.genre = "genre";
    btest1.price = 99.0f;
    btest1.publishedYear = 2024;
    btest1.numberOfCopies = 10;
    btest1.numberOfPeopleBorrowed = 3;
    btest1.borrowedPeople = (User*) calloc(btest1.numberOfPeopleBorrowed,sizeof(User));
    (btest1.borrowedPeople + 0)->UUID = generate_uuid_v4();
    (btest1.borrowedPeople + 1)->UUID = generate_uuid_v4();
    (btest1.borrowedPeople + 2)->UUID = generate_uuid_v4();
    printf("b1 : %s\nb2 : %s\n", (btest1.borrowedPeople + 0)->UUID,(btest1.borrowedPeople + 1)->UUID);
    printf("alt5\n");;

    AddBook(btest1);
    printBooksList();
    UpdateBooks();
}
void main()
{
    srand((unsigned int)time(NULL)); 
    printf("main\n");
    alt5();
}
