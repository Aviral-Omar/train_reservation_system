#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct train
{
    char number[6];
    char source[30];
    char destination[30];
    unsigned int cost;
    unsigned short int seatsLeft;
} TRAIN;

typedef struct ticket
{
    unsigned long int pnr;
    char name[50];
    unsigned int number;
    unsigned int cost;
} TICKET;

TRAIN trains[100];
//TODO change later
TICKET tickets[100];
int trainCount = 0;
int ticketCount = 0;

void welcome();
void enquiry();
void loadData();
void saveData();
void showTrains();

int main()
{
    system("clear");
    loadData();
    welcome();
    saveData();
    system("clear");
    return 0;
}

void welcome()
{
    char choice;
    printf("\tWelcome to Shramik Sahyog Kendra\n\n");
    printf("\tHow can we help you today?\n\n");
    printf("1. Enquiry\n");
    printf("2. Booking\n");
    printf("3. Cancellation\n");
    printf("0. Exit\n\n");
    printf("Choose your desired operation: ");
    choice = fgetc(stdin);
    //this clears the input buffer
    while (fgetc(stdin) != '\n')
        ;
    if (choice == '0')
    {
        return;
    }
    else if (choice == '1')
    {
        system("clear");
        enquiry();
    }
    system("clear");
    welcome();
}

void enquiry()
{
    char sr[30];
    printf("Enter Source: ");
    fgets(sr, 28, stdin);
    sr[strlen(sr) - 1] = '\0';
    if (strcmp(sr, "Delhi") == 0)
    {
        char dt[30];
        printf("Enter Destination: ");
        fgets(dt, 28, stdin);
        dt[strlen(dt) - 1] = '\0';
        for (int i = 0; i < trainCount; i++)
        {
            if (strcmp(dt, trains[i].destination) == 0)
            {
                printf("\n\nNumber of seats available: %hu\n\n", trains[i].seatsLeft);
                printf("Press ENTER to continue...");
                while (fgetc(stdin) != '\n')
                    ;
                return;
            }
        }
    }
    printf("\n\nNo trains are available for given source and destination!\n\n");
    printf("Press ENTER to continue...");
    while (fgetc(stdin) != '\n')
        ;
}

void saveData()
{
    FILE *trainPtr = fopen("trains.txt", "w");
    for (int i = 0; i < trainCount; i++)
    {
        TRAIN tr = trains[i];
        fprintf(trainPtr, "%s,%s,%s,%u,%hu", tr.number, tr.source, tr.destination, tr.cost, tr.seatsLeft);
        if (i != trainCount - 1)
        {
            fprintf(trainPtr, "\n");
        }
    }
    fclose(trainPtr);
    //TODO save ticket data
}

void loadData()
{
    FILE *trainPtr = fopen("trains.txt", "r");
    char c;
    while (!feof(trainPtr))
    {
        TRAIN tr;
        char temp[3];
        for (int i = 0; i < 10; i++)
        {
            c = fgetc(trainPtr);
            if (c == EOF)
            {
                fclose(trainPtr);
                return;
            }
            if (c == ',')
            {
                tr.number[i] = '\0';
                break;
            }
            tr.number[i] = c;
        }
        for (int i = 0; i < 29; i++)
        {
            c = fgetc(trainPtr);
            if (c == ',')
            {
                tr.source[i] = '\0';
                break;
            }
            tr.source[i] = c;
        }
        for (int i = 0; i < 29; i++)
        {
            c = fgetc(trainPtr);
            if (c == ',')
            {
                tr.destination[i] = '\0';
                break;
            }
            tr.destination[i] = c;
        }
        fscanf(trainPtr, "%u", &tr.cost);
        fgetc(trainPtr);
        fscanf(trainPtr, "%hu", &tr.seatsLeft);
        trains[trainCount] = tr;
        trainCount++;
        fgets(temp, 3, trainPtr);
    }
    //TODO Load ticket data
    fclose(trainPtr);
}

//Not to be used in program
void showTrains()
{
    printf("\nAvailable Trains:\n\n");
    printf("\t%-12s%-8s%-20s%-12s\n", "Train No.", "Source", "Destination", "Seats Left");
    for (int i = 0; i < trainCount; i++)
    {
        TRAIN tr = trains[i];
        printf("%d.\t%5s%*s%-8s%-20s%-12hu\n", i + 1, tr.number, 7, "", tr.source, tr.destination, tr.seatsLeft);
    }
}