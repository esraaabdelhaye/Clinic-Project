#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Making struct "doctors" (This is just a sample to try my code)
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
            printf("THAT'S NOT VALID. TRY AGAIN.\n");
        }
        else valid = true;
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
            printf("THAT'S NOT VALID. TRY AGAIN.\n");
        }
        else valid = true;
    }
    return *n;
}

struct doctors {
	char Name[1000];
	char Speciality[1000];
	char Clinic_address[1000];
	double Visita;
};

void search_doctor(struct doctors doctors_arr[], int size) // function takes array of structs of "doctors" and its size
{
	// variable containing the search the user inputs
	char search[1000];
	int choice;
	start:
	printf(":=======================================================:\n");
	printf("[1] Search by Name\n");
	printf("[2] Search by Speciality\n");
	printf("[3] Search by Address\n");
	printf("[4] Search by Visita\n");
	printf("[5] Show all doctors\n");
	printf("[6] Logout\n");
	printf(":=======================================================:\n");
	get_integer("YOUR CHOICE : ", &choice);
	bool byname = false, byspeciality = false, byvisita = false, byaddress = false, byall = false, logout = false;
	double visita_from, visita_to;
	printf(":=======================================================:\n");
	getting_property:
	switch (choice)
	{
		case 1:
			byname = true;
			printf("NAME : ");
			break;
		case 2:
			printf("SPECIALITY : ");
			byspeciality = true;
			break;
		case 3:
			printf("ADDRESS : ");
			byaddress = true;
			break;
		case 4:
			get_double("VISITA RANGE - FROM : ", &visita_from);
			get_double("VISITA RANGE - TO : ", &visita_to);
			byvisita = true;
			break;
		case 5:
			byall = true;
			break;
		case 6:
			logout = true;
			printf("LOGGING OUT...\n");
			printf("SAD TO SEE YOU GO :*C\n");
			goto end;
			break;
		default:
			printf("!!! That's not a valid option !!!\n");
			printf("!!!        TRY AGAIN          !!!\n");
			goto start;
	}
	// Getting the user input
	if (!byall && !byvisita) fgets(search, 1000, stdin);
	// Changing the last character in the user input from '\n' to null-terminator
	if (search[strlen(search)-1] == '\n') search[strlen(search)-1] = '\0';
	// The actual search procedures
	int found_count = 0;
	for (int i = 0; i < size; i++)
	{
		// initializing boolean value variable "found" to false which represents that target was found
		bool found = false;
		char *property = NULL;
		if (byname) property = strdup(doctors_arr[i].Name);
		else if (byspeciality) property = strdup(doctors_arr[i].Speciality);
		else if (byaddress) property = strdup(doctors_arr[i].Clinic_address);
		// Comparing with the lowercase status to see if the user input search is contained in any property
		property = strstr(strlwr(property), strlwr(search));
		if (property != NULL) found = true;
		else if (byvisita && doctors_arr[i].Visita >= visita_from && doctors_arr[i].Visita <= visita_to) found = true;
		else if (byall) found = true;
		if (found)
		{
			// Showing the results that were found
			found_count ++;
			printf("-----------------------------\n");
			printf("name: %s\n", doctors_arr[i].Name);
			printf("speciality: %s\n", doctors_arr[i].Speciality);
			printf("clinic address: %s\n", doctors_arr[i].Clinic_address);
			printf("visita: %.2lf\n", doctors_arr[i].Visita);
		}
	}
	if (found_count == 0)
	{
		printf("!!!! There were no results found !!!!\n!!!!          TRY AGAIN          !!!!\n");
		goto getting_property;
	}
	end:
	{
		printf("");
	}
}

int main()
{
	// This is just a sample to show how it works
	struct doctors d1 = {"Abdelrahman Nabil", "Neurology", "10 Al Zarkashi, Al Azaritah WA Ash Shatebi, Bab Sharqi, Alexandria Governorate 5424011", 120.53};
	struct doctors d2 = {"Abdelrahman Fathy", "Cardiology", "Green Valley Medical Center, 245 Elm Street, Springfield, IL 62704, United States", 356.72};
	struct doctors d3 = {"Mostafa Fathy", "Dermatology", "Sunrise btngana Clinic, 78 Orchard Road, Singapore 238896", 842.15};
	struct doctors d4 = {"Yousef Waleed", "Pediatrics", "Healthy Life Veterinary Clinic, 120-8 Hwarang-ro, Gyeongju-si, Gyeongsangbuk-do, South Korea", 423.89};
	struct doctors d5 = {"Jana Rashed", "Neurology", "St. Thomas Clinic, 14 Abbey Road, London NW8 9AY, United Kingdom", 978.34};
	struct doctors d6 = {"Israa Abdelhayee", "Obstetrics and Gynecology", "Clínica Médica Los Ángeles, Av. Reforma 125, Ciudad de México, CDMX 06600, Mexico", 217.56};
	struct doctors d7 = {"Youmna F.Ali", "Psychiatry", "Serenity Psychiatry Center, 412 Maplewood Avenue, Suite 7B, Brighton, MA 02135, United States", 200.00};
	struct doctors doctors_arr[10];
	doctors_arr[0] = d1;
	doctors_arr[1] = d2;
	doctors_arr[2] = d3;
	doctors_arr[3] = d4;
	doctors_arr[4] = d5;
	doctors_arr[5] = d6;
	doctors_arr[6] = d7;
	search_doctor(doctors_arr, 7);
}