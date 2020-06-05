#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct admin
{
    char id[50];
    char password[50];
};

struct admin admins[3] = {{"2019B4PS0733P", "2019B4PS0733P"}, {"2019B3PS0411P", "2019B3PS0411P"}, {"2019B2PS0966P", "2019B2PS0966P"}};

void addMember();
int welcomePage();
void loadData();

int main()
{
    system("clear");
    while(welcomePage())
    system("clear");
    return 0;
}

int welcomePage()
{
    char id[50], pass[50];
    printf("\t\tWelcome to The Escape Library\n");
    printf("\nEnter User ID: ");
    fgets(id, 49, stdin);
    id[strlen(id) - 1] = '\0';
    for (int i = 0; i < 3; i++)
    {
        if (!(strcmp(admins[i].id, id)))
        {
            printf("Enter Password: ");
            fgets(pass, 49, stdin);
            pass[strlen(pass) - 1] = '\0';
            if (!(strcmp(admins[i].password, pass)))
            {
                return 0;
            }
        }
    }
    return 1;
}

void addMember()
{
    char buf[50];
    FILE *fa = fopen("users.txt", "a");
    printf("Enter Username: ");
    fgets(buf, 49, stdin);
    buf[strlen(buf) - 1] = '\0';
    fputs(buf, fa);
    fputs(",", fa);
    printf("Enter Password: ");
    fgets(buf, 49, stdin);
    buf[strlen(buf) - 1] = '\0';
    fputs(buf, fa);
    fputs("\n", fa);
    fclose(fa);
}
