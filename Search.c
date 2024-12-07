#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Login.c"

void delete_buffer()
{
	char garbage[1000];
	scanf("%[^\n]%*c", garbage);
}
int get_integer(char *str, int *n)
{
	bool valid = false;
	while (!valid)
	{
		bool not_isdigit = false;
		printf("\033[0;34m");
		printf("%s", str);
		printf("\033[0m");
		char input[1000];
		fgets(input, 1000, stdin);
		input[strlen(input) - 1] = '\0';
		if (strlen(input) > 0)
		{
			for (int i = 0; i < strlen(input); i++)
			{
				if (!isdigit(input[i]))
				{
					not_isdigit = true;
					break;
				}
			}
		}
		else
		{
			printf("\033[0;31m");
			printf("Invalid Input. Try again\n");
			printf("\033[0m");
			valid = false;
			continue;
		}
		if (not_isdigit)
		{
			printf("\033[0;31m");
			printf("Invalid Input. Try again\n");
			printf("\033[0m");
			valid = false;
		}
		else
		{
			*n = atoi(input);
			valid = true;
		}
	}
}

double get_double(char *str, double *n)
{
	bool valid = false;
	while (!valid)
	{
		printf("\033[0;34m");
		printf("%s", str);
		printf("\033[0m");
		char newline_check;
		int checker = scanf("%lf%c", n, &newline_check);
		if (checker != 2 || newline_check != '\n')
		{
			delete_buffer();
			printf("\033[0;31m");
			printf("Invalid Input. Try Again.\n");
			printf("\033[0m");
		}
		else
			valid = true;
	}
}

void search_doctor(int numberOfdoctors) // function takes array of structs of "Doctors" and its size
{
	// variable containing the search the user inputs
	char search[1000];
	int choice;
start:
	printf("\n\t\t\t\t========== Search ==========\n");
	printf("1. Search by Name\n");
	printf("2. Search by Speciality\n");
	printf("3. Search by Address\n");
	printf("4. Search by Visita\n");
	printf("5. Show All Doctors\n");
	printf("6. Logout\n\n");
	printf("\t\t\t\t============================\n");
	printf("\033[0;34m");
	get_integer("Your Choice : ", &choice);
	printf("\033[0m");
	bool byname = false, byspeciality = false, byvisita = false, byaddress = false, byall = false, logout = false;
	double visita_from, visita_to;
getting_property:
	switch (choice)
	{
	case 1:
		printf("\033[0;34m");
		printf("Name : ");
		printf("\033[0m");
		byname = true;
		break;
	case 2:
		printf("\033[0;34m");
		printf("Speciality : ");
		printf("\033[0m");
		byspeciality = true;
		break;
	case 3:
		printf("\033[0;34m");
		printf("Address : ");
		printf("\033[0m");
		byaddress = true;
		break;
	case 4:
		printf("\033[0;34m");
		get_double("Visita (PriceRange) - From : ", &visita_from);
		get_double("Visita (PriceRange) - To : ", &visita_to);
		printf("\033[0m");
		byvisita = true;
		break;
	case 5:
		byall = true;
		break;
	case 6:
		logout = true;
		goto end;
		break;
	default:
		printf("\033[0;31m");
		printf("Invalid Option. Try Again\n");
		printf("\033[0m");
		goto start;
	}
	// Getting the user input
	if (!byall && !byvisita)
		fgets(search, 1000, stdin);
	// Changing the last character in the user input from '\n' to null-terminator
	if (search[strlen(search) - 1] == '\n')
		search[strlen(search) - 1] = '\0';
	if (strlen(search) == 0 && !byall && !byvisita)
	{
		printf("\033[0;31m");
		printf("Invalid Input. Try Again\n");
		printf("\033[0m");
		goto start;
	}
	if (ispunct(search[0]) || search[0] == ' ')
	{
		printf("\033[0;31m");
		printf("Invalid Input. Try Again\n");
		printf("\033[0m");
		goto getting_property;
	}
	// The actual search procedures
	int found_count = 0;
	int ContinueChoice;
	for (int i = 0; i < numberOfdoctors; i++)
	{
		// initializing boolean value variable "found" to false which represents that target was found
		bool found = false;
		char *property = NULL;
		if (byname)
			property = strdup(Doctors[i].Name);
		else if (byspeciality)
			property = strdup(Doctors[i].Speciality);
		else if (byaddress)
			property = strdup(Doctors[i].Clinic_address);
		// Comparing with the lowercase status to see if the user input search is contained in any property
		if (!byall && !byvisita)
			property = strstr(strlwr(property), strlwr(search));
		if (property != NULL)
			found = true;
		else if (byvisita && Doctors[i].Visita >= visita_from && Doctors[i].Visita <= visita_to)
			found = true;
		else if (byall)
			found = true;
		if (found)
		{
			// Showing the results that were found
			found_count++;
			printf("\033[0;32m");
			printf("\n\t\t\t\t========== Result ==========\n");
			printf("\033[0m");
			printf("Name: %s\n", Doctors[i].Name);
			printf("Speciality: %s\n", Doctors[i].Speciality);
			printf("Clinic Address: %s\n", Doctors[i].Clinic_address);
			printf("Visita: %.2lf\n\n", Doctors[i].Visita);
		}
	}
	if (found_count == 0)
	{
		printf("\033[0;31m");
		printf("No Matching Results. Try Again.\n");
		printf("\033[0m");
		goto getting_property;
	}
	else
	{
	ContinueChoice:
		printf("\033[0;35m");
		printf("Do You Want to Search Again? (Y for Yes, L for Logout): ");
		printf("\033[0m");
		char search_again;
		char search_again_input[1000];
		fgets(search_again_input, 1000, stdin);
		search_again_input[strlen(search_again_input) - 1] = '\0';
		if (strlen(search_again_input) != 1)
		{
			printf("\033[0;31m");
			printf("Invalid Option\n");
			printf("\033[0m");
			goto ContinueChoice;
		}
		search_again = search_again_input[0];

		int second_choice;
		if (tolower(search_again) == 'l')
			goto end;
		else if (tolower(search_again) == 'y')
		{
			printf("\n\t\t\t\t========== Search ==========\n");
			printf("1. Search With Same Criteria.\n");
			printf("2. Search With Different Criteria.\n");
			printf("3. Logout\n\n");
			printf("\t\t\t\t============================\n");
			printf("\033[0;34m");
			get_integer("Your Choice : ", &second_choice);
			printf("\033[0m");
		}
		else
		{
			printf("\033[0;31m");
			printf("Invalid Option\n");
			printf("\033[0m");
			goto ContinueChoice;
		}
		switch (second_choice)
		{
		case 1:
			goto getting_property;
			break;
		case 2:
			goto start;
			break;
		case 3:
			logout = true;
			goto end;
			break;
		default:
			printf("\033[0;31m");
			printf("Invalid Option\n");
			printf("\033[0m");
			goto ContinueChoice;
		}
	}
end:
{
	printf("\033[0;31m");
	printf("\nLogging Out...\n");
	printf("\033[0m");
}
}
