#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_BOOKS 100
#define MAX_USERS 10

struct Book 
{
    char title[100];
    char author[100];
    int ISBN;
};

struct Library 
{
    struct Book books[MAX_BOOKS];
    int count;
};

struct User 
{
    char username[50];
    char password[50];
};

struct UserDatabase 
{
    struct User users[MAX_USERS];
    int count;
};

int authenticateUser(struct UserDatabase *userDB, const char *username, const char *password) 
{
    for(int i = 0; i < userDB -> count; i++) 
    {
        if(strcmp(userDB->users[i].username, username) == 0 && strcmp(userDB->users[i].password, password) == 0)
            return 1; 
    }

    return 0;
}

void addUser(struct UserDatabase *userDB, const char *username, const char *password) 
{
    if(userDB -> count < MAX_USERS) 
    {
        strcpy(userDB->users[userDB->count].username, username);
        strcpy(userDB->users[userDB->count].password, password);
        userDB -> count++;
        printf("User added successfully!\n");
    } 
    
    else
        printf("User database is full. Cannot add more users.\n");
}

void displayMenu() 
{
    printf("\nLibrary Management System\n");
    printf("1. Sign Up\n");
    printf("2. Login\n");
    printf("3. Add Book\n");
    printf("4. Display Books\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

void addBook(struct Library *library) 
{
    if(library -> count < MAX_BOOKS) 
    {
        printf("\nEnter book details:\n");
        printf("Title: ");
        scanf(" %[^\n]s", library -> books[library -> count].title);
        printf("Author: ");
        scanf(" %[^\n]s", library -> books[library -> count].author);
        printf("ISBN: ");
        scanf("%d", &library -> books[library -> count].ISBN);

        library -> count++;
        printf("Book added successfully!\n");
    } 
    
    else
        printf("Library is full. Cannot add more books.\n");
}

void displayBooks(struct Library *library) 
{
    printf("\nLibrary Books:\n");
    
    for(int i = 0; i < library -> count; i++) 
    {
        printf("Title: %s\n", library -> books[i].title);
        printf("Author: %s\n", library -> books[i].author);
        printf("ISBN: %d\n\n", library -> books[i].ISBN);
    }
}

int main() 
{
    struct Library library;
    library.count = 0;

    struct UserDatabase userDB;
    userDB.count = 0;

    int choice;
    
    do 
    {
        displayMenu();
        scanf("%d", &choice);

        switch(choice) 
        {
            case 1:
                // Sign Up
                {
                    char username[50];
                    char password[50];
                    printf("\nEnter username: ");
                    scanf(" %[^\n]s", username);
                    
                    printf("Enter password: ");
                    scanf(" %[^\n]s", password);
                    
                    addUser(&userDB, username, password);
                }

                break;

            case 2:
                // Login
                {
                    char username[50];
                    char password[50];
                    printf("\nEnter username: ");
                    scanf(" %[^\n]s", username);
                    
                    printf("Enter password: ");
                    scanf(" %[^\n]s", password);

                    if(authenticateUser(&userDB, username, password)) 
                    {
                        printf("Login successful!\n");
                        do 
                        {
                            displayMenu();
                            scanf("%d", &choice);

                            switch(choice) 
                            {
                                case 3:
                                    addBook(&library);
                                    break;

                                case 4:
                                    displayBooks(&library);
                                    break;

                                case 5:
                                    printf("Exiting the program. Goodbye!\n");
                                    break;

                                default:
                                    printf("Invalid choice. Please try again.\n");
                            }

                        }
                        
                        while (choice != 5);
                    } 
                    
                    else
                        printf("Login failed. Invalid username or password.\n");
                }

                break;

            case 3:
                printf("Please login first.\n");
                break;

            case 4:
                printf("Please login first.\n");
                break;

            case 5:
                printf("Exiting the program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } 
    
    while(choice != 5);

    return 0;
}
