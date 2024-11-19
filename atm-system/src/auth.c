#include <termios.h>
#include "header.h"



void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%49s", a);

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
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        exit(1);
    }
};

    char *getPassword(struct User u) {
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen(USERS, "r")) == NULL) {
        printf("Error! Opening file\n");
        exit(1);
    }

    // Hash the input password for comparison
    unsigned long hashedInput = simpleHash(u.password);

    while (fscanf(fp, "%s %s", userChecker.name, userChecker.password) != EOF) {
        if (strcmp(userChecker.name, u.name) == 0) {
            fclose(fp);
            unsigned long hashedStoredPassword = simpleHash(userChecker.password);
            if (hashedInput == hashedStoredPassword){
                return "Password Match";
            } else {
                return "Password Mismatch";
            }
        }
    }

    fclose(fp);
    return "User Not Found";
}
