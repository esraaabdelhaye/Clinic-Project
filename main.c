#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Making struct "doctors" (This is just a sample to try my code)
struct doctors {
	char name[1000];
	char speciality[1000];
	char clinic_address[1000];
	double visita;
};

void search_doctor(struct doctors doctors_arr[], int size) // function takes array of structs of "doctors" and its size
{
	// variable containing the search the user inputs
	char search[1000];
	start:
	printf(":=======================================================:\n");
	printf("[1] Search by Name\n");
	printf("[2] Search by Speciality\n");
	printf("[3] Search by Address\n");
	printf("[4] Search by Visita\n");
	printf("[5] Show all doctors\n");
	printf("[6] Logout\n");
	printf(":=======================================================:\n");
	printf("YOUR CHOICE : ");
	int choice;
	bool byname = false, byspeciality = false, byvisita = false, byaddress = false, byall = false, logout = false;
	scanf("%d%*c", &choice);
	double visita_from, visita_to;
	printf(":=======================================================:\n");
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
			printf("VISITA RANGE - FROM : ");
			scanf("%lf%*c", &visita_from);
			printf("VISITA RANGE - TO : ");
			scanf("%lf%*c", &visita_to);
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
		if (byname) property = strdup(doctors_arr[i].name);
		else if (byspeciality) property = strdup(doctors_arr[i].speciality);
		else if (byaddress) property = strdup(doctors_arr[i].clinic_address);
		// Comparing with the lowercase status to see if the user input search is contained in any property
		property = strstr(strlwr(property), strlwr(search));
		if (property != NULL) found = true;
		else if (byvisita && doctors_arr[i].visita >= visita_from && doctors_arr[i].visita <= visita_to) found = true;
		else if (byall) found = true;
		if (found)
		{
			// Showing the results that were found
			found_count ++;
			printf("-----------------------------\n");
			printf("name: %s\n", doctors_arr[i].name);
			printf("speciality: %s\n", doctors_arr[i].speciality);
			printf("clinic address: %s\n", doctors_arr[i].clinic_address);
			printf("visita: %.2lf\n", doctors_arr[i].visita);
		}
	}
	if (found_count == 0)
	{
		printf("!!!! There were no results found !!!!\n!!!!          TRY AGAIN          !!!!\n");
		goto start;
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