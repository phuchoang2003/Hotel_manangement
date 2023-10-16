#include "Notification.h"
#include <iostream>
#include "main_functions.h"

void Notification::confirmBookingToCustomer(const Customer& customer) {
    clearScreen();

    std::cout << "-------------------------------------------\n";
    std::cout << "Email to " << customer.getEmail() << ":\n";
    std::cout << "Dear " << customer.getName() << ",\n";
    std::cout << "Your booking has been confirmed!\n";
    std::cout << "-------------------------------------------\n";
    std::cin.get();
}

