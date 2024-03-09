#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct 
{
    char username;
    int id;
}User;

void adduser(char username,int id);
void save_userto_file(char usersdata);
void displayusers();
int main();