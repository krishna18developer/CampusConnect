#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/utility.h"
#include "include/constants.h"
#include <time.h>
#include "include/user.h"
#include "include/librasync.h"

User* TotalUsers, *foundUsers;
Index* uIndex, UIndex;

int totalNumberOfUsers = 0, numberOfFoundUsers = 0;

void AddUser(User UserToBeAdded)
{
    UserToBeAdded.UUID = generate_uuid_v4();
    if(TotalUsers == NULL || totalNumberOfUsers == 0)
    {
        User* NewUser = (User*) malloc(1 * sizeof(User));
        Index* newUIndex = (Index*) malloc(1 * sizeof(Index));
        newUIndex->data = UserToBeAdded.UUID;
        uIndex = newUIndex;
        *NewUser = UserToBeAdded;
        TotalUsers = NewUser;
        totalNumberOfUsers = 1;
        return;
    }
    User* NewUsers = (User*) calloc((totalNumberOfUsers+1) ,sizeof(User));
    Index* newUIndex = (Index*) calloc((totalNumberOfUsers+1), sizeof(Index));
    if(NewUsers == NULL)
    {
        printf("Unable To Allocate Memory For Users.\n");
        return;
    }
    for(int i = 0 ; i < totalNumberOfUsers; i++)
    {
        *(NewUsers + i) = *(TotalUsers + i);
        (newUIndex + i)->data = (TotalUsers + i)->UUID;
    }
    (newUIndex + totalNumberOfUsers)->data = UserToBeAdded.UUID;
    *(NewUsers + totalNumberOfUsers++) = UserToBeAdded;
    free(TotalUsers);
    free(uIndex);
    uIndex = newUIndex;
    TotalUsers = NewUsers;
}

void UpdateUsers()
{
    if(TotalUsers == NULL)
    {
        printf("Unable To Update The Users.\nPlease Try Again.");
        return;
    }
    FILE* IFile;
    IFile = fopen("data/UIndex.txt","w");
    for(int i = 0; i < totalNumberOfUsers; i++) // 0 < 2
    {
        FILE* file;
        char fileName[UUIDSIZE+11];
        sprintf(fileName, "data/U-%s.txt", (TotalUsers + i)->UUID);
        file = fopen(fileName, "w");
        if(file == NULL)
        {
            printf("Unable To Update The User with UUID : %s.\nPlease Try Again.", (TotalUsers + i)->UUID);
            return;
        }
        fprintf(IFile,"%s\n", (uIndex+i)->data);

        fprintf(file, "%s\n", (TotalUsers+i)->UUID);
        fprintf(file, "%s\n", (TotalUsers+i)->privilege);
        fprintf(file, "%s\n", (TotalUsers+i)->name);
        fprintf(file, "%s\n", (TotalUsers+i)->password);
        fprintf(file, "%d\n", (TotalUsers+i)->rollnumber);
        fclose(file);
    }
    fclose(IFile);
}
void LoadUsers()
{
    totalNumberOfUsers = 0;
    if(TotalUsers!=NULL)
    {
        free(TotalUsers);
    }
    FILE *fp = fopen("data/UIndex.txt", "r");
    if(fp == NULL)
    {
        printf("Unable To Retrieve Users Index.\nPlease Try Again\n");
        return;
    }
    char c;
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
        totalNumberOfUsers += 1;

    ////printf("DEBUG() -> totalNumberOFUsers : %d\n", totalNumberOfUsers);
    rewind(fp);
    if(totalNumberOfUsers <= 0)
    {
        return;
    }
    uIndex = (Index*) calloc(totalNumberOfUsers, sizeof(Index));
    TotalUsers = (User*) calloc(totalNumberOfUsers, sizeof(User));

    for(int i = 0; i < totalNumberOfUsers; i++)
    {
        (uIndex+i)->data = (char*) calloc(UUIDSIZE, sizeof(char));
        fscanf(fp , "%s\n", (uIndex+i)->data);
        char fileName[UUIDSIZE+11];
        sprintf(fileName, "data/U-%s.txt", (uIndex+i)->data);
        ////printf("DEBUG() -> fileName: %s\n", fileName);
        FILE* file = fopen(fileName, "r");
        if(file == NULL)
        {
            printf("Unable To Open User File.\nPlease Try Again\n");
            return;            
        }
        (TotalUsers+i)->UUID = (char*) calloc(UUIDSIZE, sizeof(char));
        (TotalUsers+i)->privilege = (char*) calloc(MAXINPUTSIZE, sizeof(char));
        (TotalUsers+i)->name = (char*) calloc(MAXINPUTSIZE, sizeof(char));
        (TotalUsers+i)->password = (char*) calloc(MAXINPUTSIZE, sizeof(char));


        char *format1 = "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n";
        fscanf(file, format1, 
            (TotalUsers+i)->UUID,
            (TotalUsers+i)->privilege,
            (TotalUsers+i)->name,
            (TotalUsers+i)->password,
            &(TotalUsers+i)->rollnumber
        );
        fclose(file);
    }
}


void printUser(User *user)
{
    
    printf("\n\nUser UUID : %s\n", user->UUID);
    printf("User Privilege : %s\n", user->privilege);
    printf("User Name : %s\n", user->name);
    printf("User Roll Number : %d\n", user->rollnumber);
}
void printUserIndex()
{
    for (int j = 0; j < totalNumberOfUsers; j++)
    {
        printf("%d : %s\n", j, (uIndex + j)->data);
    }
}
void printUsersList()
{
    LoadUsers();
    if(TotalUsers == NULL)
    {
        printf("No Users Loaded To Display.\n");
        return;
    }
    printf("Number of Users : %d\n\n", totalNumberOfUsers);
    for(int i = 0; i < totalNumberOfUsers; i++)
    {
        printUser(TotalUsers + i);
    }
}
    

int CompareUsers(User b1, User b2)
{
    int UUIDCheck = (strcmp(b1.UUID,b2.UUID) == 0) ? TRUE: FALSE;
    int privilegeCheck = (strcmp(b1.privilege,b2.privilege) == 0) ? TRUE: FALSE;
    int nameCheck = (strcmp(b1.name,b2.name) == 0) ? TRUE: FALSE;
    int passwordCheck = (strcmp(b1.password,b2.password) == 0) ? TRUE: FALSE;
    int rollnumberCheck = b1.rollnumber == b2.rollnumber ? TRUE : FALSE;

    return nameCheck && privilegeCheck && nameCheck && passwordCheck && rollnumberCheck;
}

void RemoveUser(User UserToBeRemoved)
{
    //printf("DEBUG() -> RemoveUser()\n");
    printUser(&UserToBeRemoved);
    
    //printf("DEBUG() -> n - %d\n", totalNumberOfUsers);
    User* NewSetOfUsers = (User*) calloc((totalNumberOfUsers-1), sizeof(User));
    Index* newBIndex = (Index*) calloc((totalNumberOfUsers-1), sizeof(Index));
    
    //printf("DEBUG() -> RemoveUser()\n");
    if(NewSetOfUsers == NULL)
    {
        printf("Unable To Remove The User.\n");
        return;
    }
    int check = 0;
    for(int i = 0, k = 0 ; i < totalNumberOfUsers; i++)
    {
        if(CompareUsers(*(TotalUsers + i), UserToBeRemoved))
        {
            check = 1;
            continue;
        }
        *(NewSetOfUsers + k) = *(TotalUsers + i);     
        (newBIndex + k)->data = (char*) calloc(UUIDSIZE, sizeof(char));
        (newBIndex + k++)->data = (TotalUsers + i)->UUID;
    }

    //*(NewUsers + totalNumberOfUsers) = UserToBeRemoved;
    if(check)
    totalNumberOfUsers--;

    free(TotalUsers);
    free(uIndex);
    uIndex = newBIndex;
    TotalUsers = NewSetOfUsers;    
}

void AskUserDetailsForAdding()
{
    User b;
    memallocUser(&b);
    printf("Enter User Name: ");
    scanf(" %[^\n]", b.name);
    printf("Enter User Password: ");
    scanf(" %[^\n]", b.password);
    printf("Enter User Privilge: ");
    scanf(" %[^\n]", b.privilege);
    printf("Enter User Roll Number : ");
    scanf("%d", &b.rollnumber);
    
    AddUser(b);

    UpdateUsers();
    
}


void SearchUser(char* name,int type) //41
{
    LoadUsers();
    int found = FALSE;
    numberOfFoundUsers = 0;
    char *bookTypeIdentifier = "Roll Number";
    
    for(int i = 0; i < totalNumberOfUsers;i++)
    {
        
        User *user = TotalUsers + i;
        char *lName = LowerCase(name), *lB = LowerCase(user->name);
        switch (type)
        {
        case BYNAME:
            bookTypeIdentifier = "Name";
            break;
        case BYROLLNUMBER:
            sprintf(lB, "%d", user->rollnumber);
            break;
        case BYPRIVILEGELEVEL:
            bookTypeIdentifier = "Privilege";
            lB = LowerCase(user->privilege);
            break;
        default:
            break;
        }
        if(strstr(lB, lName) != NULL)
        {
            numberOfFoundUsers++;
            found = TRUE;
        }
        lB = lName;
        free(lName);
    }
    if(found == FALSE)
    {
        printf("No Books Found of %s %s ",bookTypeIdentifier, name);
        getchar();
        getchar();
        clearScreen();
        return;
    }
    foundUsers = (User*) calloc(numberOfFoundUsers, sizeof(User));
    for(int i = 0, k = 0; i < totalNumberOfUsers && k < numberOfFoundUsers;i++)
    {        
        User *user = TotalUsers + i;
        char *lName = LowerCase(name), *lB = LowerCase(user->name);
        switch (type)
        {
        case BYNAME:
            break;
        case BYROLLNUMBER:
            sprintf(lB, "%d", user->rollnumber);
            break;
        case BYPRIVILEGELEVEL:
            bookTypeIdentifier = "Privilege";
            lB = LowerCase(user->privilege);
            break;
        default:
            break;
        }
        if(strstr(lB, lName) != NULL)
        {
            *(foundUsers+k) = *user;
            k++; 
        }

        lB = lName;
        free(lName);
    }
    printf("\n");

    for(int i = 0; i < numberOfFoundUsers; i++)
    {
        printf("%d)", i + 1);
        printUser(foundUsers + i);
    }
    //AskRemoveBook(FALSE);
    //clearScreen();
    int optionMenu = 1;
    printf("1)Remove Menu\t\t2)Select User\n");
    getchar();
    scanf("%d", &optionMenu);
    switch (optionMenu)
    {

    case 2:
        setSelectedUser(SelectUser());
        break;

    default:
    case 1:
        AskRemoveUser(FALSE, getSelectedUser());
        break;
    }
    getchar();
    getchar();
    numberOfFoundUsers = 0; // FOR FREEING THE FOUNDBOOKS
    free(foundUsers);
    clearScreen();
}


void AskRemoveUser(int all, User* selected)
{
    if(all == TRUE)
    {
        LoadUsers();

        free(foundUsers);
        foundUsers = TotalUsers;
        numberOfFoundUsers = totalNumberOfUsers;
        printUsersList();
        getchar();
    }
    char option;
    
    if(selected == NULL)
    {
        printf("Select A User From User Menu and Then Try Again.\n");
        return;
    }

    printf("1)Remove Single User\t\t2)Remove Multiple Users\n3)Remove All The Users\nPress Enter To Exit\n");
    getchar();
    option = getchar();

    switch (option)
    {
        case '1':
        RemoveSingleUser();
        break;
        case '2':
        RemoveMultipleUser();
        break;
        case '3':
        RemoveAllUsers();
        break;
        case RETURNCHARACTER:
        default:
        break;
    }

}


void RemoveSingleUser()
{
    printf("Enter The Number Of User You Would Like To Remove : ");
    int option;
    scanf("%d", &option);
    if(option < 1 || option > numberOfFoundUsers)
    {
        printf("Invalid Option Entered!\n");
        return;
    }
    option--;

    User b = *(foundUsers + option);

    RemoveUser(b);
    UpdateUsers();
    printf("Deleted User\n");
    
}


void RemoveMultipleUser()
{
    int numberOfUsersToRemove = 1;
    printf("DEBUG() -> Number of found Users - %d\n", numberOfFoundUsers);
    printf("Enter Number Of The Users You Would Like To Remove : ");
    scanf("%d", &numberOfUsersToRemove);

    int UsersToRemove[numberOfUsersToRemove];

    int *i = (int*) calloc(numberOfUsersToRemove, sizeof(int));

    printf("Enter Numbers of those Users seperated by space\n");
    for(int i = 0; i < numberOfUsersToRemove; i++)
    {
        int option;
        scanf("%d", &option);
        if(option < 1 || option > numberOfFoundUsers)
        {
            printf("Invalid Option Enter Again.\n");
            i--;
            continue;
        }
        UsersToRemove[i] = --option;
    }
    

    for(int i = 0; i < numberOfUsersToRemove; i++)
    {
        User b = *(foundUsers + UsersToRemove[i]);
        RemoveUser(b);
    }

    UpdateUsers();

    getchar();
    getchar();
}
void RemoveAllUsers()
{
    char option[10];
    printf("Are You Sure You Want To Remove All The Users Data Present?\nEnter 'DELETE' To Erase All Users\n");
    getchar();
    scanf("%s", option);
    if(strstr(option, "DELETE") != NULL)
    {
        FILE *file;

        file = fopen("data/BIndex.txt", "w");
        if(file == NULL)
        {
            printf("Unable To Remove Users Data.\nPlease Try Again.\n");
            return;
        }
        fclose(file);
        printf("Deleted All The Users Data Successfully!");
        getchar();
    }
    else
    {
        printf("Wrong Confirmation Code!\nDid Not Delete The Users Data!\n");
    }
}

void UserbyName()
{
    char *in = calloc(MAXINPUTSIZE, sizeof(char));
    printf("Enter Name : ");
    scanf(" %[^\n]%*c", in);
    SearchUser(in, BYNAME);
    free(in);
}
void UserbyPrivilegeLevel()
{
    int option;
    printf("1 - Admin\t\t2 - Student\n");
    printf("Enter Privilege Level : ");
    scanf("%d", &option);
    switch (option)
    {
        case 1:
            SearchUser("admin", BYPRIVILEGELEVEL);
            break;
    
        case 2:
        default:
            SearchUser("student", BYPRIVILEGELEVEL);
            break;
    }
}
void UserbyRollNumber()
{
    char *in = calloc(MAXINPUTSIZE, sizeof(char));
    int n;
    printf("Enter Roll Number : ");
    scanf(" %d", &n);
    sprintf(in , "%d", n);
    SearchUser(in, BYROLLNUMBER);
    free(in);
}
void InputSearchUser()
{
    printf("Search By\n1)Name\t\t2)Roll Number\t\t3)Privilege Level\n");
    int option;
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        UserbyName();
        break;
    case 2:
        UserbyRollNumber();
        break;
    case 3:
        UserbyPrivilegeLevel();
        break;
    default:
        break;
    }
    
}

User* SelectUser()
{   
    int option;
    printf("Enter The Number of User You Would Like To Select : ");
    scanf("%d", &option);
    if(option < 1 || option > numberOfFoundUsers)
    {
        printf("Invalid Option Given.\nTry Again.\n");
        return NULL;
    }

    return (foundUsers + --option);
}