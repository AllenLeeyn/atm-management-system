#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const char *USERS;
extern const char *RECORDS;

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
    char accTyp[8];
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

FILE *openFileOrExit(const char *filename, const char *mode);

// authentication functions
void loginMenu(char *name, char *pw);
void registerMenu(char *name, char *pw);
const char *getPassword(struct User *u);
const char *getUserName(struct User *u);
void saveUserToFile(struct User *u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void checkAccount(struct User u);

// input validation function
int inputInt(const char *prompt, int min, int max);
double inputDouble(const char *prompt, double min, double max);
struct Date inputDate(const char *prompt);
void inputString(const char *prompt, char *dest, int maxLen);
void inputAccType(const char *prompt, char *accType);
//int inputYesNo(const char *prompt);