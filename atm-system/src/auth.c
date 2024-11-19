#include <termios.h>
#include "header.h"



void getUsername(char a[50]) {
    system("clear");
    printf("\n\n\n\t\t\t\t Bank Management System\n\t\t\t\t User Login: ");
    scanf("%49s", a);
}

void getPasswordInput(char pass[50]) {
    struct termios oflags, nflags;

    // Disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }
    printf("\t\t\t\t Enter the password to login: ");
    scanf("%49s", pass);

    // Restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }
}



char *getPassword(struct User u) {
    FILE *fp;
    struct User userChecker;
    int id;

    if ((fp = fopen(USERS, "r")) == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    while (fscanf(fp, "%d %49s %49s", &id, userChecker.name, userChecker.password) != EOF) {
        // Debugging output
        // printf("Read from file - ID: %d, Username: '%s', Password: '%s'\n", id, userChecker.name, userChecker.password);

        if (strcmp(userChecker.name, u.name) == 0) {
            fclose(fp);
            return strdup(userChecker.password);
        }
    }

    fclose(fp);
    return NULL;  // User not found
}