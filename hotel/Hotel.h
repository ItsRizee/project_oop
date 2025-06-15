#ifndef HOTEL_H
#define HOTEL_H

#include "../reservations/Reservation.h"
#include "Vector.h"
#include "../employees/Employee.h"

class Hotel {
private:
    Vector<Reservation*> reservations;
    Vector<Reservation*> historyOfReservations;
    Vector<Customer*> customers;
    Vector<Room*> rooms;
    Vector<Employee*> employees;

public:
    Hotel();
    ~Hotel();

    bool isRoomAvailable(Room* room, const Date* startDate, const Date* endDate, Employee employee) const;
    void addReservation(Customer* customer, Room* room, Date* startDate, Date* endDate, Employee employee);
    void cancelReservation(int index, Employee employee);

    void addRoom(Room* room, Employee employee);
    void addEmployee(char* name, PositionType position, Employee employee);
    void analyzeCustomerActivity(Employee employee) const;
};

#endif
