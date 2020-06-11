#include <stdio.h>
#include <stdlib.h>

typedef struct train
{
    unsigned int number;
    char source[20];
    char destination[20];
    int cost;
    unsigned short int seatsLeft;
} TRAIN;

typedef struct ticket
{
    unsigned long int pnr;
    char name[50];
    unsigned int number;
} TICKET;

TRAIN trains[100];
//TODO change later
TICKET tickets[10000];
int trainCount = 0;
int ticketCount = 0;

void welcome();
void loadData();
void showTrains();

int main()
{
    // system("clear");
    printf("Start Loading");
    loadData();
    welcome();
    // system("clear");
    return 0;
}

void loadData()
{
    FILE *trainPtr = fopen("trains.txt", "r");
    char c;
    while (!feof(trainPtr))
    {
        TRAIN tr;
        fscanf(trainPtr, "%u", &tr.number);
        printf("%u", tr.number);
        fgetc(trainPtr);
        if (feof(trainPtr))
        {
            break;
        }
        for (int i = 0; i < 19; i++)
        {
            c = fgetc(trainPtr);
            if (c == ',')
            {
                tr.source[i] = '\0';
                break;
            }
            tr.source[i] = c;
        }
        for (int i = 0; i < 19; i++)
        {
            c = fgetc(trainPtr);
            if (c == ',')
            {
                tr.destination[i] = '\0';
                break;
            }
            tr.destination[i] = c;
        }
        fscanf(trainPtr, "%d", &tr.cost);
        fgetc(trainPtr);
        fscanf(trainPtr, "%hu", &tr.seatsLeft);
        trains[trainCount] = tr;
        trainCount++;
        while (fgetc(trainPtr) != '\n')
            ;
    }
    //TODO Load ticket data
    fclose(trainPtr);
}

void showTrains()
{
    printf("\nAvailable Trains:\n\n");
    printf("\t%-12s%-8s%-20s%-12s\n", "Train No.", "Source", "Destination", "Seats Left");
    for (int i = 0; i < trainCount; i++)
    {
        TRAIN tr = trains[i];
        printf("%d.\t%05u%*s%-8s%-20s%-12hu\n", i+1, tr.number, 7, "", tr.source, tr.destination, tr.seatsLeft);
    }
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
        showTrains();
    }
}