#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "ReadingFunctions.c"

void clearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// this function Should only run when validations are complete and we want to write User's Data from the array
//  Returns -1 in case of an error

int UsernameCheckForExistance(char Searching[])
{
	for (int i = 0; i < numberOfUsers; i++)
	{
		if (!strcmp(Searching, Users[i].Username))
		{
			return 0; // found
		}
	}
	return 1; // not found
}
int PasswordCheckForExistance(char Searching[])
{
	for (int i = 0; i < numberOfUsers; i++)
	{
		if (!strcmp(Searching, Users[i].Password))
		{
			return 0; // found
		}
	}
	return 1; // not found
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
int getPassword(char *Pass, int usernumber)
{

	int i = 0;
	char password[250];
	char ch;
	int hasNumeric; // Flag to track if password contains at least one numeric value
	int hasSymbol;	// Flag to track if password contains at least one symbol
StartOfgetpass:

	hasNumeric = 0;
	hasSymbol = 0;
	// Show option to display password
	printf("\nDo you want to show your password? (Y for Yes, N for No): ");
	char showPassword;
	scanf("%c", &showPassword);
	clearInputBuffer(); // Clear input buffer

	printf("Enter your password (at least one symbol and one numeric value required): ");
	if (showPassword == 'Y' || showPassword == 'y')
	{
		fgets(password, 250, stdin);
		password[strlen(password) - 1] = '\0';
	}
	else if (showPassword == 'N' || showPassword == 'n')
	{

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
	}
	// Validate password complexity
	if (!(hasNumeric && hasSymbol))
	{
		printf("Password must contain at least one symbol and one numeric value. Please try again.\n");
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
		printf("Sorry, We don't accept more patients");
		return 0;
	}

	int CurrentUser; // Tracking The index of the current User

	int UsernameVerified = 0;
	// Flags to Track Whether Verification Was Complete or not

	int Status = ReadUsersData();
	if (Status != -1)
	{
		CurrentUser = numberOfUsers - 1;
	}
	char PatientfullName[250];
	char PatientUsername[250];
	char PatientPassword[250];
get_input:
	printf("Enter Your Username: ");
	fgets(PatientUsername, 250, stdin);
	PatientUsername[strlen(PatientUsername) - 1] = '\0';

	printf("Enter Your Full Name: ");
	fgets(PatientfullName, 250, stdin);
	PatientfullName[strlen(PatientfullName) - 1] = '\0';

	getPassword(PatientPassword, CurrentUser);

	UsernameVerified = UsernameCheckForExistance(PatientUsername);

	if (UsernameVerified)
	{
		strcpy(Users[CurrentUser].Username, PatientUsername);
		strcpy(Users[CurrentUser].Name, PatientfullName);
		strcpy(Users[CurrentUser].Password, PatientPassword);
		FILE *PatientsFile = fopen("User_Data.txt", "a");
		fprintf(PatientsFile, "\n%s,%s,%s", Users[CurrentUser].Username, Users[CurrentUser].Name, Users[CurrentUser].Password);
		fclose(PatientsFile);
		printf("\nSuccessfully Signed Up! Now Login to Use the app\n");
		CurrentUser++;
	}
	else
	{
		printf("This Username is already Used.\n");
		goto get_input;
	}
}
