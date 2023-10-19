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

    std::ofstream outFile(customersFile, std::ios::app);
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

    std::ifstream inFile(customersFile);
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            std::istringstream iss(line);
            getline(iss, storedUsername, ',');
            getline(iss, storedPassword);

            if (storedUsername == username && storedPassword == password) {
                std::cout << "Login successful!\n";
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
