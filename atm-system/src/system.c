#include "header.h"

const char *RECORDS = "./data/records.txt";
const char *validCountries[] = {
    "United States", "Canada", "United Kingdom", "Germany", "France","Africa","Europe",
    "Australia", "Japan", "India", "China", "Brazil","America"
    "South Korea", "Mexico", "Russia", "Italy", "Spain",
    "Netherlands", "Turkey", "Switzerland", "Saudi Arabia", "Sweden",
    "Norway", "Argentina", "South Africa", "Poland", "Indonesia",
    "Belgium", "Austria", "Denmark", "Singapore", "Malaysia",
    "Thailand", "Philippines", "Vietnam", "Nigeria", "Egypt",
    "Pakistan", "Bangladesh", "Ireland", "New Zealand", "Portugal",
    "Greece", "Israel", "Finland", "Chile", "Colombia",
    "Czech Republic", "Hungary", "Romania", "Slovakia", "Peru", "Greece", "UK", "GR", "USA"
};

const int countryCount = 57;
const char *USERS = "./data/users.txt"; 
int getAccountFromFile(FILE *ptr, char name[50], struct Record *r) {
    // Adjust the format specifiers based on your file's actual format.
    int fieldsRead = fscanf(ptr, "%d %d %49s %d %d/%d/%d %49s %d %lf %49s",
                            &r->id,
                            &r->userId,
                            name,  // Ensures name is limited to 49 characters
                            &r->accountNbr,
                            &r->deposit.month,
                            &r->deposit.day,
                            &r->deposit.year,
                            r->country,  // Ensure country is within its buffer limit
                            &r->phone,
                            &r->amount,
                            r->accountType);  // Ensure accountType is within its buffer limit

    // Return 1 if all fields are successfully read, 0 otherwise.
    return fieldsRead == 11;  // Expecting 11 fields in total
}


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r) {
    // // Debugging output
    // printf("Debug: Saving - ID: %d, UserID: %d, Name: %s, AccountNbr: %d, "
    //        "Date: %02d/%02d/%04d, Country: %s, Phone: %d, Amount: %.2lf, AccountType: %s\n",
    //        r.id, u.id, u.name, r.accountNbr,
    //        r.deposit.month, r.deposit.day, r.deposit.year,
    //        r.country, r.phone, r.amount, r.accountType);

    // Save the record to the file
    fprintf(ptr, "%d %d %s %d %02d/%02d/%04d %s %d %.2lf %s\n",
            r.id,        // %d for Record ID
            u.id,        // %d for User ID
            u.name,      // %s for User Name
            r.accountNbr,// %d for Account Number
            r.deposit.month, r.deposit.day, r.deposit.year,  // %02d/%02d/%04d for Date
            r.country,   // %s for Country
            r.phone,     // %d for Phone Number
            r.amount,    // %.2lf for Amount
            r.accountType); // %s for Account Type
}

int isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;

    // Handle months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return 0;

    // Handle February
    if (month == 2) {
        int isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > 29 || (day == 29 && !isLeapYear)) return 0;
    }
    return 1;
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

// Function to read a valid integer from the user
int getValidInteger(const char *prompt) {
    char input[100];
    char *endptr;
    int value;

    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove trailing newline character
            input[strcspn(input, "\n")] = '\0';

            // Check if input is empty
            if (strlen(input) == 0) {
                printf("✖ Invalid input! Input cannot be empty.\n");
                continue;
            }

            // Convert string to integer
            value = strtol(input, &endptr, 10);

            // Check for conversion errors
            if (*endptr != '\0') {
                printf("✖ Invalid input! Please enter a valid integer.\n");
            } else {
                return value;
            }
        } else {
            printf("✖ Error reading input! Please try again.\n");
        }
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

// Function to read a valid double from the user
double getValidDouble(const char *prompt) {
    char input[100];
    char *endptr;
    double value;

    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove trailing newline character
            input[strcspn(input, "\n")] = '\0';

            // Check if input is empty
            if (strlen(input) == 0) {
                printf("✖ Invalid input! Input cannot be empty.\n");
                continue;
            }

            // Convert string to double
            value = strtod(input, &endptr);

            // Check for conversion errors
            if (*endptr != '\0') {
                printf("✖ Invalid input! Please enter a valid number.\n");
            } else {
                return value;
            }
        } else {
            printf("✖ Error reading input! Please try again.\n");
        }
    }
}


void getValidDate(int *day, int *month, int *year) {
    char dateInput[11];
    while (1) {
        clearInputBuffer();
        printf("Enter today's date(mm/dd/yyyy):");
        fgets(dateInput, sizeof(dateInput), stdin);
        dateInput[strcspn(dateInput, "\n")] = 0;  // Remove trailing newline

        // Check if input is in the correct format
        if (sscanf(dateInput, "%d/%d/%d", month, day, year) == 3) {
            if (isValidDate(*day, *month, *year)) {
                break;  // Valid date, exit loop
            } else {
                printf("Invalid date. Please enter a valid date.\n");
            }
            
        } else {
            printf("\nInvalid format. Press enter to continue");
        }
    }
}

void createNewAcc(struct User u) {
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    if (pf == NULL) {
        perror("Error opening file");
        return;
    }
    int maxID = 0;  // Start with 0 to find the highest ID

    // Open the file to find the maximum account ID
    FILE *readFp = fopen(RECORDS, "r");
    if (readFp == NULL) {
        perror("Error opening records file for reading");
        fclose(pf);
        return;
    }

    // Iterate through the file to find the highest ID
    while (getAccountFromFile(readFp, userName, &cr)) {
        if (cr.id > maxID) {
            maxID = cr.id;
        }
    }
    fclose(readFp);  // Close readFp after use

    // Open users file to get userId
    FILE *userFile = fopen(USERS, "r");
    if (userFile == NULL) {
        perror("Error opening users file");
        fclose(pf);
        return;
    }
    struct User tempUser;
    int userIdFound = 0;

    while (fscanf(userFile, "%d %s %s", &tempUser.id, tempUser.name, tempUser.password) == 3) {
        if (strcmp(tempUser.name, u.name) == 0) {
            r.userId = tempUser.id; 
            u.id = tempUser.id;      // Ensure u.id is set
            userIdFound = 1;
            break;
        }
    }

    fclose(userFile);

    if (!userIdFound) {
        printf("Error: User not found in users file. Cannot create account.\n");
        fclose(pf);
        return;
    }

    system("clear");
    printf("\t\t\t===== New record =====\n");
    r.id = maxID + 1;

    // Get valid date
    int day, month, year;
    getValidDate(&day, &month, &year);

    // Assign date to struct
    r.deposit.day = day;
    r.deposit.month = month;
    r.deposit.year = year;
    clearInputBuffer();
    // Get valid account number
    r.accountNbr = getValidInteger("\nEnter an account number: ");

    // Check for duplicate account number
    rewind(pf);  // Reset file pointer to start reading
    int option;
    int validInput = 0;

    while (getAccountFromFile(pf, userName, &cr)) {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr) {
            printf("✖ This Account already exists for this user\n\n");
            printf("If you still want to make a new account, enter \"0\".\n");
            printf("If you are an existing user and want to login, enter \"1\".\n");
            printf("Otherwise, enter \"2\" to exit the program.\n");

            do {
                option = getValidInteger("Enter your choice: ");

                switch (option) {
                    case 0:
                        validInput = 1;
                        // Restart account creation
                        fclose(pf);
                        createNewAcc(u);
                        return;
                    case 1:
                        validInput = 1;
                        printf("Redirecting to the login menu...\n");
                        fclose(pf);
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

    // Get valid country
    int valid = 0;
    while (!valid) {
        printf("\nEnter the country: ");
        fgets(r.country, sizeof(r.country), stdin);
        r.country[strcspn(r.country, "\n")] = '\0';  // Remove newline

        for (int i = 0; i < countryCount; i++) {
            if (strcmp(r.country, validCountries[i]) == 0) {
                valid = 1;
                break;
            }
        }
        if (!valid) {
            printf("\n✖ Invalid country! Please enter a valid country.\n");
        }
    }

    // Get valid phone number
    r.phone = getValidInteger("\nEnter the phone number: ");

    // Get valid amount to deposit
    r.amount = getValidDouble("\nEnter amount to deposit: $");

    // Get valid account type
    int option2;
    while (1) {
        printf("\nChoose the type of account:\n");
        printf("\t-> For saving account choose \"0\"\n");
        printf("\t-> For current account choose \"1\"\n");
        printf("\t-> For fixed for 1 year (fixed01) choose \"2\"\n");
        printf("\t-> For fixed for 2 years (fixed02) choose \"3\"\n");
        printf("\t-> For fixed for 3 years (fixed03) choose \"4\"\n\n");
        
        option2 = getValidInteger("\tEnter your choice: ");

        // Assign account type based on choice
        switch (option2) {
            case 0:
                strcpy(r.accountType, "saving");
                break;
            case 1:
                strcpy(r.accountType, "current");
                break;
            case 2:
                strcpy(r.accountType, "fixed01");
                break;
            case 3:
                strcpy(r.accountType, "fixed02");
                break;
            case 4:
                strcpy(r.accountType, "fixed03");
                break;
            default:
                printf("\n✖ Invalid choice! Please select a number between 0 and 4.\n");
                continue;
        }
        // Valid account type selected, exit the loop
        break;
    }

    // Save account to file
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



char *readLine(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin) != NULL) {
        // Remove trailing newline character, if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len -1] == '\n') {
            buffer[len -1] = '\0';
        }
        return buffer;
    }
    return NULL;
}

void registerMenu(struct User *u) {
    struct User newUser, existingUser;
    FILE *fp = fopen(USERS, "a+");
    if (fp == NULL) {
        perror("Error opening users file");
        exit(1);
    }

    printf("\nPlease enter a user name: ");
    clearInputBuffer();
    readLine(newUser.name, sizeof(newUser.name));

    int maxID = -1;

    // Open file to read existing users
    FILE *readFp = fopen(USERS, "r");
    if (readFp == NULL) {
        perror("Error opening users file for reading");
        fclose(fp);
        exit(1);
    }

    // Read existing users and check for duplicates
    char line[256];
    while (fgets(line, sizeof(line), readFp) != NULL) {
        int numFields = sscanf(line, "%d %s %s", &existingUser.id, existingUser.name, existingUser.password);
        if (numFields == 3) {
            // Debugging output
            // printf("Debug: Read user - ID: %d, Name: %s, Password: %s\n", existingUser.id, existingUser.name, existingUser.password);

            // Check for duplicate username
            if (strcmp(newUser.name, existingUser.name) == 0) {
                printf("Username already exists! Please enter a new username or login.\n");
                fclose(fp);
                fclose(readFp);

                printf("Press Enter to continue...");
                getchar(); // Consume leftover newline
                

                initMenu(u);
                return;
            }

            // Update maxID
            if (existingUser.id > maxID) {
                maxID = existingUser.id;
            }
        } else {
            // Handle malformed lines if necessary
        }
    }

    fclose(readFp);

    // Assign new user ID
    newUser.id = maxID + 1;
    // printf("Debug: Assigned new user ID: %d\n", newUser.id);

    // Proceed with password input and verification
    char passwordVerify[50];
    while (1) {
        printf("\nEnter a password: ");
        readLine(newUser.password, sizeof(newUser.password));

        printf("\nPlease enter the password again: ");
        readLine(passwordVerify, sizeof(passwordVerify));

        if (strcmp(newUser.password, passwordVerify) != 0) {
            printf("\nPasswords don't match.");
            printf("\nRe-enter the password or enter \"0\" to exit: ");
            readLine(passwordVerify, sizeof(passwordVerify));

            if (strcmp(passwordVerify, "0") == 0) {
                printf("Exiting registration...\n");
                fclose(fp);

                printf("Press Enter to continue...");
                getchar(); // Wait for Enter

                initMenu(u);
                return;
            }
        } else {
            printf("\nPasswords match. Registration proceeding.\n");
            break;
        }
    }

    // Hash the password and save to file
    unsigned long hashedPassword = simpleHash(newUser.password);

    // Debugging output before writing to file
    // printf("Debug: Writing to file - ID: %d, Name: %s, Hashed Password: %lu\n", newUser.id, newUser.name, hashedPassword);

    fprintf(fp, "%d %s %lu\n", newUser.id, newUser.name, hashedPassword);
    fclose(fp);

    printf("Registration completed successfully. You may now log in.\n");
    printf("Press Enter to continue...");
    getchar(); // Wait for Enter

    initMenu(u);
}





void updateAcc(struct User u) {
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "r");
    if (pf == NULL) {
        perror("Error opening records file");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(pf);
        return;
    }

    system("clear");
    printf("\nPlease enter the account number: ");
    scanf("%d", &r.accountNbr);

    int option1;
    int validInput = 0;
    int found = 0;  // Track if account is found

    rewind(pf);  // Ensure we start from the beginning of the file

    while (getAccountFromFile(pf, userName, &cr)) {
        if (cr.accountNbr == r.accountNbr && strcmp(userName, u.name) == 0) {
            found = 1;  // Account exists, proceed to update
            int exitUpdate = 0;
            do {
                printf("\nIf you want to update the country, please enter \"0\".\n");
                printf("If you want to change the phone number, please enter \"1\".\n");
                printf("If you want to apply the changes please enter \"2\".\n");
                printf("Enter your choice: ");
                scanf("%d", &option1);
                switch (option1) {
                    case 0: {
                        int valid = 0;  // Reset valid before the loop
                        while (!valid) {
                            printf("\nEnter the country: ");
                            scanf("%s", r.country);
                            for (int i = 0; i < countryCount; i++) {
                                if (strcmp(r.country, validCountries[i]) == 0) {
                                    valid = 1;
                                    strcpy(cr.country, r.country);
                                    printf("\nCountry was updated.");
                                    break;
                                }
                            }
                            if (!valid) {
                                printf("\n✖ Invalid country! Please enter a valid country.\n");
                            }
                        }
                        break;
                    }
                    case 1:
                        //printf("\nEnter the new phone number or enter \"0\" to remain unchanged: ");
                        clearInputBuffer();
                        r.phone = getValidInteger("\nEnter the new phone number or enter \"0\" to remain unchanged: ");
                        if (r.phone != 0) {
                            cr.phone = r.phone;
                            printf("\nPhone number was updated.");  // Update phone
                        }
                        break;
                    case 2:
                        printf("\nReturning to the main menu...\n");
                        exitUpdate = 1;  // Flag to exit the update loop
                        break;
                    default:
                        printf("Insert a valid operation!\n");
                        break;
                }
            } while (!exitUpdate);
            struct User tempUser;
            // After updating, write the updated record to tempFile
            strcpy(tempUser.name, userName);
            tempUser.id = cr.userId;
            saveAccountToFile(tempFile, tempUser, cr);
        } else {
            
            // Write the original record to tempFile
            struct User tempUser;
            strcpy(tempUser.name, userName);
            tempUser.id = cr.userId;
            saveAccountToFile(tempFile, tempUser, cr);
        }
    }

    fclose(pf);
    fclose(tempFile);

    if (found) {
        remove(RECORDS);
        rename("temp.txt", RECORDS);
        printf("\n✔ Account updated successfully!\n");
        success(u);  // Display success message and options
    } else {
        // Handle account not found
        printf("✖ This Account does not exist for this user\n\n");
        printf("If you intend to update the account, enter \"0\".\n");
        printf("If you want to make a new account, enter \"1\".\n");
        printf("Otherwise, enter \"2\" to exit to the main menu.\n");

        do {
            printf("Enter your choice: ");
            scanf("%d", &option1);

            switch (option1) {
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
                    printf("You are now returning to the main menu\n");
                    mainMenu(u);
                default:
                    printf("Insert a valid operation!\n");
                    break;
            }
        } while (!validInput);

        // Remove the temporary file as it's not needed
        remove("temp.txt");
    }
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
        printf("\nPlease enter the account number you need details of (or enter \"0\" to exit to the menu): ");
        scanf("%d", &r.accountNbr);
        if (r.accountNbr == 0){
                printf("Thank you for visiting us!\n");
                    fclose(pf);
                    mainMenu(u);
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
                if (strcmp(cr.accountType, "saving") == 0) {
                    double interest = cr.amount * 0.07 / 12;
                    printf("You will get $%.2f as interest on day %d of every month.\n", interest, cr.deposit.day);
                } else if (strcmp(cr.accountType, "fixed01") == 0) {
                    double interest = cr.amount * 0.04;
                    int fixed01Year = cr.deposit.year+1;
                    printf("You will get $%.2f as interest on %d/%d/%d \n", interest, cr.deposit.month, cr.deposit.day, fixed01Year);
                } else if (strcmp(cr.accountType, "fixed02") == 0) {
                    double interest = cr.amount * 0.1;
                    int fixed02Year = cr.deposit.year+2;
                    printf("You will get $%.2f as interest on %d/%d/%d \n", interest, cr.deposit.month, cr.deposit.day, fixed02Year);
                } else if (strcmp(cr.accountType, "fixed03") == 0) {
                    double interest = cr.amount * 0.24;
                    int fixed03Year = cr.deposit.year+3;
                    printf("You will get $%.2f as interest on %d/%d/%d \n", interest, cr.deposit.month, cr.deposit.day, fixed03Year);
                } else if (strcmp(cr.accountType, "current") == 0) {
                    printf("You will not get interests because the account is of type current.\n");
                } else {
                    printf("Unknown account type.\n");
                }

            }
        }
        if (!found){
            printf("\n✖ This Account does not exist for this user. Please try again.\n");
        }
    }
}

void accountTransaction(struct User u) {
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "r");
    if (pf == NULL) {
        perror("Error opening file");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(pf);
        return;
    }

    system("clear");
    int option;

    while (1) {
        int found = 0;  // Reset found at the beginning of each iteration
        printf("\nPlease enter the account number from which you want to make a transaction (or enter \"0\" to exit): ");
        scanf("%d", &r.accountNbr);

        if (r.accountNbr == 0) {
            printf("Thank you for visiting us!\n");
            fclose(pf);
            fclose(tempFile);
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
                    break;  // Exit this inner while loop and prompt for account number again
                }

                printf("\nIf you want to make a deposit, please enter \"0\".\n");
                printf("If you want to make a new withdrawal, please enter \"1\".\n");
                printf("Otherwise, enter \"2\" to exit.\n");
                int exitUpdate = 0;
                do {
                    printf("Enter your choice: ");
                    scanf("%d", &option);

                    switch (option) {
                        case 0:  // Deposit
                            printf("Enter the amount you want to deposit: ");
                            scanf("%lf", &r.amount);
                            cr.amount += r.amount;

                            printf("✔ Deposit successful! Your new total is $%.2f\n", cr.amount);
                            printf("\nIf you want to make a new deposit, please enter \"0\".\n");
                            printf("If you want to make a withdrawal, please enter \"1\".\n");
                            printf("Otherwise, enter \"2\" to exit.\n");
                            break;

                        case 1:  // Withdrawal
                            printf("Enter the amount you want to withdraw: ");
                            scanf("%lf", &r.amount);
                            while (r.amount > cr.amount) {
                                printf("\n✖ Not enough funds.\n");
                                printf("Your current total is $%.2f. Please enter a valid amount: ", cr.amount);
                                scanf("%lf", &r.amount);
                            }
                            cr.amount -= r.amount;

                            printf("✔ Withdrawal successful! Your new total is $%.2f\n", cr.amount);
                            printf("\nIf you want to make a deposit, please enter \"0\".\n");
                            printf("If you want to make a withdrawal, please enter \"1\".\n");
                            printf("Otherwise, enter \"2\" to exit.\n");
                            break;

                        case 2:  // Exit
                            printf("Thank you for visiting us!\n");
                            exitUpdate = 1;
                            break;

                        default:
                            printf("✖ Invalid choice. Please try again.\n");
                            break;
                    }

                } while (!exitUpdate);

                // Now, we need to write all records to tempFile, including the updated cr

                rewind(pf);  // Rewind original file pointer
                char tempUserName[50];
                struct Record temp_cr;
                while (getAccountFromFile(pf, tempUserName, &temp_cr)) {
                    struct User tempUser;
                    strcpy(tempUser.name, tempUserName);
                    tempUser.id = cr.userId;
                    //r.userId = cr.userId;
                    if (temp_cr.accountNbr == cr.accountNbr && strcmp(tempUserName, u.name) == 0) {
                        
                        saveAccountToFile(tempFile, tempUser, cr);
                    } else {
                        // Save other records unchanged
                        
                        saveAccountToFile(tempFile, tempUser, temp_cr);
                    }
                }

                fclose(pf);
                fclose(tempFile);

                remove(RECORDS);
                rename("temp.txt", RECORDS);

                printf("\n✔ Account updated successfully!\n");
                mainMenu(u);
            }
        }

        if (!found) {
            printf("\n✖ This account does not exist for this user. Please try again.\n");
        }
    }
}



unsigned long simpleHash(const char *str) {
    unsigned long hash = 0;
    while (*str) {
        hash = (hash << 5) + (*str++);  // Left shift hash by 5 and add the current character
    }
    return hash;
}

void accountRemoval(struct User u) {
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "r");
    if (pf == NULL) {
        perror("Error opening file");
        return;
    }

    system("clear");
    int found = 0;

    printf("\nPlease enter the account number you want to delete (or enter \"0\" to exit): ");
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

            printf("\nYou want to delete account number: %d.\n", r.accountNbr);
            printf("For safety reasons, please enter your password (or enter \"0\" to exit):");
            getPasswordInputDeletion(u.password);
            unsigned long hashedPassword = simpleHash(u.password);  // Hash entered password
            char *storedPassword = getPassword(u);  // Get stored password as a string
            unsigned long storedHash = strtoul(storedPassword, NULL, 10);

            if (strcmp(u.password, "0") == 0) {
                printf("\nThank you for visiting us!\n");
                fclose(pf);
                free(storedPassword);
                return;
            }

            while (hashedPassword != storedHash) {
                printf("\nWrong password. Please try again or enter \"0\" to exit: ");
                getPasswordInputDeletion(u.password);  // Capture new password
                hashedPassword = simpleHash(u.password);
                if (strcmp(u.password, "0") == 0) {
                    printf("\nThank you for visiting us!\n");
                    fclose(pf);
                    free(storedPassword);
                    return;
                }
            }

            if (cr.amount > 0) {
                printf("\nThere is a remaining amount of $%.2f. The amount will be returned to the user after the account is closed.\n", cr.amount);
                printf("Press Enter to continue");
                getchar();
                getchar();
            }

            // Skip writing this record to the new file
            FILE *tempFile = fopen("temp.txt", "w");
            if (tempFile == NULL) {
                perror("Error creating temporary file");
                fclose(pf);
                return;
            }

            rewind(pf);  // Rewind original file pointer
            char tempUserName[50];
            struct Record temp_cr;
            while (getAccountFromFile(pf, tempUserName, &temp_cr)) {
                if (temp_cr.accountNbr != r.accountNbr) {  // Skip the record to be deleted
                    struct User tempUser;
                    strcpy(tempUser.name, tempUserName);
                    saveAccountToFile(tempFile, tempUser, temp_cr);
                }
            }

            fclose(pf);
            fclose(tempFile);
            free(storedPassword);

            if (remove(RECORDS) != 0) {
                perror("Error deleting the records file");
                // Handle error if needed
            }

            if (rename("temp.txt", RECORDS) != 0) {
                perror("Error renaming the temporary file");
                // Handle error if needed
            }

            printf("\n✔ Account deleted successfully!\n");
            mainMenu(u);
            return;  // Ensure the function exits after deleting the account
        }
    }

    if (!found) {
        printf("\n✖ This account does not exist for this user. Please try again.\n");
    }

    fclose(pf);
}


void transferAccount(struct User u) {
    struct Record r;
    struct Record cr;
    struct User newOwner;
    char userName[50];
    FILE *pf = fopen(RECORDS, "r");
    if (pf == NULL) {
        perror("Error opening file");
        return;
    }

    system("clear");
    int found = 0;

    printf("\nPlease enter the account number you want to transfer or enter \"0\" to exit to the menu: ");
    scanf("%d", &r.accountNbr);

    if (r.accountNbr == 0) {
        printf("\nYou are now returning to the menu.\n");    
        fclose(pf);
        mainMenu(u);
    }

    rewind(pf);
    while (getAccountFromFile(pf, userName, &cr)) {
        if (cr.accountNbr == r.accountNbr && strcmp(userName, u.name) == 0) {
            found = 1;

            printf("\nYou want to transfer account number: %d.\n", r.accountNbr);
            printf("For safety reasons, please enter your password or enter \"0\" to exit to the menu: ");
            getPasswordInputDeletion(u.password);
            unsigned long hashedPassword = simpleHash(u.password);  // Hash entered password
            char *storedPassword = getPassword(u);  // Get stored password as a string
            unsigned long storedHash = strtoul(storedPassword, NULL, 10);

            if (strcmp(u.password, "0") == 0) {
                printf("\nYou are now returning to the menu.\n");
                getchar();
                fclose(pf);
                free(storedPassword);
                mainMenu(u);
            }

            while (hashedPassword != storedHash) {
                printf("\nWrong password. Please try again or enter \"0\" to exit to the menu: ");
                getPasswordInputDeletion(u.password);  // Capture new password
                hashedPassword = simpleHash(u.password);
                if (strcmp(u.password, "0") == 0) {
                    printf("\nYou are now returning to the menu.\n");
                    fclose(pf);
                    free(storedPassword);
                    mainMenu(u);
                }
            }

            free(storedPassword);
            int var = 0;
            while(var == 0){
                // Ask for the new owner's username
                printf("\nPlease enter the new owner's username or enter \"0\" to exit to the menu: ");
                scanf("%49s", newOwner.name);
                if (strcmp(newOwner.name, "0") == 0) {
                    printf("\nYou are now returning to the menu.\n");
                    fclose(pf);
                    mainMenu(u);
                }
                // Check if new owner exists
                FILE *userFile = fopen(USERS, "r");
                if (userFile == NULL) {
                    perror("Error opening users file");
                    fclose(pf);
                    return;
                }

                int userExists = 0;
                struct User userChecker;
                while (fscanf(userFile, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF) {
                    if (strcmp(newOwner.name, userChecker.name) == 0) {
                        userExists = 1;
                        newOwner.id = userChecker.id;
                        var = 1;
                        break;
                    }
                }
                
                fclose(userFile);

                if (!userExists) {
                    printf("\n✖ The specified user does not exist.\n");
                    //fclose(pf);
                    //return;
                }
            }

            // Update the record to transfer ownership
            cr.userId = newOwner.id;  // Update the userId in the account record
            
            // Open tempFile to write updated records
            FILE *tempFile = fopen("temp.txt", "w");
            if (tempFile == NULL) {
                perror("Error creating temporary file");
                fclose(pf);
                return;
            }

            rewind(pf);  // Rewind original file pointer
            char tempUserName[50];
            struct Record temp_cr;
            while (getAccountFromFile(pf, tempUserName, &temp_cr)) {
                struct User tempUser;
                strcpy(tempUser.name, tempUserName);
                tempUser.id = temp_cr.userId;  // Assign userId from the record

                if (temp_cr.accountNbr == cr.accountNbr) {
                    // Save the updated record with the new owner's information
                    temp_cr.userId = newOwner.id;
                    saveAccountToFile(tempFile, newOwner, temp_cr);
                } else {
                    // Save other records unchanged
                    saveAccountToFile(tempFile, tempUser, temp_cr);
                }
            }

            fclose(pf);
            fclose(tempFile);

            if (remove(RECORDS) != 0) {
                perror("Error deleting the records file");
                // Handle error if needed
            }

            if (rename("temp.txt", RECORDS) != 0) {
                perror("Error renaming the temporary file");
                // Handle error if needed
            }
            
            printf("\n✔ Account successfully transferred to %s!\n", newOwner.name);
            printf("Press enter to return to the main menu");
            getchar();
            getchar();       
            mainMenu(u);
            return;  // Ensure we exit the function after transfer
        }
    }

    if (!found) {
        printf("\n✖ This account does not exist for this user. Please try again.\n");
    }
    fclose(pf);
}


