#include "header.h"

const char *USERS = "./data/users.txt";
const char *RECORDS = "./data/records.txt";

void mainMenu(struct User u) {
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

    option = inputInt("\n\t\tSelect option: ", 1, 8);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        // student TODO : add your **Update account information** function
        // here
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

int initMenu(struct User *u) {
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
        
        option = inputInt("\n\t\tSelect option: ", 1, 3);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->pw);
            if (strcmp(u->pw, getPassword(u)) == 0)
            {
                printf("\n\nPassword Match!");
            }
            else
            {
                printf("\nWrong password!! or User Name\n");
                exit(1);
            }
            r = 1;
            break;
        case 2:
            registerMenu(u->name, u->pw);
            if (strcmp(u->name, getUserName(u)) == 0)
            {
                printf("\nUser exists! Try a different Name.");
                exit(1);
            }
            else
            {
                saveUserToFile(u);
            }
            r = 1;
            break;

            exit(1);
        case 3:
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
        }
    }
    return 1;
};

int main() {
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
