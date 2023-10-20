// User.cpp
#include "User.h"
#include <iostream>

User::User(const std::string& userName, const std::string& password)
: userName(userName) ,password(password), accountBalance(0.0) {}

void User::deposit(double amount) {
    if (amount > 0) {
        accountBalance += amount;
        std::cout << "Deposited $" << amount << ". New balance: $" << accountBalance << std::endl;
    }
    else {
        std::cout << "Invalid amount entered." << std::endl;
    }
}

void User::withdraw(double amount) {
    if (amount > 0 && amount <= accountBalance) {
        accountBalance -= amount;
        std::cout << "Withdrew $" << amount << ". Remaining balance: $" << accountBalance << std::endl;
    }
    else {
        std::cout << "Invalid amount or insufficient funds." << std::endl;
    }
}

double User::getBalance() const {
    return accountBalance;
}
