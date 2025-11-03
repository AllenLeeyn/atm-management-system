#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char accTyp[10];
    int accNum;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char pw[50];
};

// authentication functions
void loginMenu(char name[50], char pw[50]);
void registerMenu(char name[50], char pw[50]);
const char *getPassword(struct User *u);
const char *getUserName(struct User *u);
void saveUserToFile(struct User *u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
