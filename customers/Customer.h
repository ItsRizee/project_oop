#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "CustomerStatus.h"

class Customer {
private:
    char* name;
    char *phoneNumber;
    char *email;
    int id;
    CustomerStatus* customerStatus;

public:
    Customer(char *name, char *phoneNumber, char *email, int id, StatusType statusType);
    ~Customer();

    char* GetName() const;
    char* GetPhone() const;
    char* GetEmail() const;
    int GetID() const;
    int GetDiscount() const;
    StatusType getStatusType() const;
    void UpgradeStatus(StatusType newStatus);

    bool operator==(const Customer& other) const;
};

#endif