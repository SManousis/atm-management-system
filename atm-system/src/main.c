#include "header.h"

void mainMenu(struct User u)
{
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit to log in menu\n");
    printf("\n\t\t[9]- Exit the program\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        updateAcc(u);
        break;
    case 3:
        checkAccount(u);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        accountTransaction(u);
        break;
    case 6:
        accountRemoval(u);
        break;
    case 7:
        transferAccount(u);
        break;
    case 8:
        initMenu(&u);
        break;
    case 9:
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;
    
    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            while (1) {
                // Prompt for username
                getUsername(u->name);

                // Check if user exists
                char *storedPassword = getPassword(*u);

                if (storedPassword == NULL) {
                    printf("\t\t\t\t User not found! Please try again or register.\n");
                    getchar();
                    continue;  // Loop back to prompt for username again
                }

                // Prompt for password
                getPasswordInput(u->password);
                unsigned long hashedPassword = simpleHash(u->password);  // Hash entered password
                unsigned long storedHash = strtoul(storedPassword, NULL, 10);  // Convert stored hash
                        // Compare passwords
                if (hashedPassword == storedHash) {
                    printf("\n\n\t\t\t\t Password Match!\n");
                    free(storedPassword);
                    getchar();
                    mainMenu(*u);  // Redirect to main menu
                    return;  // Exit initMenu after successful login
                } else {
                    printf("\n\t\t\t\t Wrong password!\n");
                    printf("\t\t\t\t Re-enter the password or enter \"0\" to exit:\n");
                    getchar();
                    getPasswordInput(u->password);

                    if (strcmp(u->password, "0") == 0) {
                        free(storedPassword);
                        break;  // Exit login loop to return to initMenu
                    }

                    
                    unsigned long hashedPassword = simpleHash(u->password);  // Hash entered password
                    unsigned long storedHash = strtoul(storedPassword, NULL, 10);  // Convert stored hash
                        // Compare passwords
                    if (hashedPassword == storedHash)  {
                        printf("\n\n\t\t\t\t Password Match!\n");
                        free(storedPassword);
                        getchar();
                        mainMenu(*u);  // Redirect to main menu
                        return;  // Exit initMenu after successful login
                    } else {
                        printf("\n\t\t\t\t Wrong password!\n");
                        getchar();
                        free(storedPassword);
                        continue;  // Loop back to prompt for username again
                    }
                }
            }
            r = 1;
            break;
        case 2:
            registerMenu(u);
            r = 1;
            break;
        case 3:
            printf ("\nThank you for visiting us\n");
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
        }
    }
};

int main()
{
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
