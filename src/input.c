#include "header.h"

// Parser function type
typedef int (*ParserFunc)(const char *input, void *out);

// generic input helper function. Prompt loop that calls parser function for validation
int inputGeneric(const char *prompt, void *out, ParserFunc parser) {
    char buffer[128];

    while (1) {
        printf("%s", prompt);

        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("✖ Input error. Please try again.\n");
            continue;
        }

        // Remove newline
        buffer[strcspn(buffer, "\n")] = 0;

        if (parser(buffer, out)) {
            return 1;
        } else {
            printf("✖ Invalid input. Please try again.\n");
        }
    }
}

// ccheck if isValidDate()
int isValidDate(const struct Date *d) {
    if (d->year < 1900 || d->year > 2100) return 0;
    if (d->month < 1 || d->month > 12) return 0;

    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    // leap year adjustment
    if ((d->year % 4 == 0 && d->year % 100 != 0) || (d->year % 400 == 0))
        daysInMonth[1] = 29;

    if (d->day < 1 || d->day > daysInMonth[d->month - 1]) return 0;
    return 1;
}

/*<--------------------- parse functions -------------------->*/
// parser function for int
int parseInt(const char *input, void *out) {
    int value;
    char extra;

    // %d %c trick: ensures no extra chars
    if (sscanf(input, "%d %c", &value, &extra) == 1) {
        *(int *)out = value;
        return 1;
    }
    return 0;
}

// parser function for double
int parseDouble(const char *input, void *out) {
    double value;
    char extra;

    if (sscanf(input, "%lf %c", &value, &extra) == 1) {
        *(double *)out = value;
        return 1;
    }
    return 0;
}

// parser function for Date
int parseDate(const char *input, void *out) {
    struct Date d;
    char extra;

    if (sscanf(input, "%d/%d/%d %c", &d.month, &d.day, &d.year, &extra) != 3)
        return 0;

    if (!isValidDate(&d))
        return 0;

    *(struct Date *)out = d;
    return 1;
}

const char *validAccTypes[] = {
    "savings",
    "current",
    "fixed01",
    "fixed02",
    "fixed03"
};
const int nAccTypes = sizeof(validAccTypes) / sizeof(validAccTypes[0]);

int parseAccType(const char *input, void *out) {
    char buffer[9];
    // remove newline
    if (sscanf(input, "%8s", buffer) != 1)
        return 0;

    if (strlen(buffer) != 7)
        return 0;

    for (int i = 0; i < nAccTypes; i++) {
        if (strcmp(buffer, validAccTypes[i]) == 0) {
            strcpy((char *)out, buffer);
            return 1;
        }
    }

    return 0;
}

/*<--------------------- iput<type> functions -------------------->*/
int inputInt(const char *prompt, int min, int max) {
    int value;
    while (inputGeneric(prompt, &value, parseInt)) {
        if (value < min || value > max) {
            printf("✖ Input must be between %d and %d.\n", min, max);
        } else {
            return value;
        }
    }
    return 0;
}

double inputDouble(const char *prompt, double min, double max) {
    double value;
    while (inputGeneric(prompt, &value, parseDouble)) {
        if (value < min || value > max) {
            printf("✖ Input must be between %g and %g.\n", min, max);
        } else {
            return value;
        }
    }
    return 0.0;
}

struct Date inputDate(const char *prompt) {
    struct Date d;
    inputGeneric(prompt, &d, parseDate);
    return d;
}

void inputString(const char *prompt, char *dest, int maxLen) {
    printf("%s", prompt);
    if (fgets(dest, maxLen, stdin)) {
        // remove trailing newline if present
        size_t len = strlen(dest);
        if (len > 0 && dest[len-1] == '\n') {
            dest[len-1] = '\0';
        }
    }
}

void inputAccType(const char *prompt, char *accType) {
    inputGeneric(prompt, accType, parseAccType);
}
