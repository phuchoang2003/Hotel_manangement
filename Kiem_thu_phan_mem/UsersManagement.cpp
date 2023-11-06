#include <iostream>
#include <fstream>
#include <sstream> 
#include "UsersManagement.h"
#include <vector>


UserManager::~UserManager() {
    logout();
}


void UserManager::registerCustomer() {
    std::string username, password;

    std::cout << "Register a new customer:\n";
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::ofstream outFile(usersFile, std::ios::app);
    if (outFile.is_open()) {
        outFile << username << "," << password << ",0.0" << "\n"; 
        outFile.close();
    }
    else {
        std::cerr << "Unable to open the users file!";
    }
}

bool UserManager::loginCustomer() {
    std::string username, password, line, storedUsername, storedPassword, balanceStr;

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
            getline(iss, storedPassword, ',');
            getline(iss, balanceStr);

            if (storedUsername == username && storedPassword == password) {
                std::cout << "Login successful!\n";
                std::cin.ignore();
                std::cin.get();
                if (loggedInUser) {
                    saveLoggedInUserInfo();
                    delete loggedInUser;
                }
                double balance = std::stod(balanceStr);  // Convert string to double
                loggedInUser = new User(username, password, balance);
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
        saveLoggedInUserInfo();
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
            saveLoggedInUserInfo();
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


std::string UserManager::getLoggedInUsername() const {
    if (loggedInUser) {
        return loggedInUser->getUsername();  // Bạn cần thêm phương thức getUsername() cho lớp User
    }
    return "";
}

double UserManager::getLoggedInUserBalance() const {
    if (loggedInUser) {
        return loggedInUser->getBalance();
    }
    return 0.0;  // hoặc trả về một giá trị không hợp lệ nào đó
}

bool UserManager::isUserLoggedIn() const {
    return loggedInUser != nullptr;
}





void UserManager::saveLoggedInUserInfo() {
    std::vector<std::string> fileLines;
    std::ifstream inFile(usersFile);
    std::string line;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            std::istringstream iss(line);                    

            std::string storedUsername;
            getline(iss, storedUsername, ',');
            if(storedUsername == loggedInUser->getUsername()) {
                std::ostringstream oss;
                oss << loggedInUser->getUsername() << ","
                    << loggedInUser->getPassword() << ","
                    << loggedInUser->getBalance();
                fileLines.push_back(oss.str());
            }
            else {
                fileLines.push_back(line);
            }
        }
        inFile.close();
    }

    // Ghi lại nội dung file với thông tin người dùng cập nhật
    std::ofstream outFile(usersFile);
    for (const auto& line : fileLines) {
        outFile << line << "\n";
    }
    outFile.close();
}


void UserManager::logout() {
    if (loggedInUser) {
        saveLoggedInUserInfo();
        delete loggedInUser;
        loggedInUser = nullptr;
    }
}