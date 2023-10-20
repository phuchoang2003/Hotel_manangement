﻿#include <iostream>
#include "Hotel.h"
#include "Booking.h"
#include "main_functions.h"
#include "UsersManagement.h"
#include <thread>

void handleHotelOperations(UserManager& userManager){
    Hotel hotel;
    hotel.loadHotelData("hotel_data.txt");

     char choice;
     do {
            clearScreen();
            std::cout << "1. Book a room\n";
            std::cout << "2. Show all rooms\n";
            std::cout << "3. Search for available room \n";
            std::cout << "4. Deposit money\n";
            std::cout << "5. Withdraw money\n";
            std::cout << "0. Logout\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
            case '1': {
                clearScreen();
                Booking booking = hotel.gatherAndBookRoom();
                bool success = hotel.finalizeBookingAndPayment(booking, &userManager);
                if (!success) {
                    std::cout << "Booking cancelled as payment was not processed." << std::endl;
                }
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
            case '4': {
                double amount;
                std::cout << "Enter amount to deposit: ";
                std::cin >> amount;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Xóa bộ đệm
                userManager.depositToLoggedInUser(amount);
                std::cin.ignore();
                std::cin.get();
                break;
            }
            case '5': {
                double amount;
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
                userManager.withdrawFromLoggedInUser(amount);
                std::cin.ignore();
                std::cin.get();
                break;
            }
            
            case '0':
                hotel.saveHotelData("hotel_data.txt");
                userManager.logout();  
                clearScreen();
                std::cout << "Logged out successfully! Returning to main menu...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));  
                return;
            default:
                clearScreen();
                std::cout << "Invalid choice! Try again.\n";
                std::cin.ignore();
                std::cin.get();  
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
        std::cout << "3. Exit program\n";  
        std::cout << "Enter your choice: ";
        std::cin >> userChoice;
        std::cin.ignore();

        switch (userChoice) {
        case '1':
            if (userManager.loginCustomer()) {
                handleHotelOperations(userManager);
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
