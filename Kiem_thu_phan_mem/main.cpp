#include <iostream>
#include "Hotel.h"
#include "Booking.h"
#include "main_functions.h"  



int main() {
    Hotel hotel;

    std::string customer_name = promptForName();
    std::string customer_email = promptForValidGmail();
    std::string customer_phone = promptForPhoneNumber(); 

    std::string check_in_date, check_out_date;
    promptForValidDates(check_in_date, check_out_date);

    Customer customer(customer_name, customer_email, customer_phone);



    hotel.showAllRooms();
    std::string room_type = promptForRoomType();

    if (hotel.bookRoom(room_type)) {
        Booking booking(customer, hotel.findAvailableRoom(room_type), check_in_date, check_out_date);
        booking.confirm();
    }
    else {
        std::cout << "Sorry, no available room of this type." << std::endl;
    }

    return 0;
}

