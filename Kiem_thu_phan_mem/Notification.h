#pragma once
#include <string>
#include "Customer.h"

class Notification {
public:
    static void confirmBookingToCustomer(const Customer& customer);
   /* static void notifyStaff(const Customer& customer);*/
};
