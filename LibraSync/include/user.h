#include "utility.h"

void AddUser(User);
void UpdateUsers();
void LoadUsers();
void printUser(User*);
void printUserIndex();
void printUsersList();
int CompareUsers(User,User);
void AskRemoveUser(int, User*);
void RemoveUser(User);
void AskUserDetailsForAdding();
void SearchUser(char*,int);
void UserbyName();
void UserbyRollNumber();
void InputSearchUser();
void RemoveSingleUser();
void RemoveMultipleUser();
void RemoveAllUsers();

User* SelectUser();