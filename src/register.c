#include <termios.h>
#include "header.h"

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
    FILE *fp = openFileOrExit(USERS, "r");
    struct User userX;

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
    FILE *fp = openFileOrExit(USERS, "r");
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

void saveUserToFile(struct User *u)
{
    FILE *fp = openFileOrExit(USERS, "a+");
    int newId = getUserId();

    fprintf(fp, "%d %s %s\n",
        newId,
        u->name,
        u->pw);

    fclose(fp);
}