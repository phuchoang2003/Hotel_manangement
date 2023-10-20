#pragma once
#include <string>

class User {
private:
    std::string userName;
    std::string password;
    double accountBalance;

public:
    User(const std::string& userName, const std::string& password, const double& accountBalance);


    void deposit(double amount);
    void withdraw(double amount);
    std::string getUsername() const;
    std::string getPassword() const;
    double getBalance() const;
};



