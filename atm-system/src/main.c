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
    printf("\n\t\t[8]- Exit\n");
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
        // student TODO : add your **Make transaction** function
        // here
        break;
    case 6:
        // student TODO : add your **Remove existing account** function
        // here
        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        // here
        break;
    case 8:
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
                loginMenu(u->name, u->password);  // Capture username and password
                char *storedPassword = getPassword(*u);
                if (storedPassword == NULL) {
                        printf("User not found!\n");
                        continue;
                    }
                if (strcmp(u->password, getPassword(*u)) == 0) {
                    printf("\n\nPassword Match!\n");
                    free(storedPassword);
                    break;  // Exit the loop if the password is correct
                } else {
                    printf("\nWrong password or username!\n");
                    printf("Re-enter the password or enter \"0\" to exit: ");
                    scanf("%s", u->password);  // Capture new password

                if (strcmp(u->password, "0") == 0) {
                    free(storedPassword); 
                    exit(1);  // Exit if the user wants to quit
                    }
                }
                free(storedPassword);
            }
            r = 1;
            break;
        case 2:
            registerMenu(u->name, u->password)
            r = 1;
            break;
        case 3:
            printf ("\nThank you for visiting us\n")
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
