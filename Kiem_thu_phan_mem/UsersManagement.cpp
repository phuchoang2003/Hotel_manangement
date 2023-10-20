#include <iostream>
#include <fstream>
#include <sstream> 
#include "UsersManagement.h"

void UserManager::registerCustomer() {
    std::string username, password;

    std::cout << "Register a new customer:\n";
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::ofstream outFile(usersFile, std::ios::app);
    if (outFile.is_open()) {
        outFile << username << "," << password << "\n";
        outFile.close();
    }
    else {
        std::cerr << "Unable to open the users file!";
    }
}

bool UserManager::loginCustomer() {
    std::string username, password, line, storedUsername, storedPassword;

    std::cout << "Login as a customer:\n";
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::ifstream inFile(usersFile);
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            std::istringstream iss(line);
            getline(iss, storedUsername, ',');
            getline(iss, storedPassword);

            if (storedUsername == username && storedPassword == password) {
                std::cout << "Login successful!\n";
                if (loggedInUser) {
                    delete loggedInUser;
                }
                loggedInUser = new User(username, password);
                return true;
            }
        }
        inFile.close();
    }
    else {
        std::cerr << "Unable to open the users file!";
    }

    return false;
}


void UserManager::depositToLoggedInUser(double amount) {
    if (loggedInUser) {
        loggedInUser->deposit(amount);
        // TODO: Cập nhật thông tin người dùng trong tệp hoặc cơ sở dữ liệu nếu cần
    }
    else {
        std::cout << "No user is currently logged in." << std::endl;
    }
}

bool UserManager::withdrawFromLoggedInUser(double amount) {
    if (loggedInUser) {
        if (loggedInUser->getBalance() >= amount) {
            loggedInUser->withdraw(amount);
            // TODO: Cập nhật thông tin người dùng trong tệp hoặc cơ sở dữ liệu nếu cần
            return true;
        }
        else {
            std::cout << "Insufficient funds in the account." << std::endl;
            return false;
        }
    }
    else {
        std::cout << "No user is currently logged in." << std::endl;
        return false;
    }
}


double UserManager::getBalanceOfLoggedInUser() const {
    if (loggedInUser) {
        return loggedInUser->getBalance();
    }
    else {
        std::cout << "No user is currently logged in." << std::endl;
        return -1.0;
    }
}

