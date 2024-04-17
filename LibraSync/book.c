#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "include/book.h"
#include "include/constants.h"
#include <string.h>

int top = -1;
Book *books = NULL;
Book* foundBooks;
int numberOfBooks = 0, numberOfFoundBooks = 0;
char* BOOKFILEINPUTSTRING  = "{Name : %[^\n] },{Author : %[^\n] },{Genre : %[^\n] },{Price : %f },{PublishedYear : %d };\n";
char* BOOKFILEREMOVALSTRING  = "{Name : %s\n },{Author : %s\n },{Genre : %s\n },{Price : %f },{PublishedYear : %d };\n" ;

void AddBook(Book* book)
{
    FILE *file;

    file = fopen("books.txt", "a");
    if(file == NULL)
    {
        printf("Unable To Create Book.\nPlease Try Again.\n");
        return;
    }
 
    fprintf(file, BOOKFILEREMOVALSTRING , book->name, book->author, book->genre, book->price, book->publishedYear);
    printf("AddedBook!");
    fclose(file);
}

void RemoveSingleBook()
{
    int option = 1;
    printf("Enter Number Of The Book You Would Like To Remove : ");
    scanf("%d", &option);
    RemoveBook(option);
}

void RemoveBook(int option)
{
    char rem[300],rem2[300],rem3[300];
    if(option < 1)
    {
        printf("Invalid Option!");
        getchar();
        return;
    }
    Book *book = foundBooks + --option;
   // sprintf(rem, BOOKFILEREMOVALSTRING , book->name, book->author, book->genre, book->price, book->publishedYear);
   // printf("rem {%d}: %s\n", option , rem);
    Book *newSetOfBooks = (Book*) calloc(--numberOfBooks, sizeof(Book));
    int k = 0;
    for(int i = 0; i < numberOfBooks; i++)
    {

        //book - Found Book - Current Book to be removed
        //b - total book list at index i
        FILE *file;

        file = fopen("books.txt", "w");
        if(file == NULL)
        {
            printf("Unable To Remove Books.\nPlease Try Again.\n");
            return;
        }
 
        Book *b = books + i;
        sprintf(rem, BOOKFILEREMOVALSTRING , book->name, book->author, book->genre, book->price, book->publishedYear);
        sprintf(rem2, BOOKFILEREMOVALSTRING , b->name, b->author, b->genre, b->price, b->publishedYear);
        
        //printf("rem : %s\nrem2: %s\n", rem,rem2);

        
        if(strcmp(rem,rem2) == 0)
        {
            printf("\n EXEC");
            //sprintf(rem3, BOOKFILEREMOVALSTRING , book->name, book->author, book->genre, book->price, book->publishedYear);
            //numberOfBooks--;
            //printf("%s\n", rem3);
        }
        else 
        {
           //fprintf(file, BOOKFILEINPUTSTRING , b->name, b->author, b->genre, b->price, b->publishedYear);
           //printf("%s\n", rem3);

          *(newSetOfBooks + k) = *b;
          k++;
        }
        
        fclose(file);
    }
    books = newSetOfBooks;
}


void RemoveMultipleBook()
{
    int numberOfBooksToRemove = 1;
    printf("Enter Number Of The Books You Would Like To Remove : ");
    scanf("%d", &numberOfBooksToRemove);

    int BooksToRemove[numberOfBooksToRemove];

    int *i = (int*) calloc(numberOfBooksToRemove, sizeof(int));

    printf("Enter Numbers of those books seperated by space\n");
    for(int i = 0; i < numberOfBooksToRemove; i++)
    scanf("%d", BooksToRemove + i);

    for(int i = 0; i < numberOfBooksToRemove; i++)
    RemoveBook(BooksToRemove[i]);

    printf("Remaining\n");
    for(int i = 0; i < numberOfBooks;i++)
    {
        Book *book = books + i;
        AddBook(book);
        printf("Name: %s\nAuthor: %s\nGenre: %s\nPrice: %.2f\nPublished Year: %d\n\n", book->name, book->author, book->genre, book->price, book->publishedYear);
    }
    

    getchar();
    getchar();
}

void RemoveAllBooks()
{
    char option[10];
    printf("Are You Sure You Want To Remove All The Books Data Present?\nEnter 'DELETE' To Erase All Books\n");
    getchar();
    scanf("%s", option);
    if(strstr(option, "DELETE") != NULL)
    {
        FILE *file;

        file = fopen("books.txt", "w");
        if(file == NULL)
        {
            printf("Unable To Remove Books Data.\nPlease Try Again.\n");
            return;
        }
        fclose(file);
        printf("Deleted All The Books Data Successfully!");
        getchar();
    }
    else
    {
        printf("Wrong Confirmation Code!\nDid Not Delete The Books Data!\n");
    }
}
void AskRemoveBook()
{
    char option;
    printf("1)Remove Single Book\t\t2)Remove Multiple Books\n3)Remove All The Books\t\tPress Enter To Exit\n");
    option = getchar();

    switch (option)
    {
        case '1':
        RemoveSingleBook();
        break;
        case '2':
        RemoveMultipleBook();
        break;
        case '3':
        RemoveAllBooks();
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

    /* STOPPED PRINTING
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
    numberOfFoundBooks = 0;
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

    AskRemoveBook();
    system("clear");
    numberOfBooks = 0;
    foundBooks = books; // FOR FREEING THE FOUNDBOOKS
    free(books);
}