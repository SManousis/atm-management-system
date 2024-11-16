#include "header.h"

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
		  &r->userId,
		  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r->id,
	    u->id
	    u->name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);
    int option;
    int option;
    int validInput = 0;

    while (getAccountFromFile(pf, userName, &cr)) {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr) {
            printf("✖ This Account already exists for this user\n\n");
            printf("If you still want to make a new account, enter \"0\".\n");
            printf("If you are an existing user and want to login, enter \"1\".\n");
            printf("Otherwise, enter \"2\" to exit the program.\n");

            do {
                printf("Enter your choice: ");
                scanf("%d", &option);

                switch (option) {
                    case 0:
                        validInput = 1;
                        // Break out of the inner loop and restart account creation.
                        break;

                    case 1:
                        validInput = 1;
                        printf("Redirecting to the login menu...\n");
                        // Call the login menu or sign-in functionality here
                        initMenu(&u);  // Assuming initMenu() handles login
                        return;        // Exit the account creation if they go to login

                    case 2:
                        validInput = 1;
                        printf("Thank you for visiting us!\n");
                        fclose(pf);
                        exit(0);

                    default:
                        printf("Insert a valid operation!\n");
                        break;
                }
         } while (!validInput);
        }
    }

    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void registerMenu(char a[50], char pass[50]) {
    struct User newUser, existingUser;
    FILE *fp =fopen(USERS, "+a");
    if (fp == NULL){
        perror("Error opening users file");
        exit(1)
    }
    pritnf("\nPlease enter a user name:")
    scanf("49%s", nameUser.name);

    while (fscanf(fp "%s%s", existingUser.name, existingUser.password) != EOF){
        if (strcmp(newUser.name, existingUser.name) == 0){
            printf("Username already exist! Please enter a new username or login\n");
            fclose(fp);
            return;
        }
    }
    char passwordVerify[50];

    while (1) {
        printf("\nEnter a password: ");
        scanf("%49s", newUser.password);  

        printf("\nPlease enter the password again: ");
        scanf("%49s", passwordVerify);    

        if (strcmp(newUser.password, passwordVerify) != 0) {
            printf("\nPasswords don't match.");
            printf("\nRe-enter the password or enter \"0\" to exit: ");
        
            // Capture input to check if user wants to exit
            scanf("%49s", passwordVerify);
            if (strcmp(passwordVerify, "0") == 0) {
                printf("Exiting registration...\n");
                return;  // Exit the function
            }
        } else {
            printf("\nPasswords match. Registration proceeding.\n");
            break;  // Exit the loop on successful match
        }
    }
    
    

    newUser.id = rand() % 10000;

    fprintf(fp, "%s %s/n", newUser.name, newUser.password);
    fclose(fp);

    printf("Registration completly succesfully. You may now log in.\n");
}