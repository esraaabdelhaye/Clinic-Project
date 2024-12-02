#include <stdio.h>
#include "SignUp.c"

int main()
{
    ReadDoctorsData();
    //There was a mistake here causing Double counting 
    //This happend because the function was called twice (one like the doctors and the other inside the condition)
    if (ReadUsersData() == -1)
    {
        printf("Error Reading Users File !");
        return 1;
    }

    int choice;

    printf("\n\t\t\t\t========== Welcome to the  System ==========\n");

    printf("\nCurrent Users = %d\n",numberOfUsers);
    printf("\nCurrent Doctors = %d\n",numberOfdoctors);
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
                // login();
                break;
            case 2:
                printf("Goodbye!");
                return 0;
                
            default:
                printf("Invalid Choice! Please enter a number between 1 and 3.\n");
            }
        } while (choice != 3);
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
                break;
            case 2:
                // login();
                break;
            case 3:
                printf("Goodbye!");
                return 0;
            default:
                printf("Invalid Choice! Please enter a number between 1 and 3.\n");
            }
        } while (choice != 3);
    }
}
