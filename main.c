#include <stdio.h>
#include "Search.c"
// Baiscally Search includes login, login includes signup, signup includes readfunctions
// which makes including search only in main valid!

int main()
{
    if (ReadDoctorsData() == -1)
    {
        printf("\033[0;31m");
        printf("Error Reading Doctors File !");
        printf("\033[0m");
        return 1;
    }
    if (ReadUsersData() == -1)
    {
        printf("\033[0;31m");
        printf("Error Reading Users File !");
        printf("\033[0m");
        return 1;
    }
    int choice;
Menu:
    printf("\n\t\t========== Welcome to the  System ==========\n");
    printf("\033[0;32m");
    printf("Active Users: %d\n", numberOfUsers);
    printf("Active Doctors: %d\n", numberOfdoctors);
    printf("\033[0;34m");
    printf("\nPlease choose your operation:\n");
    printf("\033[0m");

    // if (numberOfUsers >= 10)
    // {
    //     do
    //     {
    //         printf("\033[0;31m");
    //         printf("\n---- We Don't accept new Patients ---");
    //         printf("\033[0m");
    //         printf("\n1. Login");
    //         printf("\n2. Exit\n");
    //         printf("\033[0;34m");
    //         printf("\nYour Choice: ");
    //         printf("\033[0m");
    //         char choiceinput[1000];
    //         fgets(choiceinput, 1000, stdin);
    //         choiceinput[strlen(choiceinput) - 1] = '\0';
    //         if (strlen(choiceinput) != 1)
    //             choice = 10;
    //         else
    //             choice = atoi(choiceinput);
    //         // int scancheck = scanf("%d%c", &choice, &newline);
    //         // if (scancheck != 2 || newline != '\n'||choice=='\n')
    //         // {
    //         //     choice = 10;
    //         //     clearInputBuffer(); // Clear input buffer
    //         // }

    //         switch (choice)
    //         {
    //         case 1:
    //             login();
    //             if (LoginComplete)
    //             {
    //                 search_doctor(numberOfdoctors);
    //             }
    //             else
    //             {
    //                 printf("\033[0;31m");
    //                 printf("\nUsername Not Registered. SignUp first.");
    //                 printf("\033[0m");
    //                 goto Menu;
    //             }
    //             break;
    //         case 2:
    //             printf("\033[0;32m");
    //             printf("Goodbye!");
    //             printf("\033[0m");
    //             return 0;

    //         default:
    //             printf("\033[0;31m");
    //             printf("Invalid Choice! Please enter a number between 1 and 2.\n");
    //             printf("\033[0m");
    //             continue;
    //         }
    //     } while (1);
    // }
    // else
    // {

        do
        {
            printf("\n1. Signup");
            printf("\n2. Login");
            printf("\n3. Exit\n");
            printf("\033[0;34m");
            printf("\nYour Choice: ");
            printf("\033[0m");
            char choiceinput[1000];
            fgets(choiceinput, 1000, stdin);
            choiceinput[strlen(choiceinput) - 1] = '\0';
            if (strlen(choiceinput) != 1)
                choice = 10;
            else
                choice = atoi(choiceinput);
            // int scancheck = scanf("%d%c", &choice, &newline);
            // if (scancheck != 2 || newline != '\n')
            // {
            //     choice = 10;
            //     clearInputBuffer(); // Clear input buffer
            // }

            switch (choice)
            {
            case 1:
                Signup();
                goto Menu;
                break;
            case 2:
                login();
                if (LoginComplete)
                {
                    search_doctor(numberOfdoctors);
                }
                else
                {
                    printf("\033[0;31m");
                    printf("\nUsername Not Registered. SignUp first.");
                    printf("\033[0m");
                    goto Menu;
                }
                break;
            case 3:
                printf("\033[0;32m");
                printf("Goodbye!");
                printf("\033[0m");
                return 0;
            default:
                printf("\033[0;31m");
                printf("Invalid Choice! Please enter a number between 1 and 3.\n");
                printf("\033[0m");
                continue;
            }
        } while (1);
    // }
}

/*
color guide
red   printf("\033[0;31m");
Green printf("\033[0;32m");
Blue printf("\033[0;34m");
Purple printf("\033[0;35m");
reset printf("\033[0m");
This Method Won't Work on Clion...
*/