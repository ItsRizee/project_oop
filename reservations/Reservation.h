#ifndef RESERVATION_H
#define RESERVATION_H

#include "Date.h"
#include "../customers/Customer.h"
#include "../rooms/Room.h"

class Reservation {
private:
    Customer* customer;
    Room* room;
    Date* startDate;
    Date* endDate;

    bool validInput(Customer* customer, Room* room, Date* startDate, Date* endDate);

public:
    Reservation(Customer* customer, Room* room, Date* startDate, Date* endDate);

    Customer* GetCustomer() const;
    Room* GetRoom() const;
    Date* GetStartDate() const;
    Date* GetEndDate() const;
    double CalculatePrice() const;

};
#endif
