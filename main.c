#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

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
		printf("%s", str);
		char newline_check;
		int checker = scanf("%d%c", n, &newline_check);
		if (checker != 2 || newline_check != '\n')
		{
			delete_buffer();
			printf("Invalid Input. Try again\n");
		}
		else
			valid = true;
	}
	return *n;
}

double get_double(char *str, double *n)
{
	bool valid = false;
	while (!valid)
	{
		printf("%s", str);
		char newline_check;
		int checker = scanf("%lf%c", n, &newline_check);
		if (checker != 2 || newline_check != '\n')
		{
			delete_buffer();
			printf("Invalid Input. Try Again.\n");
		}
		else
			valid = true;
	}
	return *n;
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
	get_integer("Your Choice : ", &choice);
	bool byname = false, byspeciality = false, byvisita = false, byaddress = false, byall = false, logout = false;
	double visita_from, visita_to;
getting_property:
	switch (choice)
	{
	case 1:
		printf("Name : ");
		byname = true;
		break;
	case 2:
		printf("Speciality : ");
		byspeciality = true;
		break;
	case 3:
		printf("Address : ");
		byaddress = true;
		break;
	case 4:
		get_double("Visita (PriceRange) - From : ", &visita_from);
		get_double("Visita (PriceRange) - To : ", &visita_to);
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
		printf("Invalid Option. Try Again\n");
		goto start;
	}
	// Getting the user input
	if (!byall && !byvisita) fgets(search, 1000, stdin);
		// Changing the last character in the user input from '\n' to null-terminator
	if (search[strlen(search)-1] == '\n') search[strlen(search)-1] = '\0';
	// The actual search procedures
	int found_count = 0;
	int ContinueChoice;
	for (int i = 0; i < numberOfdoctors; i++)
	{
		// initializing boolean value variable "found" to false which represents that target was found
		bool found = false;
		char *property = NULL;
		if (byname) property = strdup(Doctors[i].Name);
		else if (byspeciality) property = strdup(Doctors[i].Speciality);
		else if (byaddress) property = strdup(Doctors[i].Clinic_address);
		// Comparing with the lowercase status to see if the user input search is contained in any property
		if (!byall && !byvisita) property = strstr(strlwr(property), strlwr(search));
		if (property != NULL) found = true;
		else if (byvisita && Doctors[i].Visita >= visita_from && Doctors[i].Visita <= visita_to) found = true;
		else if (byall) found = true;
		if (found)
		{
			// Showing the results that were found
			found_count++;
			printf("\n\t\t\t\t========== Result ==========\n");
			printf("Name: %s\n", Doctors[i].Name);
			printf("Speciality: %s\n", Doctors[i].Speciality);
			printf("Clinic Address: %s\n", Doctors[i].Clinic_address);
			printf("Visita: %.2lf\n\n", Doctors[i].Visita);
		}
	}
	if (found_count == 0)
	{
		printf("No Matching Results. Try Again.\n");
		goto getting_property;
	}
	else
	{
	ContinueChoice:
		printf("Do You Want to Search Again? (Y for Yes, L for Logout): ");
		char search_again;
		scanf("%c%*c", &search_again);
		if (tolower(search_again) == 'l') goto end;
		else if (tolower(search_again) == 'y')
		{
			printf("\n\t\t\t\t========== Search ==========\n");
			printf("1. Search With Same Criteria.\n");
			printf("2. Search With Different Criteria.\n");
			printf("3. Logout\n\n");
			printf("\t\t\t\t============================\n");
			get_integer("Your Choice : ", &choice);
		}
		else
		{
			printf("Invalid Option\n");
			goto ContinueChoice;
		}
		switch (choice)
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
			printf("Invalid Option\n");
			goto ContinueChoice;
		}
	}
end:
{
	printf("\nLogging Out...\n");
}
}
