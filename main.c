#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Making struct "doctors" (This is just a sample to try my code)
struct doctors {
	char name[1000];
	char speciality[1000];
	char clinic_address[1000];
	char visita[100];
};

void search_doctor(struct doctors arr[], int size) // function takes array of structs of "doctors" and its size
{
	// variable containing the search the user inputs
	char search[100];
	printf("Enter your search: ");
	// Getting the user input
	fgets(search, 100, stdin);
	// Changing the last character in the user input from '\n' to null-terminator
	if (search[strlen(search)-1] == '\n') search[strlen(search)-1] = '\0';
	// The actual search procedures
	int found_count = 0;
	for (int i = 0; i < size; i++)
	{
		// Getting every doctor's properties (name, speciality, etc) and putting them in an array of size 4
		char **doctor = (char **)calloc(4*1000, sizeof(char *));
		doctor[0] = arr[i].name;
		doctor[1] = arr[i].speciality;
		doctor[2] = arr[i].clinic_address;
		doctor[3] = arr[i].visita;
		// initializing boolean value variable "found" to false which represents that target was found
		bool found = false;
		// looping through the properties of every doctor (name, speciality, etc)
		for (int j = 0; j < 4; j++)
		{
			// Comparing with the lowercase status to see if the user input search is contained in any property
			char *ptr = strdup(doctor[j]);
			ptr = strstr(strlwr(ptr), strlwr(search));
			if (ptr != NULL)
			{
				found = true;
				found_count ++;
				break;
			}
		}
		if (found)
		{
			// Showing the results that were found
			printf("-----------------------------\n");
			printf("name: %s\n", doctor[0]);
			printf("speciality: %s\n", doctor[1]);
			printf("clinic address: %s\n", doctor[2]);
			printf("visita: %s\n", doctor[3]);
		}
	}
	if (found_count == 0) printf("!!!! There were no results found !!!!\nTRY AGAIN.\n");

	
}

int main()
{
	// This is just a sample to show how it works
	struct doctors d1 = {"Abdelrahman Nabil", "Neurology", "10 Al Zarkashi, Al Azaritah WA Ash Shatebi, Bab Sharqi, Alexandria Governorate 5424011", "120.53"};
	struct doctors d2 = {"Abdelrahman Fathy", "Cardiology", "Green Valley Medical Center, 245 Elm Street, Springfield, IL 62704, United States", "356.72"};
	struct doctors d3 = {"Mostafa Fathy", "Dermatology", "Sunrise btngana Clinic, 78 Orchard Road, Singapore 238896", "842.15"};
	struct doctors d4 = {"Yousef Waleed", "Pediatrics", "Healthy Life Veterinary Clinic, 120-8 Hwarang-ro, Gyeongju-si, Gyeongsangbuk-do, South Korea", "423.89"};
	struct doctors d5 = {"Jana Rashed", "Neurology", "St. Thomas Clinic, 14 Abbey Road, London NW8 9AY, United Kingdom", "978.34"};
	struct doctors d6 = {"Israa Abdelhayee", "Obstetrics and Gynecology", "Clínica Médica Los Ángeles, Av. Reforma 125, Ciudad de México, CDMX 06600, Mexico", "217.56"};
	struct doctors d7 = {"Youmna F.Ali", "Psychiatry", "Serenity Psychiatry Center, 412 Maplewood Avenue, Suite 7B, Brighton, MA 02135, United States", "200.00"};
	struct doctors arr[10];
	arr[0] = d1;
	arr[1] = d2;
	arr[2] = d3;
	arr[3] = d4;
	arr[4] = d5;
	arr[5] = d6;
	arr[6] = d7;
	printf("%d\n", *(&arr + 1) - arr);
	while (1) search_doctor(arr, 7);
}