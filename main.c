#include <stdio.h>
#include <regex.h>

static const specialities[100][10000] = {
	{"Allergy and Immunology"}, {"Neurology"}, {"Cardiology"}, {"Otolaryngology"},
{"Dermatology"}, {"Family Medicine"}, {"Forensic Pathology"}, {"Obstetrics and Gynecology"},
{"Genetics and Genomics"}, {"Pathology"}, {"Pediatrics"}, {"Preventive Medicine"}, {"Psychiatry"}, {"Radiology"}
};

struct doctors {
	char name[1000];
	char speciality[1000];
	char clinic_address[1000];
	float visita;
};

void search_doctor(char *query, struct doctors doc)
{
	char search[100];
	printf("Enter your search: ");
	fgets(search, 100, stdin);
	if (search[strlen(search)-1] == '\n') search[strlen(search)-1] = '\0';
	
}

int main()
{
	struct doctors d1 = {"Abdelrahman Nabil", "Neurology", "10 Al Zarkashi, Al Azaritah WA Ash Shatebi, Bab Sharqi, Alexandria Governorate 5424011", 120.53};
	struct doctors d2 = {"Abdelrahman Fathy", "Cardiology", "Green Valley Medical Center, 245 Elm Street, Springfield, IL 62704, United States", 356.72};
	struct doctors d3 = {"Mostafa Fathy", "Genetics and Genomics", "Sunrise Dental Clinic, 78 Orchard Road, Singapore 238896", 842.15};
	struct doctors d4 = {"Yousef Waleed", "Pediatrics", "Healthy Life Veterinary Clinic, 120-8 Hwarang-ro, Gyeongju-si, Gyeongsangbuk-do, South Korea", 423.89};
	struct doctors d5 = {"Jana Rashed", "Psychiatry", "St. Thomas Family Clinic, 14 Abbey Road, London NW8 9AY, United Kingdom", 978.34};
	struct doctors d6 = {"Israa Abdelhayee", "Forensic Patholog", "Clínica Médica Los Ángeles, Av. Reforma 125, Ciudad de México, CDMX 06600, Mexico", 217.56};
}