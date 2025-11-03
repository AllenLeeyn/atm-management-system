#include "header.h"

int getAccId()
{
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

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
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

void saveAccountToFile(FILE *ptr, struct User *u, struct Record *r)
{
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
    FILE *fp = openFileOrExit(RECORDS, "a+");
    struct Record r;
    struct Record cr;
    char userName[50];

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    r.deposit = inputDate("\nEnter today's date (mm/dd/yyyy): ");
    r.accNum = inputInt("\nEnter the account number: ", 1, 99999999);

    while (getAccountFromFile(fp, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accNum == r.accNum)
        {
            printf("✖ This Account already exists for this user\n\n");
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

void checkAllAccounts(struct User u)
{
    FILE *fp = openFileOrExit(RECORDS, "r");
    char userName[100];
    struct Record r;

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(fp, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accNum,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accTyp);
        }
    }
    fclose(fp);
    success(u);
}
