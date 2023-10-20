#pragma once
#include <string>
#include "User.h"

class UserManager {
private:
    std::string usersFile = "users.txt";
    User* loggedInUser = nullptr;



public:
    ~UserManager();
    void registerCustomer();
    bool loginCustomer();
    void depositToLoggedInUser(double amount);
    bool withdrawFromLoggedInUser(double amount);
    double getBalanceOfLoggedInUser() const;
    void saveLoggedInUserInfo();
    std::string getLoggedInUsername() const; 
    double getLoggedInUserBalance() const;  
    void logout();
    bool isUserLoggedIn() const;
};