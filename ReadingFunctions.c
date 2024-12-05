#include <stdio.h>
#include <stdbool.h>
//------------------- Definitions -------------------------
// Definitions are Global to be used by different functions

// Defining A struct for Users.
typedef struct
{
	char Username[250];
	char Name[250];
	char Password[250];
} User;
// Defining An array of structs for Users to put thier data.
User Users[10];
// Tracking The numbers of existing Users.
int numberOfUsers = 0;

// Defining A struct for Doctors.
typedef struct
{
	char Name[1000];
	char Speciality[1000];
	char Clinic_address[1000];
	double Visita;
} Doctor;
// Defining An array of structs for Doctors to put thier data.
Doctor Doctors[10];
// Tracking The numbers of existing Doctors.
int numberOfdoctors = 0;

//------------------- Functions Reference + Notes -------------------------

// This Function Reads UsersData. We will call it multiple times.
int ReadUsersData();
// This Function Reads DoctorsData. We will call it at the start of the program only.
int ReadDoctorsData();

void clearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

/*
Most of the error handling in these two functions
is Redundunt and only exists until we finish testing
As this only Checks for errors in formatting/existance of the file
which obviouslly won't happen as we're the ones who put the data
with this formatting.

User's will have a maximum for name,username,passwords
I've Set that Max to 250 for the mean time.

Both Functions Return -1 in Case of an error.

Read Users Data Function Returns the index of the next User

*/

//------------------- Functions -------------------------


int removeUsersdups()
{
	FILE *Output;
	FILE *Input;
	Output = fopen("temp.txt", "w");
	int Inline = 0, Outlines = 0;

		char tempUsername[250];
		char tempname[250];
		char temppass[250];
		Input = fopen("User_Data.txt", "r");
		if (Input == NULL)
		{
			return -1;
		}
		while (!feof(Input))
		{
			int read = 0;
			bool dublicated = false;
			User tempUsers[10];
			read = fscanf(Input,
						  "%250[^,],%250[^,],%250[^\n]%*c",
						  &tempUsername,
						  &tempname,
						  &temppass);

			if (read == 3)
			{
				for (int i = 0; i < Outlines; i++)
				{
					if (!strcmp(tempUsername,tempUsers[i].Username))
					{
						dublicated = true;
						break;
					}
				}
				if (dublicated == false)
				{
					strcpy(tempUsers[Outlines].Username, tempUsername);
					strcpy(tempUsers[Outlines].Name, tempname);
					strcpy(tempUsers[Outlines].Password, temppass);
					Outlines++;
					fprintf(Output, "%s,%s,%s", tempUsername, tempname, temppass);
					if(!feof(Input)){
						fprintf(Output,"\n");
					}
				}
			}
			if (read != 3 && !feof(Input))
			{
				continue;
			}
			if (ferror(Input))
			{
				return -1;
			}
		}
		fclose(Input);
		fclose(Output);
	}
	

	


int ReadUsersData()
{
	FILE *UsersData;
	removeUsersdups();
	remove("User_Data.txt");
	rename("temp.txt", "User_Data.txt");
	UsersData = fopen("User_Data.txt", "r");
	if (UsersData == NULL)
	{
		return -1;
	}
	while (!feof(UsersData))
	{
		int read = 0, i = 0; // redundant i
		read = fscanf(UsersData,
					  "%250[^,],%250[^,],%250[^\n]%*c",
					  &Users[numberOfUsers].Username,
					  &Users[numberOfUsers].Name,
					  &Users[numberOfUsers].Password);

		if (read == 3)
		{
			numberOfUsers++;
			continue;
		}
		if (read != 3 && !feof(UsersData))
		{
			return -1;
		}
		if (ferror(UsersData))
		{
			return -1;
		}
	}

	fclose(UsersData);
	return 0;
}

int ReadDoctorsData()
{

	FILE *DoctorsData;
	DoctorsData = fopen("Doctors_Data.txt", "r");
	if (DoctorsData == NULL)
	{
		return -1;
	}
	int read = 0;

	do
	{
		read = fscanf(DoctorsData,
					  "%250[^/]/%250[^/]/%250[^/]/%lf",
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
			return -1;
		}
		if (ferror(DoctorsData))
		{
			return -1;
		}

	} while (!feof(DoctorsData));

	fclose(DoctorsData);
}

