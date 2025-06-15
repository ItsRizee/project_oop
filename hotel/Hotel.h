#ifndef HOTEL_H
#define HOTEL_H

#include "../reservations/Reservation.h"
#include "Vector.h"

class Hotel {
private:
    Vector<Reservation*> reservations;
    Vector<Reservation*> historyOfReservations;
    Vector<Customer*> customers;
    Vector<Room*> rooms;

public:
    Hotel();
    ~Hotel();

    bool isRoomAvailable(Room* room, const Date* startDate, const Date* endDate) const;
    void addReservation(Customer* customer, Room* room, Date* startDate, Date* endDate);
    void cancelReservation(int index);

    void addRoom(Room* room);
    void analyzeCustomerActivity() const;
};

#endif
