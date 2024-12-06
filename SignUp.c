#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "ReadingFunctions.c"

int UsernameCheckForExistance(char Searching[])
{
	for (int i = 0; i < numberOfUsers; i++)
	{
		if (!strcmp(Searching, Users[i].Username))
		{
			return 1;
		}
	}
	return 0;
}
int PasswordCheckForExistance(char Searching[])
{
	for (int i = 0; i < numberOfUsers; i++)
	{
		if (!strcmp(Searching, Users[i].Password))
		{
			return 1;
		}
	}
	return 0;
}
// This Password Check isn't really required Here,but would be useful in login

// Function to get password and show option during signup
// This Function was originally made by Jana but useful here That's why I'n using it ,as This file would be imported into Login anyways
// However I made some slight changes that would make the function more user friendly -I guess- and fixed some problems in the logic itself

/*
The Changes I made to this function :
-----------------------------
1.I changed The Parameters of the function to (Pointer to an array that would store the password,the current user index in the array)
2.I made the user choose wether to show password or not before actually typing the password
3.Obviouslly as we're getting the password with two different ways ,It was essential that the check of validation be after the if-else condition
of the two ways.
4.all this time the password retrived is stored into a temporary password "string" until it's validated
Then it gets stored in the array That's pointer was passed to the function.

*/
int getPassword(char *Pass)
{
	int i;
	char password[250];
	char ch;
	int hasNumeric; // Flag to track if password contains at least one numeric value
	int hasSymbol;	// Flag to track if password contains at least one symbol
	int hasUpper;
	int haslwr;
StartOfgetpass:
	for (int i = 0; strlen(password); i++) password[i] = '\0';

	i = 0;
	hasNumeric = 0;
	hasSymbol = 0;
	hasUpper = 0;
	haslwr = 0;
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
		printf("Enter your password (at least one symbol, one numeric value ,one uppercase and one lowercase required): ");
		printf("\033[0m");
		fgets(password, 250, stdin);
		password[strlen(password) - 1] = '\0';
	}
	else if (tolower(showPassword) == 'n')
	{
		printf("\033[0;34m");
		printf("Enter your password (at least one symbol, one numeric value ,one uppercase and one lowercase required): ");
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
		printf("Wrong Choice. Try again.\n");
		printf("\033[0m");
		goto StartOfgetpass;
	}
	for (int i = 0; i < strlen(password); i++)
	{
		if (ispunct(password[i]))
		{
			hasSymbol = 1;
		}
		if (isdigit(password[i]))
		{
			hasNumeric = 1;
		}
		if (isupper(password[i]))
		{
			hasUpper = 1;
		}
		if (islower(password[i]))
		{
			haslwr = 1;
		}
	}
	// Validate password complexity

	if (!(hasNumeric && hasSymbol && haslwr && hasUpper))
	{
		printf("\033[0;31m");
		printf("\nPassword must contain at least one symbol , one numeric value, one uppercase and one lowercase. Please try again.\n");
		printf("\033[0m");
		goto StartOfgetpass;
	}
	else if (strlen(password) < 8)
	{
		printf("\033[0;31m");
		printf("\nPassword must Should Have at least 8 characters. Please try again.\n");
		printf("\033[0m");
		goto StartOfgetpass;
	}

	else
	{
		strcpy(Pass, password);
	}
}

int Signup()
{
	// can't add another patient
	if (numberOfUsers >= 10)
	{
		printf("\033[0;31m");
		printf("\nSorry, We don't accept more patients");
		printf("\033[0m");
		return 0;
	}

	int UsernameDuplicated = 0;
	// Flags to Track Whether Verification Was Complete or not

	char PatientfullName[250];
	char PatientUsername[250];
	char PatientPassword[250];
getusr:
	printf("Enter Your Username: ");
	fgets(PatientUsername, 250, stdin);
	PatientUsername[strlen(PatientUsername) - 1] = '\0';
	for (int i = 0; i < strlen(PatientUsername); i++)
	{
		if (PatientUsername[i] == ' ' || PatientUsername[i] == '.' || PatientUsername[i] == '!' || PatientUsername[i] == '?' || PatientUsername[i] == ',' || PatientUsername[i] == '$' || PatientUsername[i] == '/')
		{
			printf("\033[0;31m");
			printf("Username Can't Contain spaces or (./,/;/!/? or /).\n");
			printf("\033[0m");
			goto getusr;
		}
	}

	UsernameDuplicated = UsernameCheckForExistance(PatientUsername); // zero here means it's verified

	if (UsernameDuplicated)
	{
		printf("\033[0;31m");
		printf("This Username is already Used.\n");
		printf("\033[0m");
		goto getusr;
	}
	if (PatientUsername[0] == '\n' || PatientUsername[0] == '\0')
	{
		printf("\033[0;31m");
		printf("All required fields Can't be left empty.\n");
		printf("\033[0m");
		goto getusr;
	}
	if (strlen(PatientUsername) < 4 || strlen(PatientUsername) > 20)
	{
		printf("\033[0;31m");
		printf("Username Should Be between 4 and 20 characters.\n");
		printf("\033[0m");
		goto getusr;
	}
	if (PatientUsername[0] == ' ')
	{
		printf("\033[0;31m");
		printf("Username Can't start with spaces.\n");
		printf("\033[0m");
		goto getusr;
	}
getname:
	printf("\033[0;34m");
	printf("Enter Your Full Name: ");
	printf("\033[0m");
	fgets(PatientfullName, 250, stdin);
	PatientfullName[strlen(PatientfullName) - 1] = '\0';
	for (int i = 0; i < strlen(PatientfullName); i++)
	{
		if (!(isalpha(PatientfullName[i]) || PatientfullName[i] == ' '))
		{
			printf("\033[0;31m");
			printf("Names Can't Contain Special Characters nor Numbers.\n");
			printf("\033[0m");
			goto getname;
		}
	}
	if (PatientfullName[0] == ' ')
	{
		printf("\033[0;31m");
		printf("Name Can't start with spaces.\n");
		printf("\033[0m");
		goto getname;
	}
	if (PatientfullName[0] == '\0' || PatientfullName[0] == '\n')
	{
		printf("\033[0;31m");
		printf("All required fields Can't be left empty.\n");
		printf("\033[0m");
		goto getname;
	}
getpassw:
	getPassword(PatientPassword);

	for (int i = 0; i < strlen(PatientPassword); i++)
	{
		if (PatientPassword[i] == ' ' || PatientPassword[i] == '.' || PatientPassword[i] == '!' || PatientPassword[i] == '?' || PatientPassword[i] == ',' || PatientPassword[i] == '$' || PatientPassword[i] == '/')
		{
			printf("\033[0;31m");
			printf("\nPassword Can't Contain spaces or (./,/;/!/? or /).\n");
			printf("\033[0m");
			goto getpassw;
		}
	}

	strcpy(Users[numberOfUsers].Username, PatientUsername);
	strcpy(Users[numberOfUsers].Name, PatientfullName);
	strcpy(Users[numberOfUsers].Password, PatientPassword);
	FILE *PatientsFile = fopen("User_Data.txt", "a");
	fprintf(PatientsFile, "%s,%s,%s", Users[numberOfUsers].Username, Users[numberOfUsers].Name, Users[numberOfUsers].Password);
	if (numberOfUsers + 1 != 10)
	{
		fprintf(PatientsFile, "\n");
	}
	fclose(PatientsFile);
	printf("\033[0;32m");
	printf("\nSuccessfully Signed Up! Now Login to Use the app\n");
	printf("\033[0m");
	numberOfUsers++;
}
