#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "include/book.h"
#include "include/constants.h"
#include <string.h>

Book *books = NULL;
int numberOfBooks = 0;

void AddBook(Book* book)
{
    FILE *file;

    file = fopen("books.txt", "a");
    if(file == NULL)
    {
        printf("Unable To Create Book.\nPlease Try Again.\n");
        return;
    }
 
    fprintf(file, "{Name : %s },{Author : %s },{Genre : %s },{Price : %f },{PublishedYear : %d };\n", book->name, book->author, book->genre, book->price, book->publishedYear);
    printf("AddedBook!");
    fclose(file);
}

void SearchBookByName(char* name)
{
    LoadBooks();
    int found = FALSE;
    Book* foundBooks;
    int numberOfFoundBooks = 0;
    for(int i = 0; i < numberOfBooks;i++)
    {
        
        Book *book = books + i;
        if(strcmp(name, book->name) == 0)
        {
            numberOfFoundBooks++;
            found = TRUE;
        }
    }
    if(found == FALSE)
    {
        printf("No Books Found of Name %s ", name);
        getchar();
        system("clear");
        numberOfBooks = 0;
        free(books);
        return;
    }
    foundBooks = (Book*) calloc(numberOfFoundBooks, sizeof(Book));
    for(int i = 0, k = 0; i < numberOfBooks && k < numberOfFoundBooks;i++)
    {
        
        Book *book = books + i;
        if(strcmp(name, book->name) == 0)
        {
            *(foundBooks+k) = *book;
            k++; 
        }
    }
    printf("\n");

    for(int i = 0; i < numberOfFoundBooks; i++)
    {
        Book *book = foundBooks + i;
        printf("Name: %s\nAuthor: %s\nGenre: %s\nPrice: %.2f\nPublished Year: %d\n\n", book->name, book->author, book->genre, book->price, book->publishedYear);
    }

    AskRemoveBook(foundBooks);
    system("clear");
    numberOfBooks = 0;
    free(books);
}
void SearchBookByAuthor(char* author)
{
    LoadBooks();
    int found = FALSE;
    Book* foundBooks;
    int numberOfFoundBooks = 0;
    for(int i = 0; i < numberOfBooks;i++)
    {
        
        Book *book = books + i;
        if(strcmp(author, book->author) == 0)
        {
            numberOfFoundBooks++;
            found = TRUE;
        }
    }
    if(found == FALSE)
    {
        printf("No Books Found of Author %s ", author);
        getchar();
        system("clear");
        numberOfBooks = 0;
        free(books);
        return;
    }
    foundBooks = (Book*) calloc(numberOfFoundBooks, sizeof(Book));
    for(int i = 0, k = 0; i < numberOfBooks && k < numberOfFoundBooks;i++)
    {
        
        Book *book = books + i;
        if(strcmp(author, book->author) == 0)
        {
            *(foundBooks+k) = *book;
            k++; 
        }
    }
    printf("\n");

    for(int i = 0; i < numberOfFoundBooks; i++)
    {
        Book *book = foundBooks + i;
        printf("Name: %s\nAuthor: %s\nGenre: %s\nPrice: %.2f\nPublished Year: %d\n\n", book->name, book->author, book->genre, book->price, book->publishedYear);
    }

    AskRemoveBook(foundBooks);
    system("clear");
    numberOfBooks = 0;
    free(books);
}
void SearchBookByGenre(char* genre)
{
    LoadBooks();
    int found = FALSE;
    Book* foundBooks;
    int numberOfFoundBooks = 0;
    for(int i = 0; i < numberOfBooks;i++)
    {
        
        Book *book = books + i;
        if(strcmp(genre, book->genre) == 0)
        {
            numberOfFoundBooks++;
            found = TRUE;
        }
    }
    if(found == FALSE)
    {
        printf("No Books Found of Genre %s ", genre);
        getchar();
        system("clear");
        numberOfBooks = 0;
        free(books);
        return;
    }
    foundBooks = (Book*) calloc(numberOfFoundBooks, sizeof(Book));
    for(int i = 0, k = 0; i < numberOfBooks && k < numberOfFoundBooks;i++)
    {
        
        Book *book = books + i;
        if(strcmp(genre, book->genre) == 0)
        {
            *(foundBooks+k) = *book;
            k++; 
        }
    }
    printf("\n");
    for(int i = 0; i < numberOfFoundBooks; i++)
    {
        Book *book = foundBooks + i;
        printf("Name: %s\nAuthor: %s\nGenre: %s\nPrice: %.2f\nPublished Year: %d\n\n", book->name, book->author, book->genre, book->price, book->publishedYear);
    }

    AskRemoveBook(foundBooks);
    system("clear");
    numberOfBooks = 0;
    free(books);
}

void RemoveSingleBook(Book *found)
{
    LoadBooks();
    for(int i = 0; i < numberOfBooks; i++)
    {
        
    }
}

void AskRemoveBook(Book *b)
{
    char option;
    printf("1)Remove Single Book\t\t2)Remove Multiple Books\n3)Remove All The Books\t\tPress Enter To Exit\n");
    option = getchar();

    switch (option)
    {
        case '1':
        RemoveSingleBook(b);
        break;
        case '2':
        RemoveSingleBook(b);
        break;
        case '3':
        RemoveSingleBook(b);
        break;
        case RETURNCHARACTER:
        default:
        break;
    }

}

void LoadBooks()
{
    numberOfBooks = 0;
    FILE *file;
    char ch;
    file = fopen("books.txt", "r");
    if(file == NULL)
    {
        printf("Unable To Load Book.\nPlease Try Again.\n");
        return;
    }

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == ';')
        {
            numberOfBooks++;
        }
    }
    books = (Book*) calloc(numberOfBooks,sizeof(Book));
    if(books == NULL)
    {
        printf("Unable To Load Book.\nPlease Try Again.\n");
        return;
    }
    rewind(file);
    int i, k = 0;
    do
    {
        Book *book = books + k;
        i = fscanf(file, "{Name : %[^\n] },{Author : %[^\n] },{Genre : %[^\n] },{Price : %f },{PublishedYear : %d };\n", book->name, book->author, book->genre, &book->price, &book->publishedYear);
        k++;
    }
    while(i == 5);

    /*
    for(int i = 0; i < numberOfBooks;i++)
    {
        Book *book = books + i;
       printf("Name: %s\nAuthor: %s\nGenre: %s\nPrice: %.2f\nPublished Year: %d\n\n", book->name, book->author, book->genre, book->price, book->publishedYear);
    }
    */
}