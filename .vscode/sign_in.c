#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

// Define structure to store user data
struct Patient {
    char fullName[50];
    char password[50];
    char username[50]; // Added username member
};

// Function prototypes
void login();
void clearInputBuffer();
void takepassword(char pwd[50]);
void printStars(const char str[]); // Function to print stars
void getPasswordAndShowOption(char password[]); // Function to get password and show option during signup

int main() {
    int choice;

    printf("\n\t\t\t\t========== Welcome to the  System ==========\n");

    do {
        printf("\nPlease choose your operation:");
        printf("\n1. Signup");
        printf("\n2. Login");
        printf("\n3. Exit\n");
        printf("\nYour choice (1 for Signup, 2 for Login, 3 for Exit): ");
        scanf("%d", &choice);
        clearInputBuffer(); // Clear input buffer

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                login();
                break;
            case 3:
                printf("Goodbye!");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 3.\n");
        }

    } while (choice != 3);

    return 0;
}

void login() {
    char username[50];
    char password[50];
    int choice;

    printf("\n\t\t\t\t\t\t========== Login ==========\n");
    int authResult;
    do {
        clearInputBuffer(); // Clear input buffer


        printf("Enter your username: ");
        fgets(username, sizeof(username), stdin);



        printf("Enter your password: ");
        takepassword(password);

        // Authenticate user
        authResult = authenticateUser(username, password);

        if (authResult == 1) {
            printf("\nLogged in successfully!\n");
        } else {
            printf("\nInvalid email or password.\n");
        }
    } while(authResult != 1); // Loop until login is successful
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to take password securely without showing characters
void takepassword(char pwd[50]) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();
        if (ch == '\n' || ch == '\r') {
            pwd[i] = '\0';
            break;
        } else if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            pwd[i++] = ch;
            printf("*");
        }
    }
}

// Function to print characters as stars
void printStars(const char str[]) {
    for (int i = 0; i < strlen(str); i++) {
        printf("*");
    }
}

// Function to get password and show option during signup
void getPasswordAndShowOption(char password[]) {
    int i = 0;
    char ch;
    int hasNumeric = 0; // Flag to track if password contains at least one numeric value
    int hasSymbol = 0; // Flag to track if password contains at least one symbol

    printf("Enter your password (at least one symbol and one numeric value required): ");
    while (1) {
        ch = getch();
        if (ch == '\n' || ch == '\r') {
            password[i] = '\0';
            break;
        } else if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
            if (!hasSymbol && ispunct(ch)) {
                hasSymbol = 1;
            }
            if (!hasNumeric && isdigit(ch)) {
                hasNumeric = 1;
            }
        }
    }

    // Show option to display password
    printf("\nDo you want to show your password? (1 for Yes, 0 for No): ");
    int showPassword;
    scanf("%d", &showPassword);
    clearInputBuffer(); // Clear input buffer

    if (showPassword) {
        printf("Your password is: %s\n", password);
    }

    // Validate password complexity
    if (!hasNumeric || !hasSymbol) {
        printf("Password must contain at least one symbol and one numeric value. Please try again.\n");
        getPasswordAndShowOption(password);
    }
}

