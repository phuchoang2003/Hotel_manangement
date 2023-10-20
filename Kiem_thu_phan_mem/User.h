#pragma once
#include <string>

class User {
private:
    std::string userName;
    std::string password;
    double accountBalance;

public:
    User(const std::string& userName, const std::string& password);


    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;
};
