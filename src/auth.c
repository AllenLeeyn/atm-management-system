#include <termios.h>
#include "header.h"

void loginMenu(char *name, char *pw) {
    struct termios oflags, nflags;

    system("clear");
    inputString("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:", name, 50);

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
    inputString("\n\n\n\n\n\t\t\t\tEnter the password to login:", pw, 50);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

const char *getPassword(struct User *u) {
    FILE *fp = openFileOrExit(USERS, "r");
    struct User userX;

    while (fscanf(fp, "%d %s %s", &userX.id, userX.name, userX.pw) != EOF)
    {
        if (strcmp(userX.name, u->name) == 0)
        {
            fclose(fp);
            u->id = userX.id;
            char *buff = userX.pw;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}