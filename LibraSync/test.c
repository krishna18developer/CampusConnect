#include <stdio.h>
#include <string.h>

// Define a structure for a book
struct Book {
    char title[100];
    char author[100];
    int year;
};

// Function to print a single book
void printBook(struct Book book) {
    printf("Title: %-30s Author: %-20s Year: %d\n", book.title, book.author, book.year);
}

int main() {
    // Define two sample books
    struct Book book1, book2;
    strcpy(book1.title, "Book One");
    strcpy(book1.author, "Author One");
    book1.year = 2020;

    strcpy(book2.title, "Book Two");
    strcpy(book2.author, "Author Two");
    book2.year = 2018;

    // Print the two structures side by side
    printf("%-55s%-55s\n", "Book 1", "Book 2");
    printf("%-55s%-55s\n", "---------------------------", "---------------------------");
    printf("%-55s%-55s\n", "Title", "Title");
    printf("%-55s%-55s\n", "Author", "Author");
    printf("%-55s%-55s\n", "Year", "Year");
    printf("%-55s%-55s\n", "---------------------------", "---------------------------");
    printf("%-55s%-55s\n", book1.title, book2.title);
    printf("%-55s%-55s\n", book1.author, book2.author);
    printf("%-55d%-55d\n", book1.year, book2.year);

    return 0;
}
