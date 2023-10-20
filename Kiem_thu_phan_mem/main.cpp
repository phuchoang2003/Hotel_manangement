#include <iostream>
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
                std::string customer_name = promptForName();
                std::string customer_email = promptForValidGmail();
                std::string customer_phone = promptForPhoneNumber();

                std::string check_in_date, check_out_date;
                promptForValidDates(check_in_date, check_out_date);

                Customer customer(customer_name, customer_email, customer_phone);

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
                            hotel.bookRoomById(roomId);  // Đặt phòng nhưng chưa lưu vào file
                            Booking booking(customer, desiredRoom, check_in_date, check_out_date);

                            // Tích hợp thanh toán vào đoạn này
                            bool paymentSuccess = hotel.finalizePayment(roomId, check_in_date, check_out_date, &userManager, customer);
                            if (paymentSuccess) {
                                booking.saveToFile();  // Lưu thông tin đặt phòng sau khi thanh toán thành công
                                hotel.saveHotelData("hotel_data.txt");  // Lưu trạng thái của phòng sau khi thanh toán thành công
                            }
                            break;
                        }
                        else {
                            std::cout << "The room ID does not match the selected room type. Please try again." << std::endl;
                        }
                    }
                    else {
                        std::cout << "Sorry, the selected room is not available or invalid ID. Please try again." << std::endl;
                    }
                } while (!validRoomId);
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
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Xóa bộ đệm
                userManager.withdrawFromLoggedInUser(amount);
                std::cin.ignore();
                std::cin.get();
                break;
            }
            
            case '0':
                hotel.saveHotelData("hotel_data.txt");
                userManager.logout();  // Đảm bảo rằng bạn đã thêm phương thức này vào class UserManager như đã được đề cập ở trước.
                clearScreen();
                std::cout << "Logged out successfully! Returning to main menu...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));  // Pause for a short time before returning
                return;
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
