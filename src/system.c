#include "header.h"

int getAccId() {
    FILE *fp = openFileOrExit(RECORDS, "r");
    int count = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Check if this buffer contains a newline
        if (strchr(buffer, '\n') != NULL) {
            count++;
        }
    }

    fclose(fp);
    return count;
}

int getAccountFromFile(FILE *ptr, char *name, struct Record *r) {
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
        &r->id,
        &r->userId,
        name,
        &r->accNum,
        &r->deposit.month,
        &r->deposit.day,
        &r->deposit.year,
        r->country,
        &r->phone,
        &r->amount,
        r->accTyp) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User *u, struct Record *r) {
    r->id = getAccId();

    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
        r->id,
        u->id,
        u->name,
        r->accNum,
        r->deposit.month,
        r->deposit.day,
        r->deposit.year,
        r->country,
        r->phone,
        r->amount,
        r->accTyp);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u) {
    int option;

    if (notGood == 0) {
        system("clear");
        printf("\n✖ Record not found!!\n");

        while (1) {
            option = inputInt("\nEnter 0 to try again, 1 to return to main menu, 2 to exit: ", 0, 2);
            
            if (option == 0) f(u);
            else if (option == 1) mainMenu(u);
            else if (option == 2) exit(0);

            // If function returns, break the loop
            break;
        }
    } else {
        option = inputInt("\nEnter 1 to go to the main menu and 0 to exit: ", 0, 1);

        if (option == 1) {
            system("clear");
            mainMenu(u);
        } else {
            system("clear");
            exit(0);
        }
    }
}

void success(struct User u) {
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

void createNewAcc(struct User u) {
    FILE *fp = openFileOrExit(RECORDS, "a+");
    rewind(fp);
    struct Record r;
    struct Record cr;
    char userName[50];
    char msg[128] = "";

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");
    printf("%s", msg);

    r.deposit = inputDate("\nEnter today's date (mm/dd/yyyy): ");
    r.accNum = inputInt("\nEnter the account number: ", 0, 99999999);

    while (getAccountFromFile(fp, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accNum == r.accNum)
        {
            sprintf(msg, "\n✖ [%s:%d] already exists.\n", u.name, r.accNum);
            goto noAccount;
        }
    }
    inputString("\nEnter the country: ", r.country, sizeof(r.country));
    r.phone = inputInt("\nEnter the phone number: ", 1000000, 999999999);  // adjust limits
    r.amount = inputDouble("\nEnter amount to deposit: $", 0.01, 1000000.0);
    inputAccType("\nChoose the type of account:\n\t-> savings\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:", 
        r.accTyp);

    saveAccountToFile(fp, &u, &r);

    fclose(fp);
    success(u);
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
    stayOrReturn(found, checkAllAccounts, u);
}

void printAccountInterest(struct Record r) {
    if (strcmp(r.accTyp, "current") == 0) {
        printf("%s\n", "You will not get interests because the account is of type current");
        return;
    }
    
    char msg[200];  // message to display
    double interest = r.amount * 0.07; // Default savings

    if (strcmp(r.accTyp, "Fixed01") == 0) {  // 1-year fixed
        interest = r.amount * 0.04;
    }
    else if (strcmp(r.accTyp, "Fixed02") == 0) {  // 2-year fixed
        interest = r.amount * 0.05;
    }
    else if (strcmp(r.accTyp, "Fixed03") == 0) {  // 3-year fixed
        interest = r.amount * 0.08;
    }

    snprintf(msg, sizeof(msg), "You will get $%.2f as interest on day %d of every month",
                interest, r.deposit.day);
    printf("%s\n", msg);
}

void checkAccount(struct User u) {
    FILE *fp = openFileOrExit(RECORDS, "r");

    struct Record r;
    char userName[50];
    int accNum;
    int found = 0;
    accNum = inputInt("\nEnter account number: ", 0, 99999999);
    while (getAccountFromFile(fp, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && accNum == r.accNum)
        {
            found = 1;
            printAccountDeatil(r);
            printAccountInterest(r);
            break;
            
        }
    }
    fclose(fp);
    stayOrReturn(found, checkAccount, u);
}