#include "Customer.h"
#include <iostream>
#include <fstream>

Customer::Customer(const std::string& name, const std::string& email, const std::string& phone)
    : name(name), email(email), phone(phone) {}

std::string Customer::getName() const {
    return name;
}

std::string Customer::getEmail() const {
    return email;
}

std::string Customer::getPhone() const {
    return phone;
}

void Customer::saveToFile() const {
    std::ofstream outFile("customers.txt", std::ios::app); // append mode
    if (outFile.is_open()) {
        outFile << getName() << ","
            << getEmail() << ","
            << getPhone() << ",";
            //<< getBalance() << "\n";  // if you want to save accountBalance
        outFile.close();
    }
    else {
        std::cerr << "Unable to open file for writing!";
    }
}

