#include "SignUp.c"
#include <stdbool.h>

int getLoginPassword(char *Pass)
{
    int i;
    char password[250];
    char ch;
StartOfgetpass:
    for (int i = 0; strlen(password); i++) password[i] = '\0';
    i = 0;
    // Show option to display password
    printf("\033[0;35m");
    printf("\nDo you want to show your password? (Y for Yes, N for No): ");
    printf("\033[0m");
   	char showPassword;
    char showPasswordInput[1000];
    fgets(showPasswordInput, 1000, stdin);
    showPasswordInput[strlen(showPasswordInput) - 1] = '\0';
    if (strlen(showPasswordInput) != 1)
    {
        printf("\033[0;31m");
        printf("Wrong Choice. Try again.\n");
        printf("\033[0m");
        goto StartOfgetpass;
    }
    showPassword = showPasswordInput[0]; 
    //clearInputBuffer(); // Clear input buffer

    if (tolower(showPassword) == 'y')
    {
        printf("\033[0;34m");
        printf("Enter your password : ");
        printf("\033[0m");
        fgets(password, 250, stdin);
        password[strlen(password) - 1] = '\0';
    }
    else if (tolower(showPassword) == 'n')
    {
        printf("\033[0;34m");
        printf("Enter your password : ");
        printf("\033[0m");
        while (1)
        {

            ch = getch();
            if (ch == '\n' || ch == '\r')
            {
                password[i] = '\0';
                break;
            }
            else if (ch == '\b')
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else
            {
                password[i++] = ch;
                printf("*");
            }
        }
    }
    else
    {
        printf("\033[0;31m");
        printf("Wrong Choice. Try again.");
        printf("\033[0m");
        i = 0;
        goto StartOfgetpass;
    }
    strcpy(Pass, password);
}

// Previous Check for existance functions but merged as in login we are checking that this exact username exist and the password associated to it is correct
bool UsernameFound = false;
int LoginVA(char Username[], char Password[])
{
    for (int i = 0; i < numberOfUsers; i++)
    {
        if (!strcmp(Username, Users[i].Username))
        {
            UsernameFound = true;
            if (!strcmp(Password, Users[i].Password))
            {
                return 1;
            }
        }
    }
    return 0;
}
bool LoginComplete;
void login()
{
    LoginComplete = false;
    char Username[250];
    char Password[250];
    int choice;

    printf("\n\t\t\t========== Login ==========\n");
    // clearInputBuffer(); // Clear input buffer
logingetusr:
    printf("\033[0;34m");
    printf("Enter your username: ");
    printf("\033[0m");
    fgets(Username, sizeof(Username), stdin);
    Username[strcspn(Username, "\n")] = '\0';
    if (Username[0] == '\n' || Username[0] == '\0')
    {
        printf("\033[0;31m");
        printf("All required fields Can't be left empty.\n");
        printf("\033[0m");
        goto logingetusr;
    }
PasswordEntry:
    getLoginPassword(Password);
    // Authenticate user

    if (LoginVA(Username, Password))
    {
        printf("\033[0;32m");
        printf("\nLogged in successfully!\n");
        printf("\033[0m");
        LoginComplete = true;
    }
    else if ((!LoginVA(Username, Password)) && UsernameFound)
    {
        printf("\033[0;31m");
        printf("\nInvalid password.\n");
        printf("\033[0m");
        goto PasswordEntry;
    }
    else
    {
        LoginComplete = false;
    }
    UsernameFound = false;
}
