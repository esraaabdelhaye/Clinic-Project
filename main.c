#include <stdio.h>
#include "SignUp.c"

int main()
{
    ReadDoctorsData();
    ReadUsersData();
    if (ReadUsersData()==-1)
    {
        printf("Error Reading Users File !");
        return 1;
    }

    int choice;

    printf("\n\t\t\t\t========== Welcome to the  System ==========\n");

    do
    {
        printf("\nPlease choose your operation:");
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
            break;
        default:
            printf("Invalid Choice! Please enter a number between 1 and 3.\n");
        }

    } while (choice != 3);
}
