#include "header.h"

const char *RECORDS = "./data/records.txt";
const char *validCountries[] = {
    "United States", "Canada", "United Kingdom", "Germany", "France",
    "Australia", "Japan", "India", "China", "Brazil",
    "South Korea", "Mexico", "Russia", "Italy", "Spain",
    "Netherlands", "Turkey", "Switzerland", "Saudi Arabia", "Sweden",
    "Norway", "Argentina", "South Africa", "Poland", "Indonesia",
    "Belgium", "Austria", "Denmark", "Singapore", "Malaysia",
    "Thailand", "Philippines", "Vietnam", "Nigeria", "Egypt",
    "Pakistan", "Bangladesh", "Ireland", "New Zealand", "Portugal",
    "Greece", "Israel", "Finland", "Chile", "Colombia",
    "Czech Republic", "Hungary", "Romania", "Slovakia", "Peru", "Greece"
};

const int countryCount = 51;

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
    int valid = 0;
    while (!valid){
        printf("\nEnter the country:");
        scanf("%s", r.country);
        for (int i = 0; i < countryCount; i++){
            if (strcmp(r.country, validCountries[i])) == 0{
                valid = 1;
                break;
            }
        }
        if (!valid){
            printf("\n✖ Invalid country! Please enter a valid country.\n")
        }
    }
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    
    while (1){
        printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
        scanf("%s", r.accountType);
        if (strcmp(r.accountType, "saving")) == 0 ||
            (strcmp(r.accountType, "current")) == 0 ||
            (strcmp(r.accountType, "fixed01")) == 0 ||
            (strcmp(r.accountType, "fixed02")) == 0 ||
            (strcmp(r.accountType, "fixed03")) == 0 ||{
                break;
            }else{
                printf("\n✖ Invalid account type! Please enter a valid account type.\n");
            }
    }
        
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

void updateAcc(struct User u) {
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "r+");
    if (pf == NULL) {
        perror("Error opening file");
        return;
    }

    system("clear");
    printf("\nPlease enter the account number: ");
    scanf("%d", &r.accountNbr);

    int valid = 0;
    int option;
    int option1;
    int validInput = 0;
    int found = 0;  // Track if account is found
    while (getAccountFromFile(pf, userName, &cr)) {
        if (cr.accountNbr == r.accountNbr && strcmp(userName, u.name) == 0) {
            found = 1;  // Account exists, proceed to update
            
            do{
                printf("\nIf you want to update the country, please enter \"0\".\n");
                printf("If you want to change the phone number, please enter \"1\".\n");
                printf("Enter your choice: ");
                scanf("%d", &option1);
                switch (option1)
                {
                case 0:
                    while (!valid){
                        printf("\nEnter the country:");
                        scanf("%s", r.country);
                        for (int i = 0; i < countryCount; i++){
                            if (strcmp(r.country, validCountries[i])) == 0{
                                valid = 1;
                                strcpy(cr.country, r.country);
                                break;
                            }
                        }
                        if (!valid){
                            printf("\n✖ Invalid country! Please enter a valid country.\n")
                        }
                    }
                    break;

                case 1:
                    printf("\nEnter the new phone number or enter \"0\" to remain unchanged: ");
                    scanf("%d", &r.phone);
                    if (r.phone != 0) {
                            cr.phone = r.phone;  // Update phone
                        }
                    break;

                default:
                    printf("Insert a valid operation!\n");
                    break;
                }
            }
             // Update completed, prepare to rewrite the file
            FILE *tempFile = fopen("temp.txt", "w");
            if (tempFile == NULL) {
                perror("Error creating temporary file");
                fclose(pf);
                return;
            }

            rewind(pf);  // Start from the beginning of the file
            while (getAccountFromFile(pf, userName, &cr)) {
                saveAccountToFile(tempFile, u, cr);
            }

            fclose(pf);
            fclose(tempFile);

            remove(RECORDS);
            rename("temp.txt", RECORDS);

            printf("\n✔ Account updated successfully!\n");
            success(u);  // Display success message and options
            return;
        }
    }

    if (!found) {  // Account not found, handle this case
        printf("✖ This Account does not exist for this user\n\n");
        printf("If you intend to update the account, enter \"0\".\n");
        printf("If you want to make a new account, enter \"1\".\n");
        printf("Otherwise, enter \"2\" to exit the program.\n");

        do {
            printf("Enter your choice: ");
            scanf("%d", &option);

            switch (option) {
                case 0:
                    validInput = 1;  // Retry updating account
                    updateAcc(u);
                    return;

                case 1:
                    validInput = 1;  // Redirect to account creation
                    createNewAcc(u);
                    return;

                case 2:
                    validInput = 1;  // Exit the program
                    printf("Thank you for visiting us!\n");
                    fclose(pf);
                    exit(0);

                default:
                    printf("Insert a valid operation!\n");
                    break;
            }
        } while (!validInput);
    }

    fclose(pf);
}

void checkAccount(struct User u){
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "r+");
    if (pf == NULL) {
        perror("Error opening file");
        return;
    }

    system("clear");
    int found = 0;
    
    while(1) {
        printf("\nPlease enter the account number you need details of (or enter \"0\" to exit): ");
        scanf("%d", &r.accountNbr);
        if (r.accountNbr == 0){
                printf("Thank you for visiting us!\n");
                    fclose(pf);
                    exit(0);
            }
        rewind(pf);
        while (getAccountFromFile(pf, userName, &cr)){
            if (cr.accountNbr == r.accountNbr && strcmp(userName, u.name) == 0) {
            found = 1;
            printf("\n✔ Account Details:\n");
                printf("Account Number: %d\n", cr.accountNbr);
                printf("Account Type: %s\n", cr.accountType);
                printf("Deposit Amount: $%.2f\n", cr.amount);
                printf("Deposit Date: %02d/%02d/%04d\n", cr.deposit.day, cr.deposit.month, cr.deposit.year);
                
                // Calculate interest based on account type
                if (strcmp(cr.accountType, "savings") == 0) {
                    double interest = cr.amount * 0.07 / 12;
                    printf("You will get $%.2f as interest on day %d of every month.\n", interest, cr.deposit.day);
                } else if (strcmp(cr.accountType, "fixed01") == 0) {
                    double interest = cr.amount * 0.04 / 12;
                    printf("You will get $%.2f as interest on day %d of every month.\n", interest, cr.deposit.day);
                } else if (strcmp(cr.accountType, "fixed02") == 0) {
                    double interest = cr.amount * 0.05 / 12;
                    printf("You will get $%.2f as interest on day %d of every month.\n", interest, cr.deposit.day);
                } else if (strcmp(cr.accountType, "fixed03") == 0) {
                    double interest = cr.amount * 0.08 / 12;
                    printf("You will get $%.2f as interest on day %d of every month.\n", interest, cr.deposit.day);
                } else if (strcmp(cr.accountType, "current") == 0) {
                    printf("You will not get interests because the account is of type current.\n");
                } else {
                    printf("Unknown account type.\n");
                }

            }
        }
        if !(found){
            printf("\n✖ This Account does not exist for this user. Please try again.\n")
        }
    }
}

void accountTransaction(struct User u) {
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "r+");
    if (pf == NULL) {
        perror("Error opening file");
        return;
    }

    system("clear");
    int found = 0;
    int option;
    double newTotal;

    while (1) {
        printf("\nPlease enter the account number you need details of (or enter \"0\" to exit): ");
        scanf("%d", &r.accountNbr);

        if (r.accountNbr == 0) {
            printf("Thank you for visiting us!\n");
            fclose(pf);
            return;
        }

        rewind(pf);  // Reset file pointer to start reading
        while (getAccountFromFile(pf, userName, &cr)) {
            if (cr.accountNbr == r.accountNbr && strcmp(userName, u.name) == 0) {
                found = 1;

                // Check for fixed account types
                if (strcmp(cr.accountType, "fixed01") == 0 ||
                    strcmp(cr.accountType, "fixed02") == 0 ||
                    strcmp(cr.accountType, "fixed03") == 0) {
                    printf("\n✖ It is not possible to withdraw or deposit from this account type.\n");
                    printf("Please try with a different account.\n");
                    return;
                }

                printf("\nIf you want to make a deposit, please enter \"0\".\n");
                printf("If you want to make a withdrawal, please enter \"1\".\n");
                printf("Otherwise, enter \"2\" to exit.\n");

                do {
                    printf("Enter your choice: ");
                    scanf("%d", &option);

                    switch (option) {
                        case 0:  // Deposit
                            printf("Enter the amount you want to deposit: ");
                            scanf("%lf", &r.amount);
                            newTotal = cr.amount + r.amount;
                            cr.amount = newTotal;
                            printf("✔ Deposit successful! Your new total is $%.2f\n", newTotal);
                            break;

                        case 1:  // Withdrawal
                            printf("Enter the amount you want to withdraw: ");
                            scanf("%lf", &r.amount);
                            while (r.amount > cr.amount) {
                                printf("\n✖ Not enough funds.\n");
                                printf("Your current total is $%.2f. Please enter a valid amount: ", cr.amount);
                                scanf("%lf", &r.amount);
                            }
                            newTotal = cr.amount - r.amount;
                            cr.amount = newTotal;
                            printf("✔ Withdrawal successful! Your new total is $%.2f\n", newTotal);
                            break;

                        case 2:  // Exit
                            printf("Thank you for visiting us!\n");
                            fclose(pf);
                            return;

                        default:
                            printf("✖ Invalid choice. Please try again.\n");
                            break;
                    }

                } while (option != 2);

                // Save updated account record to the file
                FILE *tempFile = fopen("temp.txt", "w");
                if (tempFile == NULL) {
                    perror("Error creating temporary file");
                    fclose(pf);
                    return;
                }

                rewind(pf);  // Rewind original file pointer
                while (getAccountFromFile(pf, userName, &cr)) {
                    saveAccountToFile(tempFile, u, cr);
                }

                fclose(pf);
                fclose(tempFile);

                remove(RECORDS);
                rename("temp.txt", RECORDS);

                printf("\n✔ Account updated successfully!\n");
                return;
            }
        }

        if (!found) {
            printf("\n✖ This account does not exist for this user. Please try again.\n");
        }
    }
}
