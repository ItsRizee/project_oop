#include "Customer.h"
#include "CustomerStatus.h"
#include <cstring>

Customer::Customer(char* name, char* phoneNumber, char* email, int id, StatusType statusType)
    : id(id)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    this->phoneNumber = new char[strlen(phoneNumber) + 1];
    strcpy(this->phoneNumber, phoneNumber);

    this->email = new char[strlen(email) + 1];
    strcpy(this->email, email);

    this->customerStatus = new CustomerStatus(statusType);
}

char* Customer::GetName() const {
    return name;
}

char* Customer::GetPhone() const {
    return phoneNumber;
}

char* Customer::GetEmail() const {
    return email;
}

int Customer::GetID() const {
    return id;
}

int Customer::GetDiscount() const {
    return customerStatus->GetDiscount();
}

StatusType Customer::getStatusType() const {
    return customerStatus->GetStatusType();
}

void Customer::UpgradeStatus(StatusType newStatus) {
    customerStatus->SetStatusType(newStatus);
}

Customer::~Customer() {
    delete[] name;
    delete[] phoneNumber;
    delete[] email;
    delete customerStatus;
}

bool Customer::operator==(const Customer& other) const {
    return this->id == other.id;
}