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

// The data stored in the files will be loaded in these
// arrays of structures for convenient access.
// Any changes like booking and cancellation will first
// be reflected in these arrays.
// Later, the data in the files will be overwritten.
// Assumption is made that every train has 1000 seats.
TRAIN trains[100];
TICKET tickets[32000];
// These variables are initialized when data is loaded.
int trainCount;
int ticketCount;
int nextPNR;

void welcome();
void enquiry();
void booking();
void cancel();
void loadData();
void saveData();

int main()
{
    // This command clears the terminal
    system("clear");
    // Loading data at the beginning
    loadData();
    welcome();
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
    // This clears the input buffer and discards all characters till end of line.
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
    else if (choice == '3')
    {
        system("clear");
        cancel();
    }
    system("clear");
    // By recursively calling welcome, the program does not end until the user explicitly selects Exit.
    welcome();
}

void enquiry()
{
    char sr[30];
    printf("Enter Source: ");
    fgets(sr, 30, stdin);
    // This discards the newline character which fgets also reads.
    sr[strlen(sr) - 1] = '\0';
    // Checks if user entered source is Delhi.
    if (strcmp(sr, "Delhi") == 0)
    {
        char dt[30];
        printf("Enter Destination: ");
        fgets(dt, 30, stdin);
        dt[strlen(dt) - 1] = '\0';
        for (int i = 0; i < trainCount; i++)
        {
            // Checks all trains to see if destination matches.
            if (strcmp(dt, trains[i].destination) == 0)
            {
                printf("\nTrain Number: %s \nCost: Rs.%u", trains[i].number, trains[i].cost);
                printf("\n\nNumber of seats available: %hu", trains[i].seatsLeft);
                break;
            }
            // Printed if no destination matches till the last iteration.
            else if (i == trainCount - 1)
            {
                printf("\n\nNo trains are available for given source and destination!");
            }
        }
    }
    else
    {
        printf("\n\nNo trains are available for given source!");
    }
    // This waits for the user to enter a newline character i.e. press ENTER.
    printf("\n\nPress ENTER to continue...");
    while (fgetc(stdin) != '\n')
        ;
}

void booking()
{
    char name[50], sr[30];
    // Assumes maximum length of name to be 49.
    printf("Enter your Name: ");
    fgets(name, 50, stdin);
    name[strlen(name) - 1] = '\0';
    printf("\nEnter Source: ");
    fgets(sr, 50, stdin);
    sr[strlen(sr) - 1] = '\0';
    // Checks if entered source is Delhi like enquiry system.
    if (strcmp(sr, "Delhi") == 0)
    {
        char dt[30];
        printf("\nEnter Destination: ");
        fgets(dt, 50, stdin);
        dt[strlen(dt) - 1] = '\0';
        for (int i = 0; i < trainCount; i++)
        {
            // Similar to enquiry system.
            if (!strcmp(dt, trains[i].destination))
            {
                // This checks if desired train has any seats available.
                if (trains[i].seatsLeft > 0)
                {
                    // Available seats decreased.
                    trains[i].seatsLeft--;
                    TICKET tc;
                    // PNR assigned and nextPNR increased by 1.
                    tc.pnr = nextPNR;
                    nextPNR++;
                    // Name and train number assigned.
                    strcpy(tc.name, name);
                    strcpy(tc.number, trains[i].number);
                    // Ticket stored in array.
                    tickets[ticketCount] = tc;
                    ticketCount++;
                    printf("\nYou successfully booked a seat in train number %s.", tc.number);
                    printf("\n\nYour PNR number is %lu.", tc.pnr);
                    printf("\n\nYou have been charged Rs.%u.", trains[i].cost);
                    printf("\n\nDue To Covid-19, You Are Required To Seriously Follow The Guidelines Listed Below:");
                    printf("\n\n1. It is Advisable to download Aarogya Setu App on your mobile phone, before commencing Rail Journey.");
                    printf("\n2. Every Passenger is requested to arrive atleast two hours before the scheduled departure for thermal screening and other procedures required to prevent Covid-19.");
                    printf("\n3. Use Face Mask, Maintain Social Distancing and Wash Hands Frequently.");
                    printf("\n4. No Blanket and linen shall be provided in the train.");
                    printf("\n5. If you wish to cancel your ticket, half of the ticket cost will be refunded.");
                    // This writes the data back into the files.
                    saveData();
                    break;
                }
                // Printed if no more seats left.
                else
                {
                    printf("\n\nNo seats are left in this train!");
                }
            }
            // Printed if no destination matches till the last iteration.
            else if (i == trainCount - 1)
            {
                printf("\n\nNo trains are available for given source and destination!");
            }
        }
    }
    else
    {
        printf("\n\nNo trains are available for given source!");
    }
    printf("\n\nPress ENTER to continue...");
    while (fgetc(stdin) != '\n')
        ;
}

void cancel()
{
    // Cancellation is done using PNR number as it is unique.
    long unsigned int pnr;
    printf("Enter PNR number of ticket to be cancelled: ");
    scanf("%lu", &pnr);
    while (fgetc(stdin) != '\n')
        ;
    // Iterates through all the tickets in the array.
    for (int i = 0; i < ticketCount; i++)
    {
        //Checks if PNR of current ticket matches.
        if (tickets[i].pnr == pnr)
        {
            // Finds the train for which the ticket has been booked using the train number.
            for (int j = 0; j < trainCount; j++)
            {
                // Checks if train number matches.
                if (!strcmp(trains[j].number, tickets[i].number))
                {
                    printf("\nDeatils of the booked ticket:\n");
                    printf("Train Number: %s\nCost: Rs.%u", trains[j].number, trains[j].cost);
                    printf("\n\nAre you sure about proceeding with cancellation?(Enter y/n): ");
                    char h = fgetc(stdin);
                    while ((getchar()) != '\n')
                        ;
                    if (h == 'y' || h == 'Y')
                    {
                        // Seats left in the train increased.
                        trains[j].seatsLeft++;
                        // To cancel the ticket, all further tickets in the array are shifted by 1.
                        // Ticket count is decreased which also ensures that last ticket is not read twice.
                        for (int k = i; k < ticketCount - 1; k++)
                        {
                            tickets[k] = tickets[k + 1];
                        }
                        ticketCount--;
                        printf("\nYour ticket has been cancelled!\n");
                        // Half the amount is refunded.
                        printf("You have been refunded Rs.%.2f.", ((float)trains[j].cost) / 2);
                        // The data is written to the files.
                        saveData();
                        // Data is also reloaded so that nextPNR can be determined.
                        loadData();
                        break;
                    }
                    else
                    {
                        printf("\nTicket has not been cancelled!");
                    }
                }
            }
            break;
        }
        // If PNR number entered does not match any ticket.
        else if (i == ticketCount - 1)
        {
            printf("\n\nNo ticket has entered PNR number!");
        }
    }
    printf("\n\nPress ENTER to continue...");
    while (fgetc(stdin) != '\n')
        ;
}

void loadData()
{
    trainCount = 0;
    ticketCount = 0;
    FILE *trainPtr = fopen("trains.txt", "r");
    // Gets first character which might be EOF in empty file
    char c = fgetc(trainPtr);
    while (c != EOF)
    {
        TRAIN tr;
        // This loop reads the train number on every line.
        for (int i = 0; i < 10; i++)
        {
            if (trainCount != 0)
            {
                c = fgetc(trainPtr);
            }
            // This closes the string when a comma is encountered.
            if (c == ',')
            {
                tr.number[i] = '\0';
                break;
            }
            tr.number[i] = c;
            // In the first iteration i.e. first line, c already contains the first character.
            // So we increment at the end of loop.
            if (trainCount == 0)
            {
                c = fgetc(trainPtr);
            }
        }
        // This loop reads the source on every line.
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
        // This loop reads the destination on every line.
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
        // This reads the cost of ticket.
        fscanf(trainPtr, "%u", &tr.cost);
        // This discards the comma.
        fgetc(trainPtr);
        // This reads the number of seats left.
        fscanf(trainPtr, "%hu", &tr.seatsLeft);
        // The structure which stored the read data is now stored in the array.
        trains[trainCount] = tr;
        trainCount++;
        // This reads the newline character or the EOF character.
        c = fgetc(trainPtr);
    }
    fclose(trainPtr);
    // Loading tickets works with a similar logic.
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
    // The PNR of the last ticket is the highest PNR by design.
    // This checks if no tickets have been booked yet.
    if (ticketCount != 0)
    {
        nextPNR = tickets[ticketCount - 1].pnr + 1;
    }
    else
    {
        nextPNR = 1;
    }
    fclose(ticketPtr);
}

void saveData()
{
    // Data is written in the trains.txt file in a specific format.
    // Every line represents a single train.
    // Format is train_number,source,destination,cost,seats_left
    FILE *trainPtr = fopen("trains.txt", "w");
    for (int i = 0; i < trainCount; i++)
    {
        TRAIN tr = trains[i];
        fprintf(trainPtr, "%s,%s,%s,%u,%hu", tr.number, tr.source, tr.destination, tr.cost, tr.seatsLeft);
        // All lines except the last one end with a newline character.
        if (i != trainCount - 1)
        {
            fprintf(trainPtr, "\n");
        }
    }
    fclose(trainPtr);
    // Data is written in the tickets.txt file in a specific format.
    // Every line represents a single ticket.
    // Format is name,train_number,pnr
    FILE *ticketPtr = fopen("tickets.txt", "w");
    for (int i = 0; i < ticketCount; i++)
    {
        TICKET tc = tickets[i];
        fprintf(ticketPtr, "%s,%s,%lu", tc.name, tc.number, tc.pnr);
        // All lines except the last one end with a newline character.
        if (i != ticketCount - 1)
        {
            fprintf(ticketPtr, "\n");
        }
    }
    fclose(ticketPtr);
}