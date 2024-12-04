#include "SignUp.c"

int getLoginPassword(char *Pass, int usernumber)
{

    int i = 0;
    char password[250];
    char ch;
StartOfgetpass:
    // Show option to display password
    printf("\nDo you want to show your password? (Y for Yes, N for No): ");
    char showPassword;
    scanf("%c", &showPassword);
    clearInputBuffer(); // Clear input buffer

    if (tolower(showPassword) == 'y')
    {
        printf("Enter your password : ");
        fgets(password, 250, stdin);
        password[strlen(password) - 1] = '\0';
    }
    else if (tolower(showPassword) == 'n')
    {
        printf("Enter your password : ");
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
		printf("Wrong Choice. Try again.");
		goto StartOfgetpass;
	}
    strcpy(Pass, password);
}

//Previous Check for existance functions but merged as in login we are checking that this exact username exist and the password associated to it is correct
int LoginVA(char Username[],char Password[])
{
    for (int i = 0; i < numberOfUsers; i++)
    {
        if (!strcmp(Username, Users[i].Username))
        {
            if (!strcmp(Password, Users[i].Password))
                {
                    return 1;
                }
        }
    }
    return 0;
}

void login()
{
    char Username[250];
    char Password[250];
    int choice;

    printf("\n\t\t\t\t\t\t========== Login ==========\n");
    int authResult = 0;
    do
    {
        // clearInputBuffer(); // Clear input buffer

        printf("Enter your username: ");
        fgets(Username, sizeof(Username), stdin);
        Username[strcspn(Username, "\n")] = '\0';
        getLoginPassword(Password, numberOfUsers - 1);
        // Authenticate user

        if (LoginVA(Username,Password))
        {
            printf("\nLogged in successfully!\n");
        }
        else
        {
            printf("\nInvalid Username or password.\n");
        }
    } while (LoginVA(Username,Password)!= 1); // Loop until login is successful
}


