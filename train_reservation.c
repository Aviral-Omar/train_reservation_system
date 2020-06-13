//TODO Document properly
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
    char number[6];
} TICKET;

TRAIN trains[100];
TICKET tickets[32000];
int trainCount = 0;
int ticketCount = 0;
int nextPNR = 1;

void welcome();
void enquiry();
void booking();
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
    else if (choice == '2')
    {
        system("clear");
        booking();
    }
    system("clear");
    welcome();
}

void enquiry()
{
    char sr[30];
    printf("Enter Source: ");
    fgets(sr, 30, stdin);
    sr[strlen(sr) - 1] = '\0';
    if (strcmp(sr, "Delhi") == 0)
    {
        char dt[30];
        printf("Enter Destination: ");
        fgets(dt, 30, stdin);
        dt[strlen(dt) - 1] = '\0';
        for (int i = 0; i < trainCount; i++)
        {
            if (strcmp(dt, trains[i].destination) == 0)
            {
                printf("\n\nNumber of seats available: %hu", trains[i].seatsLeft);
                break;
            }
            else if (i == trainCount - 1)
            {
                printf("\n\nNo trains are available for given source and destination!");
            }
        }
    }
    else
    {
        printf("\n\nNo trains are available for given source and destination!");
    }
    printf("\n\nPress ENTER to continue...");
    while (fgetc(stdin) != '\n')
        ;
}

void booking()
{
    char name[50], sr[30];
    printf("Enter your Name: ");
    fgets(name, 50, stdin);
    name[strlen(name) - 1] = '\0';
    printf("\nEnter Source: ");
    fgets(sr, 50, stdin);
    sr[strlen(sr) - 1] = '\0';
    if (strcmp(sr, "Delhi") == 0)
    {
        char dt[30];
        printf("\nEnter Destination: ");
        fgets(dt, 50, stdin);
        dt[strlen(dt) - 1] = '\0';
        for (int i = 0; i < trainCount; i++)
        {
            if (strcmp(dt, trains[i].destination) == 0)
            {
                trains[i].seatsLeft--;
                TICKET tc;
                tc.pnr = nextPNR;
                nextPNR++;
                strcpy(tc.name, name);
                strcpy(tc.number, trains[i].number);
                tickets[ticketCount] = tc;
                ticketCount++;
                printf("\nYou successfully booked a seat in train number %s.\n", tc.number);
                printf("Your PNR number is %lu.\n", tc.pnr);
                printf("You have been charged Rs.%u.", trains[i].cost);
                break;
            }
            else if (i == trainCount - 1)
            {
                printf("\n\nNo trains are available for given source and destination!");
            }
        }
    }
    else
    {
        printf("\n\nNo trains are available for given source and destination!");
    }
    printf("\n\nPress ENTER to continue...");
    while (fgetc(stdin) != '\n')
        ;
}

void loadData()
{
    FILE *trainPtr = fopen("trains.txt", "r");
    char c = fgetc(trainPtr);
    while (c != EOF)
    {
        TRAIN tr;
        for (int i = 0; i < 10; i++)
        {
            if (trainCount != 0)
            {
                c = fgetc(trainPtr);
            }
            if (c == ',')
            {
                tr.number[i] = '\0';
                break;
            }
            tr.number[i] = c;
            if (trainCount == 0)
            {
                c = fgetc(trainPtr);
            }
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
        c = fgetc(trainPtr);
    }
    fclose(trainPtr);
    FILE *ticketPtr = fopen("tickets.txt", "r");
    char d = fgetc(ticketPtr);
    while (d != EOF)
    {
        TICKET tc;
        for (int i = 0; i < 50; i++)
        {
            if (ticketCount != 0)
            {
                d = fgetc(ticketPtr);
            }
            if (d == ',')
            {
                tc.name[i] = '\0';
                break;
            }
            tc.name[i] = d;
            if (ticketCount == 0)
            {
                d = fgetc(ticketPtr);
            }
        }
        for (int i = 0; i < 10; i++)
        {
            d = fgetc(ticketPtr);
            if (d == ',')
            {
                tc.number[i] = '\0';
                break;
            }
            tc.number[i] = d;
        }
        fscanf(ticketPtr, "%lu", &tc.pnr);
        tickets[ticketCount] = tc;
        ticketCount++;
        d = fgetc(ticketPtr);
    }
    if (ticketCount != 0)
    {
        nextPNR = tickets[ticketCount - 1].pnr + 1;
    }
    fclose(ticketPtr);
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
    FILE *ticketPtr = fopen("tickets.txt", "w");
    for (int i = 0; i < ticketCount; i++)
    {
        TICKET tc = tickets[i];
        fprintf(ticketPtr, "%s,%s,%lu", tc.name, tc.number, tc.pnr);
        if (i != ticketCount - 1)
        {
            fprintf(ticketPtr, "\n");
        }
    }
    fclose(ticketPtr);
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
    while (fgetc(stdin) != '\n')
        ;
}