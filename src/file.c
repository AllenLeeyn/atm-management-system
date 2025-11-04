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

FILE *openFileOrExit(const char *filename, const char *mode) {
    FILE *fp = fopen(filename, mode);
    if (!fp) {
        printf("Error! Could not open file: %s\n", filename);
        exit(1);
    }
    return fp;
}

int findAccount(struct User u, int accNum, struct Record *result) {
    FILE *fp = openFileOrExit(RECORDS, "r");
    char userName[50];
    int found = 0;

    while (getAccountFromFile(fp, userName, result)) {
        if (strcmp(userName, u.name) == 0 && accNum == result->accNum) {
            found = 1;
            break;
        }
    }

    fclose(fp);
    return found;
}

int overwriteFileLine(const char *filename, int entryNum, const char *newContent) {
    FILE *src = openFileOrExit(filename, "r");
    FILE *tmp = openFileOrExit("temp.txt", "w");

    char buffer[1024];
    int success = 0;

    while (fgets(buffer, sizeof(buffer), src)) {
        int curEntry = 0;
        sscanf(buffer, "%d", &curEntry);
        if (curEntry == entryNum) {
            fprintf(tmp, "%s\n", newContent);
            success = 1;
        } else {
            fputs(buffer, tmp);
        }
    }

    fclose(src);
    fclose(tmp);

    remove(filename);
    rename("temp.txt", filename);

    return success;
}

void recordToString(struct Record *r, struct User *u, char *buffer, size_t bufSize) {
    snprintf(buffer, bufSize, "%d %d %s %d %d/%d/%d %s %d %.2lf %s",
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

int UpdateAccountToFile(const char *filename, struct User *u, struct Record *r) {
    char recordLine[512];
    recordToString(r, u, recordLine, sizeof(recordLine));

    // overwrite the line with the given id
    return overwriteFileLine(filename, r->id, recordLine);
}