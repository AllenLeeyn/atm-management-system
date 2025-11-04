#include "header.h"

const char *USERS = "./data/users.txt";
const char *RECORDS = "./data/records.txt";

void mainMenu(struct User u) {
    const char *mainMenuOptions[] = {
        "Create a new account",
        "Update account information",
        "Check accounts",
        "Check list of owned account",
        "Make Transaction",
        "Remove existing account",
        "Transfer ownership",
        "Exit"
    };
    system("clear");
    int option = displayMenu("ATM", mainMenuOptions, 8);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        updateAccount(u);
        break;
    case 3:
        checkAccount(u);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        makeTransaction(u);
        break;
    case 6:
        deleteAccount(u);
        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        // here
        break;
    case 8:
        exit(1);
        break;
    }
};

int initMenu(struct User *u) {
    const char *initMenuOptions[] = {
        "login",
        "register",
        "exit"
    };

    system("clear");
    int option = displayMenu("ATM", initMenuOptions, 3);
    switch (option)
    {
    case 1:
        loginMenu(u->name, u->pw);
        if (strcmp(u->pw, getPassword(u)) == 0) {
            printf("\n\nPassword Match!");
        } else {
            printf("\nWrong password!! or User Name\n");
            exit(1);
        }
        return 1;
    case 2:
        registerMenu(u->name, u->pw);
        if (strcmp(u->name, getUserName(u)) == 0) {
            printf("\nUser exists! Try a different Name.");
            exit(1);
        } else {
            saveUserToFile(u);
        }
        return 1;
    case 3:
        exit(1);
        break;
    }
    return 1;
};

int main() {
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
