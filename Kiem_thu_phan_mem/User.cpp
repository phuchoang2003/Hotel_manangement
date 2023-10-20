#include "User.h"
#include <iostream>
#include <iomanip> 

User::User(const std::string& userName, const std::string& password, const double& accountBalance)
    : userName(userName), password(password), accountBalance(accountBalance) {}

void User::deposit(double amount) {
    if (amount > 0) {
        accountBalance += amount;
        std::cout << std::fixed << std::setprecision(2) << "Deposited $" << amount << ". New balance: $" << accountBalance << std::endl;
    }
    else {
        std::cout << "Invalid amount entered." << std::endl;
    }
}

void User::withdraw(double amount) {
    if (amount > 0 && amount <= accountBalance) {
        accountBalance -= amount;
        std::cout << std::fixed << std::setprecision(2) << "Withdrew $" << amount << ". Remaining balance: $" << accountBalance << std::endl;
    }
    else {
        std::cout << "Invalid amount or insufficient funds." << std::endl;
    }
}

double User::getBalance() const {
    return accountBalance;
}

std::string User::getUsername() const {
    return userName;
}

std::string User::getPassword() const {
    return password;
}
