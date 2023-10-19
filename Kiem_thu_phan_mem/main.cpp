#include <iostream>
#include "Hotel.h"
#include "Booking.h"
#include "main_functions.h"
#include "UsersManagement.h"
#include "Notification.h"

void handleHotelOperations() {
    Hotel hotel;
    hotel.loadHotelData("hotel_data.txt");

     char choice;
     do {
            clearScreen();
            std::cout << "1. Book a room\n";
            std::cout << "2. Show all rooms\n";
            std::cout << "3. Search for available room \n";
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
                customer.saveToFile();

                //std::string room_type = promptForRoomType();



                std::string chosenRoomType = hotel.showAvailableRoomsOfType();
                int roomId;
                bool validRoomId = false;

                do {
                    std::cout << "Please enter the ID of the room you would like to book: ";
                    std::cin >> roomId;

                    // Xóa bộ đệm
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (hotel.isRoomAvailable(roomId)) {
                        const Room* desiredRoom = hotel.getRoomById(roomId);

                        if (desiredRoom->getType() == chosenRoomType) {
                            hotel.bookRoomById(roomId);
                            Booking booking(customer, desiredRoom, check_in_date, check_out_date);
                            booking.confirm();
                            booking.saveToFile();
                            hotel.saveHotelData("hotel_data.txt");
                            validRoomId = true;
                        }
                        else {
                            std::cout << "The room ID does not match the selected room type. Please try again." << std::endl;
                        }
                    }
                    else {
                        std::cout << "Sorry, the selected room is not available or invalid ID. Please try again." << std::endl;
                    }
                } while (!validRoomId);
                Notification::confirmBookingToCustomer(customer);
                break;
            }
            case '2':
                hotel.showAllRooms();
                std::cin.ignore();
                std::cin.get();  
                break;
            case '3':
                searchForAvailableRooms(hotel);
                break;
            /*case '3':
                if (authenticateEmployee()) {
                    hotel.searchCustomerByRoomIdFromFile();
                }
                else {
                    clearScreen();
                    std::cout << "Authentication failed. Access denied." << std::endl;
                    std::cin.ignore();
                    std::cin.get();
                }
                break;*/
            case '0':
                hotel.saveHotelData("hotel_data.txt");
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
}




int main() {
    UserManager userManager;
    char userChoice;

    do {
        clearScreen();
        std::cout << "1. Login\n";
        std::cout << "2. Register\n";
        std::cout << "3. Exit program\n";  // Rename to make it clear this exits the program
        std::cout << "Enter your choice: ";
        std::cin >> userChoice;
        std::cin.ignore();

        switch (userChoice) {
        case '1':
            if (userManager.loginCustomer()) {
                handleHotelOperations();
            }
            else {
                std::cout << "Login failed. Try again.\n";
                std::cin.ignore();
                std::cin.get();
            }
            break;

        case '2':
            userManager.registerCustomer();
            std::cout << "Registration successful!\n";
            std::cin.ignore();
            std::cin.get(); 
            break;

        case '3':
            return 0;

        default:
            std::cout << "Invalid choice! Try again.\n";
            break;
        }
    } while (true);

    return 0;
}
