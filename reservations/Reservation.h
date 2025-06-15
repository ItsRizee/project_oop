#ifndef RESERVATION_H
#define RESERVATION_H

#include "Date.h"
#include "../customers/Customer.h"
#include "../rooms/Room.h"

class Reservation {
private:
    int id;
    Customer* customer;
    Room* room;
    Date* startDate;
    Date* endDate;

    bool validInput(Customer* customer, Room* room, Date* startDate, Date* endDate);

public:
    Reservation(int id, Customer* customer, Room* room, Date* startDate, Date* endDate);

    int GetID() const;
    Customer* GetCustomer() const;
    Room* GetRoom() const;
    Date* GetStartDate() const;
    Date* GetEndDate() const;
    double CalculatePrice() const;

};
#endif
