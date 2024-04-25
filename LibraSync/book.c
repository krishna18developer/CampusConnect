#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/utility.h"
#include "include/constants.h"
#include <time.h>
#include "include/book.h"
#include "include/user.h"
#include "include/librasync.h"

Book* TotalBooks, *foundBooks;
Index* bIndex, UIndex;

int totalNumberOfBooks = 0, numberOfFoundBooks = 0;

void AddBook(Book bookToBeAdded)
{
    bookToBeAdded.UUID = generate_uuid_v4();
    if(TotalBooks == NULL || totalNumberOfBooks == 0)
    {
        Book* NewBook = (Book*) malloc(1 * sizeof(Book));
        Index* newBIndex = (Index*) malloc(1 * sizeof(Index));
        newBIndex->data = bookToBeAdded.UUID;
        bIndex = newBIndex;
        *NewBook = bookToBeAdded;
        TotalBooks = NewBook;
        totalNumberOfBooks = 1;
        return;
    }
    Book* NewBooks = (Book*) calloc((totalNumberOfBooks+1) ,sizeof(Book));
    Index* newBIndex = (Index*) calloc((totalNumberOfBooks+1), sizeof(Index));
    if(NewBooks == NULL)
    {
        printf("Unable To Allocate Memory For Books.\n");
        return;
    }
    for(int i = 0 ; i < totalNumberOfBooks; i++)
    {
        *(NewBooks + i) = *(TotalBooks + i);
        (newBIndex + i)->data = (TotalBooks + i)->UUID;
    }
    (newBIndex + totalNumberOfBooks)->data = bookToBeAdded.UUID;
    *(NewBooks + totalNumberOfBooks++) = bookToBeAdded;
    free(TotalBooks);
    free(bIndex);
    bIndex = newBIndex;
    TotalBooks = NewBooks;
}

void UpdateBooks()
{
    printf("DEBUG() -> UpdateBooks()\n");
    if(TotalBooks == NULL)
    {
        printf("Unable To Update The Books.\nPlease Try Again.");
        return;
    }
    FILE* IFile;
    IFile = fopen("data/BIndex.txt","w");
    printf("DEBUG() -> UpdateBooks() -> totalNumberOfBooks %d\n", totalNumberOfBooks);
    for(int i = 0; i < totalNumberOfBooks; i++) // 0 < 2
    {
        printf("DEBUG() -> UpdateBooks() -> LOOP %d\n", i);
        FILE* file;
        char fileName[UUIDSIZE+11];
        sprintf(fileName, "data/B-%s.txt", (TotalBooks + i)->UUID);
        file = fopen(fileName, "w");
        if(file == NULL)
        {
            printf("Unable To Update The Book with UUID : %s.\nPlease Try Again.", (TotalBooks + i)->UUID);
            return;
        }
        fprintf(IFile,"%s\n", (bIndex+i)->data);

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
            /*
            if((TotalBooks + i)->borrowedPeople == NULL)
            {
                continue;
            } 
            User* u = (TotalBooks + i)->borrowedPeople;
            if((u + j)->UUID == NULL)
            {
                printf("DEBUG()-> NULL");
            }
            fprintf(file, "%s\n", (u + j)->UUID);
            */
           printf("DEBUG() -> UUID : '%s'\n", ((TotalBooks + i)->borrowedPeople + j)->UUID);
           fprintf(file, "%s\n", ((TotalBooks + i)->borrowedPeople + j)->UUID);
        }
        fclose(file);
    }
    fclose(IFile);
}
void LoadBooks()
{
    totalNumberOfBooks = 0;
    if (TotalBooks != NULL)
    {
        free(TotalBooks);
    }
    FILE *fp = fopen("data/BIndex.txt", "r");
    if (fp == NULL)
    {
        printf("Unable To Retrieve Books Index.\nPlease Try Again\n");
        return;
    }
    char c;
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            totalNumberOfBooks += 1;

    ////printf("DEBUG() -> totalNumberOFBooks : %d\n", totalNumberOfBooks);
    rewind(fp);
    if (totalNumberOfBooks <= 0)
    {
        return;
    }
    bIndex = (Index *)calloc(totalNumberOfBooks, sizeof(Index));
    TotalBooks = (Book *)calloc(totalNumberOfBooks, sizeof(Book));

    for (int i = 0; i < totalNumberOfBooks; i++)
    {
        (bIndex + i)->data = (char *)calloc(UUIDSIZE, sizeof(char));
        fscanf(fp, "%s\n", (bIndex + i)->data);
        char fileName[UUIDSIZE + 11];
        sprintf(fileName, "data/B-%s.txt", (bIndex + i)->data);
        ////printf("DEBUG() -> fileName: %s\n", fileName);
        FILE *file = fopen(fileName, "r");
        if (file == NULL)
        {
            printf("Unable To Open Book File.\nPlease Try Again\n");
            return;
        }
        (TotalBooks + i)->UUID = (char *)calloc(UUIDSIZE, sizeof(char));
        (TotalBooks + i)->name = (char *)calloc(MAXINPUTSIZE, sizeof(char));
        (TotalBooks + i)->author = (char *)calloc(MAXINPUTSIZE, sizeof(char));
        (TotalBooks + i)->genre = (char *)calloc(MAXINPUTSIZE, sizeof(char));
        char *format1 = "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%f\n%d\n%d\n%d\n";
        char *format2 = "%s\n%s\n%s\n%s\n%f\n%d\n%d\n%d\n";
        fscanf(file, format1,
               (TotalBooks + i)->UUID,
               (TotalBooks + i)->name,
               (TotalBooks + i)->author,
               (TotalBooks + i)->genre,
               &(TotalBooks + i)->price,
               &(TotalBooks + i)->publishedYear,
               &((TotalBooks + i)->numberOfCopies),
               &((TotalBooks + i)->numberOfPeopleBorrowed));
        int numberOfPeopleBorrowed = (TotalBooks + i)->numberOfPeopleBorrowed;
        printf("DEBUG() -> numberOfPeopleBorrowed : %d\n", numberOfPeopleBorrowed);
        if (numberOfPeopleBorrowed == 0)
        {
            (TotalBooks + i)->borrowedPeople = NULL;
        }
        else
        {
            (TotalBooks + i)->borrowedPeople = (User *)calloc(numberOfPeopleBorrowed, sizeof(User));
            for (int j = 0; j < numberOfPeopleBorrowed; j++)
            {
                ((TotalBooks + i)->borrowedPeople + j)->UUID = (char *)calloc(UUIDSIZE, sizeof(char));
                fscanf(file, "%s\n", ((TotalBooks + i)->borrowedPeople + j)->UUID);
            }
            for (int j = 0; j < numberOfPeopleBorrowed; j++)
            {
                char fileName[UUIDSIZE + 11];
                sprintf(fileName, "data/U-%s.txt", ((TotalBooks + i)->borrowedPeople + j)->UUID);
                printf("DEBUG() -> fileName: %s\n", fileName);
                FILE *file2 = fopen(fileName, "r");
                if (file2 == NULL)
                {
                    printf("Unable To Open User File.\nPlease Try Again\n");
                    continue;
                }
                ((TotalBooks + i)->borrowedPeople + j)->privilege = (char *)calloc(MAXINPUTSIZE, sizeof(char));
                ((TotalBooks + i)->borrowedPeople + j)->name = (char *)calloc(MAXINPUTSIZE, sizeof(char));
                ((TotalBooks + i)->borrowedPeople + j)->password = (char *)calloc(MAXINPUTSIZE, sizeof(char));

                char *format1 = "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n";
                fscanf(file2, format1,
                       ((TotalBooks + i)->borrowedPeople + j)->UUID,
                       ((TotalBooks + i)->borrowedPeople + j)->privilege,
                       ((TotalBooks + i)->borrowedPeople + j)->name,
                       ((TotalBooks + i)->borrowedPeople + j)->password,
                       &((TotalBooks + i)->borrowedPeople + j)->rollnumber);
                fclose(file2);
            }
        }
    }
}

void printBook(Book *book)
{
    
    printf("\n\nBook UUID : %s\n", book->UUID);
    printf("Book Name : %s\n", book->name);
    printf("Book Author : %s\n", book->author);
    printf("Book Genre : %s\n", book->genre);
    printf("Book Price : %.2f INR\n", book->price);
    printf("Book Published Year : %d\n", book->publishedYear);
    printf("Book Copies : %d\n", book->numberOfCopies);
    printf("Book Borrowed Number : %d\n", book->numberOfPeopleBorrowed);
    for (int j = 0; j < book->numberOfPeopleBorrowed; j++)
    {
        printf("Book Borrowed by : %s\n", (book->borrowedPeople + j)->name);
    }
}
void printBookIndex()
{
    for (int j = 0; j < totalNumberOfBooks; j++)
    {
        printf("%d : %s\n", j, (bIndex + j)->data);
    }
}
void printBooksList()
{
    LoadBooks();
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
    int UUIDCheck = (strcmp(b1.UUID,b2.UUID) == 0) ? TRUE: FALSE;
    int nameCheck = (strcmp(b1.name,b2.name) == 0) ? TRUE: FALSE;
    int authorCheck = (strcmp(b1.author,b2.author) == 0) ? TRUE: FALSE;
    int genreCheck = (strcmp(b1.genre,b2.genre) == 0) ? TRUE: FALSE;
    int priceCheck = b1.price == b2.price ? TRUE : FALSE;
    int publishedCheck = b1.publishedYear == b2.publishedYear ? TRUE : FALSE;

    return UUIDCheck && nameCheck && authorCheck && genreCheck && priceCheck && publishedCheck;
}

void RemoveBook(Book bookToBeRemoved)
{
    Book* NewSetOfBooks = (Book*) calloc((totalNumberOfBooks-1), sizeof(Book));
    Index* newBIndex = (Index*) calloc((totalNumberOfBooks-1), sizeof(Index));
    if(NewSetOfBooks == NULL)
    {
        printf("Unable To Remove The Book.\n");
        return;
    }
    int check = 0;
    for(int i = 0, k = 0 ; i < totalNumberOfBooks; i++)
    {
        if(CompareBooks(*(TotalBooks + i), bookToBeRemoved))
        {
            check = 1;
            continue;
        }
        *(NewSetOfBooks + k) = *(TotalBooks + i);     
        (newBIndex + k)->data = (char*) calloc(UUIDSIZE, sizeof(char));
        (newBIndex + k++)->data = (TotalBooks + i)->UUID;
    }

    //*(NewBooks + totalNumberOfBooks) = bookToBeRemoved;
    if(check)
    totalNumberOfBooks--;

    free(TotalBooks);
    free(bIndex);
    bIndex = newBIndex;
    TotalBooks = NewSetOfBooks;    
}

void AskBookDetailsForAdding()
{
    Book b;
    b.numberOfPeopleBorrowed = 0;
    memallocBook(&b);
    printf("Enter Book Name: ");
    scanf(" %[^\n]", b.name);
    printf("Enter Book Author: ");
    scanf(" %[^\n]", b.author);
    printf("Enter Book Genre: ");
    scanf(" %[^\n]", b.genre);
    printf("Enter Book Price: ");
    scanf("%f", &b.price);
    printf("Enter Book Published Year: ");
    scanf("%d", &b.publishedYear);
    printf("Enter Book Copies: ");
    scanf("%d", &b.numberOfCopies);
    
    AddBook(b);

    UpdateBooks();
    
}

void SearchBook(char* name,int type)
{
    LoadBooks();
    int found = FALSE;
    numberOfFoundBooks = 0;
    char *bookTypeIdentifier = "Author";
    
    for(int i = 0; i < totalNumberOfBooks;i++)
    {
        
        Book *book = TotalBooks + i;
        char *lName = LowerCase(name), *lB = LowerCase(book->name);
        switch (type)
        {
        case BYNAME:
            bookTypeIdentifier = "Name";
            break;
        case BYAUTHOR:
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
        clearScreen();
        return;
    }
    foundBooks = (Book*) calloc(numberOfFoundBooks, sizeof(Book));
    for(int i = 0, k = 0; i < totalNumberOfBooks && k < numberOfFoundBooks;i++)
    {        
        Book *book = TotalBooks + i;
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
        printf("%d)", i + 1);
        printBook(foundBooks + i);
    }
    int optionMenu = 1;
    printf("1)Remove Menu\t\t2)Borrow Menu\n");
    scanf("%d", &optionMenu);
    switch (optionMenu)
    {
    
    case 2:
        AskBorrowBook(FALSE);
        break;
    
    
    default:
        case 1:
            AskRemoveBook(FALSE);
            break;

    }
    //AskRemoveBook(FALSE);
    //clearScreen();
    numberOfFoundBooks = 0; // FOR FREEING THE FOUNDBOOKS
    free(foundBooks);
}


void AskBorrowBook(int all)
{
    if(all == TRUE)
    {
        LoadBooks();

        free(foundBooks);
        foundBooks = TotalBooks;
        numberOfFoundBooks = totalNumberOfBooks;
        printBooksList();
        getchar();
    }
    char option;
    if(getSelectedUser() == NULL)
    {
        printf("Select a User And try Again.\n");
        return;
    }

    printf("1)Borrow Single Book\t\t2)Borrow Multiple Books\t\tPress Enter To Exit\n");
    getchar();
    option = getchar();

    switch (option)
    {
        case '1':
        BorrowSingleBook();
        break;

        case '2':
        BorrowMultipleBook();
        break;

        case RETURNCHARACTER:
        default:
        break;
    }
}


void BorrowSingleBook()
{
    printf("Enter The Number Of Book You Would Like To Borrow : ");
    int option;
    scanf("%d", &option);
    if(option < 1 || option > numberOfFoundBooks)
    {
        printf("Invalid Option Entered!\n");
        return;
    }
    option--;

    printBook((foundBooks + option));
    BorrowBook(*(foundBooks + option));
    UpdateBooks();

}
void BorrowMultipleBook()
{

}
void BorrowBook(Book bookToBorrow)
{
    if(TotalBooks == NULL)
    {
        printf("Unable To Borrow The Book.\n");
        return;
    }
    int check = 0;
    Book* newSet = (Book*) calloc(totalNumberOfBooks, sizeof(Book));
    for(int i = 0 ; i < totalNumberOfBooks; i++)
    {
        if(CompareBooks(*(TotalBooks + i), bookToBorrow))
        {
            
            if(bookToBorrow.borrowedPeople == NULL)
            {
                bookToBorrow.borrowedPeople = (User*) malloc(sizeof(User));
                bookToBorrow.borrowedPeople = getSelectedUser();
                bookToBorrow.numberOfPeopleBorrowed = 1;
            }
            else
            {
                int n = bookToBorrow.numberOfPeopleBorrowed;
                User* newSetOfUsers = (User*) calloc((n+1), sizeof(User));
                if(newSetOfUsers == NULL)
                {
                    printf("Unknown Error Occured.\n");
                }
                for(int j = 0; j < n; j++)
                {
                    *(newSetOfUsers + j) = *(bookToBorrow.borrowedPeople + j);
                }
                *(newSetOfUsers + n) = *getSelectedUser();
                //printUser((TotalBooks + i)->borrowedPeople + n);
                free(bookToBorrow.borrowedPeople);
                bookToBorrow.borrowedPeople = newSetOfUsers;
                printf("numberOfPeopleBorrowed : %d\n", bookToBorrow.numberOfPeopleBorrowed);
                bookToBorrow.numberOfPeopleBorrowed++;
                printf("After + numberOfPeopleBorrowed : %d\n", bookToBorrow.numberOfPeopleBorrowed);
            }
            *(TotalBooks + i) = bookToBorrow;

        }
        *(newSet + i) = *(TotalBooks + i);
    }
    free(TotalBooks);
    TotalBooks = newSet;

    printf("DEBUG()-> Modified Book\n");
    printBook(&bookToBorrow); 
}

void OBorrowBook(Book *bookToBorrow)
{
    printf("DEBUG() -> Before.\n");
    printf("DEBUG() -> BorrowBook() -> numberOfPeopleBorrowed : %d\n",bookToBorrow->numberOfPeopleBorrowed);

    if(bookToBorrow->borrowedPeople == NULL)
    {
        printf("DEBUG() -> NULL\n");
        bookToBorrow->borrowedPeople = getSelectedUser();
        bookToBorrow->numberOfPeopleBorrowed = 1;
        printf("DEBUG() -> NULL\n");
        return;
    }
    bookToBorrow->numberOfPeopleBorrowed++;
    
    printf("DEBUG() -> After.\n");
}



void AskRemoveBook(int all)
{
    if(all == TRUE)
    {
        LoadBooks();

        free(foundBooks);
        foundBooks = TotalBooks;
        numberOfFoundBooks = totalNumberOfBooks;
        printBooksList();
        getchar();
    }
    char option;
    
    printf("1)Remove Single Book\t\t2)Remove Multiple Books\n3)Remove All The Books\t\tPress Enter To Exit\n");
    getchar();
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

void RemoveSingleBook()
{
    printf("Enter The Number Of Book You Would Like To Remove : ");
    int option;
    scanf("%d", &option);
    if(option < 1 || option > numberOfFoundBooks)
    {
        printf("Invalid Option Entered!\n");
        return;
    }
    option--;

    Book b = *(foundBooks + option);

    RemoveBook(b);
    UpdateBooks();
    printf("Deleted Book\n");
    
}


void RemoveMultipleBook()
{
    int numberOfBooksToRemove = 1;
    printf("DEBUG() -> Number of found Books - %d\n", numberOfFoundBooks);
    printf("Enter Number Of The Books You Would Like To Remove : ");
    scanf("%d", &numberOfBooksToRemove);

    int BooksToRemove[numberOfBooksToRemove];

    int *i = (int*) calloc(numberOfBooksToRemove, sizeof(int));

    printf("Enter Numbers of those books seperated by space\n");
    for(int i = 0; i < numberOfBooksToRemove; i++)
    {
        int option;
        scanf("%d", &option);
        if(option < 1 || option > numberOfFoundBooks)
        {
            printf("Invalid Option Enter Again.\n");
            i--;
            continue;
        }
        BooksToRemove[i] = --option;
    }
    

    for(int i = 0; i < numberOfBooksToRemove; i++)
    {
        Book b = *(foundBooks + BooksToRemove[i]);
        RemoveBook(b);
    }

    UpdateBooks();

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

        file = fopen("data/BIndex.txt", "w");
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

void BookbyName()
{
    char *in = calloc(MAXINPUTSIZE, sizeof(char));
    printf("Enter Name : ");
    scanf(" %[^\n]%*c", in);
    SearchBook(in, BYNAME);
    free(in);
}
void BookbyAuthor()
{
    char *in = calloc(MAXINPUTSIZE, sizeof(char));
    printf("Enter Author : ");
    scanf(" %[^\n]%*c", in);
    SearchBook(in, BYAUTHOR);
    free(in);
}
void BookbyGenre()
{
    char *in = calloc(MAXINPUTSIZE, sizeof(char));
    printf("Enter Genre : ");
    scanf(" %[^\n]%*c", in);
    SearchBook(in, BYGENRE);
    free(in);
}
void InputSearchBook()
{
    printf("Search By\n1)Name\t\t2)Author\t\t3)Genre\n");
    int option;
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        BookbyName();
        break;
    case 2:
        BookbyAuthor();
        break;
    case 3:
        BookbyGenre();
        break;
    default:
        break;
    }
    
}
/*
int main()
{
    LoadBooks();
    srand((unsigned int)time(NULL)); 
    printf("main\n");
    //AskBookDetailsForAdding();

    InputSearchBook();

    //UpdateBooks();

    return 0;

}

*/
void testF()
{
    if(TotalBooks == NULL)
    {
        printf("DEBUG() -> testF() -> TotalBooks NULL");
        return;
    }
    printf("DEBUG() -> testF() -> TotalBooks->UUID : %s\n", TotalBooks->UUID);
    printf("DEBUG() -> testF() -> TotalBooks->numberOfPeopleBorrowed : %d\n", TotalBooks->numberOfPeopleBorrowed);
    printf("DEBUG() -> testF() -> Incrementing\n");
    TotalBooks->numberOfPeopleBorrowed++;
    printf("DEBUG() -> testF() -> TotalBooks->numberOfPeopleBorrowed : %d\n", TotalBooks->numberOfPeopleBorrowed);
    UpdateBooks();
}