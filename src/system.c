#include "header.h"
#include <math.h> 

void stayOrReturn(char *msg, int notGood, void f(struct User u), struct User u) {
    int option;

    if (notGood == 0) {
        printf("%s", msg);
        option = inputInt("\nEnter 1 to try again, 2 to return to main menu, 0 to exit: ", 0, 2);
        switch (option) {
            case 1: 
                f(u); 
                break;
            case 2: 
                mainMenu(u); 
                break;
            case 0: 
                exit(0);
        }

    } else {
        option = inputInt("\nEnter 1 to go to the main menu and 0 to exit: ", 1, 2);
        switch (option) {
            case 1:
                mainMenu(u);
                break;

            case 0:
                exit(0);
        }
    }
}

void success(struct User u) {
    int option; 
    printf("\n✔ Success!\n\n");

    option = inputInt("Enter 1 to go to the main menu and 0 to exit!\n", 0, 1);
    system("clear");
    switch (option) {
        case 1:
            mainMenu(u);
            break;

        case 0:
            exit(0);
    }
}

const char *validAccTypes[] = {
    "savings",
    "current",
    "fixed01",
    "fixed02",
    "fixed03"
};

void createNewAcc(struct User u) {
    struct Record r;
    char msg[128] = "";

    system("clear");
    printf("\t\t\t===== New record =====\n");

    r.deposit = inputDate("\nEnter today's date (mm/dd/yyyy): ");
    r.accNum = inputInt("\nEnter the account number: ", 0, 99999999);

    struct Record existing;
    int canProceed = !findAccount(u, r.accNum, &existing);
    if (!canProceed) {
        sprintf(msg, "\n✖ [%s:%d] already exists.\n", u.name, r.accNum);

    } else {
        inputString("\nEnter the country: ", r.country, sizeof(r.country));
        r.phone = inputInt("\nEnter the phone number: ", 1000000, 999999999);
        r.amount = inputDouble("\nEnter amount to deposit: $", 0.01, 1000000.0);
        int accType = displayMenu("Choose the type of account:", validAccTypes, 5) -1;
        strcpy(r.accTyp, validAccTypes[accType]);

        FILE *fp = openFileOrExit(RECORDS, "a+");
        saveAccountToFile(fp, &u, &r);
        fclose(fp);
    }

    stayOrReturn(msg, canProceed, createNewAcc, u);
}

void printAccountDeatil(struct Record r) {
    printf("_____________________\n");
    printf("\nAccount number: \t%d\nDeposit Date: \t\t%d/%d/%d \ncountry: \t\t%s \nPhone number: \t\t%d \nAmount deposited: \t$%.2f \nType Of Account: \t%s\n",
            r.accNum,
            r.deposit.day,
            r.deposit.month,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accTyp);
}

void checkAllAccounts(struct User u) {
    FILE *fp = openFileOrExit(RECORDS, "r");
    char userName[50];
    struct Record r;
    int found = 0;

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(fp, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            found = 1;
            printAccountDeatil(r);
        }
    }
    fclose(fp);
    stayOrReturn("\n✖ Records not found!!\n", found, checkAllAccounts, u);
}

void printAccountInterest(struct Record r) {
    char msg[200];  // message to display
    double interest = r.amount * 0.07; // Default savings

    if (strcmp(r.accTyp, "current") == 0) {
        printf("%s\n", "You will not get interests because the account is of type current");
        return;
    }
    
    if (strcmp(r.accTyp, "savings") == 0) {
        double monthlyInterest = ceil((r.amount * 0.07 / 12.0) * 100.0) / 100.0;
        snprintf(msg, sizeof(msg),
                 "You will get $%.2f as interest on day %d of every month.",
                 monthlyInterest, r.deposit.day);
        printf("%s\n", msg);
        return;
    }

    int termYears = 1;
    double rate = 0.04;

    if (strcmp(r.accTyp, "fixed02") == 0) {
        rate = 0.05;
        termYears = 2;
    }
    else if (strcmp(r.accTyp, "fixed03") == 0) {
        rate = 0.08;
        termYears = 3;
    }
    double monthlyInterest = ceil((interest / 12.0) * 100.0) / 100.0;

    interest = ceil((r.amount * rate) * 100.0) / 100.0;
    int maturityYear = r.deposit.year + termYears;

    snprintf(msg, sizeof(msg),
             "You will get $%.2f as interest on %02d/%02d/%04d.",
             interest, r.deposit.month, r.deposit.day, maturityYear);
    printf("%s\n", msg);
}

void checkAccount(struct User u) {
    struct Record r;
    int accNum;
    int found = 0;
    
    system("clear");
    accNum = inputInt("\n\t\tEnter account number: ", 0, 99999999);

    found = findAccount(u, accNum, &r);
    if (found) {
        printf("\t\t====== Account[%d] from user, %s =====\n\n", accNum, u.name);
        printAccountDeatil(r);
        printAccountInterest(r);
    }

    stayOrReturn("\n✖ Record not found!!\n", found, checkAccount, u);
}

void updateAccount(struct User u) {
    struct Record r;
    int accNum;
    int found = 0;

    system("clear");
    accNum = inputInt("\n\t\tEnter account number: ", 0, 99999999);

    found = findAccount(u, accNum, &r);
    if (found) {
        printf("\t\t====== Account[%d] from user, %s =====\n\n", accNum, u.name);
        printAccountDeatil(r);
        printAccountInterest(r);

        int choice = displayMenu(
            "Which field do you want to update?",
            (const char*[]){"Country", "Phone Number"}, 
            2
        );

        if (choice == 1) {  // Country
            inputString("\nEnter new country: ", r.country, sizeof(r.country));
        } else if (choice == 2) {  // Phone
            r.phone = inputInt("\nEnter new phone number: ", 1000000, 999999999);
        }

        if (UpdateAccountToFile(RECORDS, &u, &r)) {
            printf("\n✔ Account updated successfully!\n");
        } else {
            printf("\n✖ Failed to update account!\n");
        }
    }
    stayOrReturn("\n✖ Record not found!!\n", found, updateAccount, u);
}

void makeTransaction(struct User u) {
    struct Record r;
    int accNum;
    int found = 0;

    system("clear");
    accNum = inputInt("\n\t\tEnter account number: ", 0, 99999999);

    found = findAccount(u, accNum, &r);
    if (found) {
        printf("\t\t====== Account[%d] from user, %s =====\n\n", accNum, u.name);
        found = 1;
        printAccountDeatil(r);

        if (strcmp(r.accTyp, "fixed01") == 0 ||
            strcmp(r.accTyp, "fixed02") == 0 ||
            strcmp(r.accTyp, "fixed03") == 0) {
            printf("\n✖ Transactions not allowed on fixed deposit accounts!\n");

        } else {
            int choice = displayMenu(
                "Select transaction type: ",
                (const char*[]){"Withdraw", "Deposite"}, 
                2
            );

            double max = 1000000.0;
            if (choice == 1) max = r.amount;
            double amount = inputDouble("\nEnter amount: $", 0.01, max);

            if (choice == 1) {  // Withdraw
                r.amount -= amount;
            } else {  // Deposit
                r.amount += amount;
            }

            if (UpdateAccountToFile(RECORDS, &u, &r)) {
                printf("\n✔ Account updated successfully!\n");
            } else {
                printf("\n✖ Failed to update account!\n");
            }
        }
    }
    stayOrReturn("\n✖ Record not found!!\n", found, makeTransaction, u);
}
