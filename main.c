#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Patient{
	char fullName[50];
	char email[50];
	char password[50];
	char phone[15];
	char username[50];
};

int getNumOfPatients(){
	int linesCount = 0;
	char letter;
	FILE *patientsFile = fopen("Patients.txt", "r");

	if(patientsFile == NULL){
		printf("Error: Couldn't open file :(\n)");
		return -1;
	}

	do{
		letter = fgetc(patientsFile);    // fscanf      fgets
		if(letter == '\n') linesCount++;
	}while(letter != EOF);
	fclose(patientsFile);
	return linesCount;
}

bool storePatientInFile(struct Patient P){
	FILE *PatientsFile = fopen("Patients.txt", "a");
	fprintf(PatientsFile,"%s#//#%s#//#%s#//#%s#//#%s#//#%s\n", P.fullName, P.email, P.password, P.phone, P.username);
	
	fclose(PatientsFile);
}

bool addPatient(struct Patient newPatient){
	
	char fullName[50];
	printf("Enter full name: ");
	fgets(fullName,50,stdin);
	fullName[strlen(fullName)-1] = '\0';
	strcpy(newPatient.fullName,fullName);

	printf("Enter email: ");      // validation on email
	scanf("%s", newPatient.email);

	printf("Enter password: ");
	scanf("%s", newPatient.password);

	printf("Enter phone: ");      // validation on phone
	scanf("%s", newPatient.phone);
	
	if(storePatientInFile(newPatient)) return true;
	return false;

}

void signup(){
	// can't add another patient
	if(getNumOfPatients() == 10){
		printf("Sorry, We don't accept more patients");
		return;
	}
	// we couldn't access the patients file
	if(getNumOfPatients() == -1) return;
	printf("%d\n", getNumOfPatients() );
	struct Patient newPatient;
	printf("Username: ");
	fgets(newPatient.username,50,stdin);

	// validation (whether or not this username is used before)
	// if username wasn't found do the following
	addPatient(newPatient);
}

int main()
{
	signup();
	return 0;
}