#include <stdio.h>

//------------------- Definitions -------------------------
//Definitions are Global to be used by different functions

//Defining A struct for Users.
typedef struct
{
	char Name[250];
	char Username[250];
	char Password[250];
} User;
//Defining An array of structs for Users to put thier data.
User Users[10];
//Tracking The numbers of existing Users.
int numberOfUsers = 0;

//Defining A struct for Doctors.
typedef struct {
	char Name[1000];
	char Speciality[1000];
	char Clinic_address[1000];
	char Visita[100];
}Doctor;
//Defining An array of structs for Doctors to put thier data.
Doctor Doctors [10];
//Tracking The numbers of existing Doctors.
int numberOfdoctors=0;

//------------------- Functions Reference + Notes -------------------------

//This Function Reads UsersData. We will call it multiple times. 
int ReadUsersData();
//This Function Reads DoctorsData. We will call it at the start of the program only. 
int ReadDoctorsData();

/*
Note That most of the error handling in these two functions
is Redundunt and only exists until we finish testing 
As this only Checks for errors in formatting/existance of the file
which obviouslly won't happen as we're the ones who put the data
with this formatting.

Also Note That User's will have a maximum for name,username,passwords
I've Set that Max to 250 for the mean time.
*/


int main()
{

}


//------------------- Functions -------------------------
int ReadUsersData()
{
	FILE *UsersData;
	UsersData = fopen("User_Data.txt", "r");
	if (UsersData == NULL)
	{
		printf("Error Reading Users File !");
		return 1;
	}
	int read = 0;
	do
	{
		read = fscanf(UsersData,
			        	"%250[^,],%250[^,],%250[^\n]",
						&Users[numberOfUsers].Name,
					 	&Users[numberOfUsers].Username,
					 	&Users[numberOfUsers].Password);

		if (read == 3)
		{
			numberOfUsers++;
		}
		if (read != 3 && !feof(UsersData))
		{
			printf("Incorrect File Format !\n");
			return 1;
		}
		if(ferror(UsersData)){
			printf("Error Reading File !\n");
			return 1;
		}

	} while (!feof(UsersData));

	fclose(UsersData);
}

int ReadDoctorsData(){
	FILE *DoctorsData;
	DoctorsData = fopen("Doctors_Data.txt", "r");
	if (DoctorsData == NULL)
	{
		printf("Error Reading Users File !");
		return 1;
	}
	int read = 0;

	do
	{
		read = fscanf(DoctorsData,
			        	"%250[^,],%250[^,],%250[^,],%250[^\n]",
						&Doctors[numberOfdoctors].Name,
					 	&Doctors[numberOfdoctors].Speciality,
					 	&Doctors[numberOfdoctors].Clinic_address,
					 	&Doctors[numberOfdoctors].Visita);

		if (read == 4)
		{
			numberOfdoctors++;
		}
		if (read != 4 && !feof(DoctorsData))
		{
			printf("Incorrect File Format !\n");
			return 1;
		}
		if(ferror(DoctorsData)){
			printf("Error Reading File !\n");
			return 1;
		}

	} while (!feof(DoctorsData));

	fclose(DoctorsData);
}