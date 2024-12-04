#include <stdio.h>
#include "Search.c" 
//Baiscally Search includes login, login includes signup, signup includes readfunctions
//which makes including search only in main valid!

int main()
{
    ReadDoctorsData();
    if (ReadUsersData() == -1)
    {
        printf("Error Reading Users File !");
        return 1;
    }

    int choice;
Menu:
    printf("\n\t\t\t\t========== Welcome to the  System ==========\n");

    printf("\nPlease choose your operation:\n");

    if (numberOfUsers >= 10)
    {
        do
        {
            printf("\n---- We Don't accept new Patients ---");
            printf("\n1. Login");
            printf("\n2. Exit\n");
            printf("\nYour Choice: ");
            scanf("%d", &choice);
            clearInputBuffer(); // Clear input buffer

            switch (choice)
            {
            case 1:
                login();
                search_doctor(numberOfdoctors);
                break;
            case 2:
                printf("Goodbye!");
                return 0;
                
            default:
                printf("Invalid Choice! Please enter a number between 1 and 3.\n");
                continue;
            }
        } while (1);
    }
    else
    {

        do
        {
            printf("\n1. Signup");
            printf("\n2. Login");
            printf("\n3. Exit\n");
            printf("\nYour Choice: ");
            scanf("%d", &choice);
            clearInputBuffer(); // Clear input buffer

            switch (choice)
            {
            case 1:
                Signup();
                if(numberOfUsers>=10)
                {
                    goto Menu;
                }
                break;
            case 2:
                login();
                search_doctor(numberOfdoctors);
                break;
            case 3:
                printf("Goodbye!");
                return 0;
            default:
                printf("Invalid Choice! Please enter a number between 1 and 3.\n");
                continue;
            }
        } while (1);
    }
}
