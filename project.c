#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 40
#define MAX_BUSES 3

typedef struct {
    int busNumber;
    char passengerName[50];
    int seatNumber;
} Reservation;

void displayBuses();
void bookTicket();
void cancelTicket();
void viewReservations();
void saveToFile();
void loadFromFile();

Reservation reservations[MAX_SEATS];
int reservationCount = 0;

int main() {
    int choice;
    loadFromFile(); // Load previous reservations from file

    while (1) {
        printf("\n======= BUS RESERVATION SYSTEM =======\n");
        printf("1. View Available Buses\n");
        printf("2. Book a Ticket\n");
        printf("3. Cancel a Ticket\n");
        printf("4. View Reservations\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                displayBuses();
                break;
            case 2:
                bookTicket();
                break;
            case 3:
                cancelTicket();
                break;
            case 4:
                viewReservations();
                break;
            case 5:
                saveToFile();
                printf("Exiting... Data saved successfully.\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

// Function to display available buses
void displayBuses() {
    printf("\nAvailable Buses:\n");
    printf("1. Bus 101 - City A to City B\n");
    printf("2. Bus 102 - City C to City D\n");
    printf("3. Bus 103 - City E to City F\n");
}

// Function to book a ticket
void bookTicket() {
    if (reservationCount >= MAX_SEATS) {
        printf("Sorry, no more seats available!\n");
        return;
    }

    Reservation newRes;
    printf("Enter Bus Number (101-103): ");
    scanf("%d", &newRes.busNumber);
    
    if (newRes.busNumber < 101 || newRes.busNumber > 103) {
        printf("Invalid Bus Number!\n");
        return;
    }

    printf("Enter Passenger Name: ");
    scanf(" %[^\n]s", newRes.passengerName);
    
    printf("Enter Seat Number (1-%d): ", MAX_SEATS);
    scanf("%d", &newRes.seatNumber);

    if (newRes.seatNumber < 1 || newRes.seatNumber > MAX_SEATS) {
        printf("Invalid Seat Number!\n");
        return;
    }

    // Save reservation
    reservations[reservationCount++] = newRes;
    printf("Ticket booked successfully for %s on Bus %d, Seat %d!\n", newRes.passengerName, newRes.busNumber, newRes.seatNumber);
}

// Function to cancel a ticket
void cancelTicket() {
    int seat, bus, i, found = 0;
    printf("Enter Bus Number to cancel (101-103): ");
    scanf("%d", &bus);
    
    printf("Enter Seat Number to cancel: ");
    scanf("%d", &seat);

    for (i = 0; i < reservationCount; i++) {
        if (reservations[i].busNumber == bus && reservations[i].seatNumber == seat) {
            printf("Ticket for %s on Bus %d, Seat %d cancelled successfully!\n", reservations[i].passengerName, bus, seat);
            reservations[i] = reservations[--reservationCount]; // Shift last reservation to current index
            found = 1;
            break;
        }
    }
    
    if (!found)
        printf("No booking found for Bus %d, Seat %d!\n", bus, seat);
}

// Function to view all reservations
void viewReservations() {
    if (reservationCount == 0) {
        printf("No reservations found!\n");
        return;
    }

    printf("\nCurrent Reservations:\n");
    for (int i = 0; i < reservationCount; i++) {
        printf("Passenger: %s, Bus: %d, Seat: %d\n", reservations[i].passengerName, reservations[i].busNumber, reservations[i].seatNumber);
    }
}

// Function to save reservations to a text file
void saveToFile() {
    FILE *file = fopen("reservations.txt", "w");
    if (file == NULL) {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < reservationCount; i++) {
        fprintf(file, "%d,%s,%d\n", reservations[i].busNumber, reservations[i].passengerName, reservations[i].seatNumber);
    }

    fclose(file);
}

// Function to load reservations from a text file
void loadFromFile() {
    FILE *file = fopen("reservations.txt", "r");
    if (file == NULL) {
        return; // No previous data found
    }

    while (fscanf(file, "%d,%49[^,],%d\n", &reservations[reservationCount].busNumber, reservations[reservationCount].passengerName, &reservations[reservationCount].seatNumber) != EOF) {
        reservationCount++;
    }

    fclose(file);
}
