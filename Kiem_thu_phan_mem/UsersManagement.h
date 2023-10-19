#pragma once
#include <string>

class UserManager {
private:
    std::string customersFile = "users.txt";

public:
    void registerCustomer();
    bool loginCustomer();
};
