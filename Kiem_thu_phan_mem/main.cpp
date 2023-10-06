#include <iostream>
#include "Hotel.h"
#include "Booking.h"
#include "main_functions.h"

int main() {
    Hotel hotel;
    char choice;

    do {
        clearScreen(); 
        std::cout << "=== Hotel Room Booking ===\n";
        std::cout << "1. Book a room\n";
        std::cout << "2. Show all rooms\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        

        switch (choice) {
        case '1': {
            clearScreen();
            std::string customer_name = promptForName();
            std::string customer_email = promptForValidGmail();
            std::string customer_phone = promptForPhoneNumber();

            std::string check_in_date, check_out_date;
            promptForValidDates(check_in_date, check_out_date);

            Customer customer(customer_name, customer_email, customer_phone);

            std::string room_type = promptForRoomType();
            hotel.showAvailableRoomsOfType(room_type);

            char proceed;
            std::cout << "Would you like to book one of these rooms? (Y/N): ";
            std::cin >> proceed;
            if (proceed == 'Y' || proceed == 'y') {
                if (hotel.bookRoom(room_type)) {
                    Booking booking(customer, hotel.findAvailableRoom(room_type), check_in_date, check_out_date);
                    booking.confirm();
                }
                else {
                    std::cout << "Sorry, no available room of this type." << std::endl;
                }
            }
            break;
        }
        case '2':
            hotel.showAllRooms();
            std::cin.ignore();
            std::cin.get();  // Pause for user to read the list
            break;
        case '0':
            clearScreen();
            std::cout << "Thank you for using our system! Goodbye!\n";
            break;
        default:
            clearScreen();
            std::cout << "Invalid choice! Try again.\n";
            std::cin.ignore();
            std::cin.get();  // Pause for user to read the message
            break;
        }
    } while (choice != '0');

    return 0;
}
