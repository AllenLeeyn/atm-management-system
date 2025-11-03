#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void registerMenu(char name[50], char pw[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t     User Registration:");
    scanf("%s", name);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to register:");
    scanf("%s", pw);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

const char *getUserName(struct User *u)
{
    FILE *fp;
    struct User userX;

    if ((fp = fopen(USERS, "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &userX.id, userX.name, userX.pw) != EOF)
    {
        if (strcmp(userX.name, u->name) == 0)
        {
            fclose(fp);
            char *buff = userX.name;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}

int getUserId()
{
    FILE *fp;
    int count = 0;
    char buffer[256];

    if ((fp = fopen(USERS, "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Check if this buffer contains a newline
        if (strchr(buffer, '\n') != NULL) {
            count++;
        }
    }

    fclose(fp);
    return count;
}

void saveUserToFile(struct User *u)
{
    FILE *fp;
    if ((fp = fopen(USERS, "a+")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    int newId = getUserId();

    fprintf(fp, "%d %s %s\n",
        newId,
        u->name,
        u->pw);

    fclose(fp);
}