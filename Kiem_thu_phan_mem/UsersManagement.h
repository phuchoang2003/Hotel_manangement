#pragma once
#include <string>
#include "User.h"

class UserManager {
private:
    std::string usersFile = "users.txt";
    User* loggedInUser = nullptr;



public:
    void registerCustomer();
    bool loginCustomer();
    void depositToLoggedInUser(double amount);
    bool withdrawFromLoggedInUser(double amount);
    double getBalanceOfLoggedInUser() const;
};
