#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "include/book.h"
#include "include/constants.h"
#include <string.h>

Book *books = NULL;
int numberOfBooks = 0;
char* BOOKFILEINPUTSTRING  = "{Name : %[^\n] },{Author : %[^\n] },{Genre : %[^\n] },{Price : %f },{PublishedYear : %d };\n";
void AddBook(Book* book)
{
    FILE *file;

    file = fopen("books.txt", "a");
    if(file == NULL)
    {
        printf("Unable To Create Book.\nPlease Try Again.\n");
        return;
    }
 
    fprintf(file, BOOKFILEINPUTSTRING , book->name, book->author, book->genre, book->price, book->publishedYear);
    printf("AddedBook!");
    fclose(file);
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
        i = fscanf(file, BOOKFILEINPUTSTRING, book->name, book->author, book->genre, &book->price, &book->publishedYear);
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




void SearchBook(char* name,int type)
{
    LoadBooks();
    int found = FALSE;
    Book* foundBooks;
    int numberOfFoundBooks = 0;
    char *bookTypeIdentifier = "Author";
    
    for(int i = 0; i < numberOfBooks;i++)
    {
        
        Book *book = books + i;
        char *lName = LowerCase(name), *lB = LowerCase(book->name);
        switch (type)
        {
        case BYNAME:
            bookTypeIdentifier = "Name";
            break;
        case BYAUTHOR:
            bookTypeIdentifier = "Author";
            lB = LowerCase(book->author);
            break;
        case BYGENRE:
            bookTypeIdentifier = "Genre";
            lB = LowerCase(book->genre);
            break;  
        default:
            break;
        }
        if(strstr(lB, lName) != NULL)
        {
            numberOfFoundBooks++;
            found = TRUE;
        }
        lB = lName;
        free(lName);
    }
    if(found == FALSE)
    {
        printf("No Books Found of %s %s ",bookTypeIdentifier, name);
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
        char *lName = LowerCase(name), *lB = LowerCase(book->name);
        switch (type)
        {
        case BYNAME:
            break;
        case BYAUTHOR:
            lB = LowerCase(book->author);
            break;
        case BYGENRE:
            lB = LowerCase(book->genre);
            break;  
        default:
            break;
        }
        if(strstr(lB, lName) != NULL)
        {
            *(foundBooks+k) = *book;
            k++; 
        }
        lB = lName;
        free(lName);
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