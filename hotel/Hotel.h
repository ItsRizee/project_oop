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

    bool isRoomAvailable(Room* room, const Date* startDate, const Date* endDate, Employee* employee) const;
    void addReservation(int id, Customer* customer, Room* room, Date* startDate, Date* endDate, Employee* employee);
    void cancelReservation(int id, Employee* employee);
    void addCustomer(Customer* customer, Employee* employee);
    void addRoom(Room* room, Employee* employee);
    void addEmployee(Employee* newEmployee, Employee* employee);
    Employee* getEmployeeByUsername(char* username) const;
    Customer* getCustomerById(int id) const;
    Room* getRoomByNumber(int number) const;
    void showAvailableRooms(Employee* employee) const;
    void showReservations(Employee* employee) const;
    void analyzeCustomerActivity(Employee* employee) const;
    void calculateRevenue(Employee* employee) const;
};

#endif
