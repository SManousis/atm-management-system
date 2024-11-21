#ifndef HEADER_H    // Start of include guard. we are using include guards to prevent multiple inclusions of header everytime is used in a ddifferent c file
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void getPasswordInput(char pass[50]);
void getPasswordInputDeletion(char pass[50]);
void getUsername(char a[50]);
void registerMenu(struct User *u);
char *getPassword(struct User u);
unsigned long simpleHash(const char *str);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void updateAcc(struct User u);
void checkAccount(struct User u);
void accountTransaction(struct User u);
void accountRemoval(struct User u);
void transferAccount(struct User u);
void initMenu(struct User *u);
extern const char *USERS; 

#endif