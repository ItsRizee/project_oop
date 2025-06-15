#include "Hotel.h"

#include <iostream>
#include <stdexcept>

Hotel::Hotel() {}

Hotel::~Hotel() {
    for (int i = 0; i < reservations.size(); i++)
        delete reservations[i];
    for (int i = 0; i < historyOfReservations.size(); i++)
        delete historyOfReservations[i];
    for (int i = 0; i < customers.size(); i++)
        delete customers[i];
    for (int i = 0; i < employees.size(); i++)
        delete employees[i];
    for (int i = 0; i < rooms.size(); i++)
        delete rooms[i];
}

static bool roomExists(Room* room, Vector<Room*> rooms) {
    for (int i = 0; i < rooms.size(); i++)
        if (rooms[i] == room)
            return true;
    return false;
}

bool Hotel::isRoomAvailable(Room* room, const Date* startDate, const Date* endDate, Employee employee) const {
    if (employee.GetPosition() != PositionType::Receptionist) {
        throw std::runtime_error("Access denied: employee role does not have permission for this feature");
    }

    if (room->UnderRenovation()) {
        return false;
    }

    for (int i = 0; i < reservations.size(); ++i) {
        if (reservations[i]->GetRoom() == room) {
            const Date* existingStart = reservations[i]->GetStartDate();
            const Date* existingEnd = reservations[i]->GetEndDate();

            if (!(*endDate <= *existingStart || *startDate >= *existingEnd)) {
                return false;
            }
        }
    }
    return true;
}

void Hotel::addReservation(Customer* customer, Room* room, Date* startDate, Date* endDate, Employee employee) {
    if (employee.GetPosition() != PositionType::Receptionist) {
        throw std::runtime_error("Access denied: employee role does not have permission for this feature");
    }

    if (!roomExists(room, rooms)) {
        throw std::invalid_argument("The room does not belong to this hotel.");
    }

    if (!isRoomAvailable(room, startDate, endDate, employee)) {
        throw std::invalid_argument("The room is not available for the selected period.");
    }

    Reservation* newReservation = new Reservation(customer, room, startDate, endDate);
    reservations.push_back(newReservation);
    historyOfReservations.push_back(newReservation);

    if (customers.contains(customer)) {
        int reservationCount = 0;
        for (int i = 0; i < historyOfReservations.size(); ++i) {
            if (historyOfReservations[i]->GetCustomer() == customer) {
                reservationCount++;
            }
        }

        if (reservationCount > 50) {
            customer->UpgradeStatus(StatusType::Platinum);
        } else if (reservationCount > 10) {
            customer->UpgradeStatus(StatusType::Gold);
        }
    } else {
        customers.push_back(customer);
    }
}

void Hotel::cancelReservation(int index, Employee employee) {
    if (employee.GetPosition() != PositionType::Receptionist) {
        throw std::runtime_error("Access denied: employee role does not have permission for this feature");
    }

    if (index < 0 || index >= reservations.size())
        throw std::out_of_range("The index is out of range");

    Date today;

    if ((*reservations[index]->GetStartDate()) < today) {
        throw std::invalid_argument("This reservation is in the past");
    }

    delete reservations[index];
    reservations.remove(index);
    delete historyOfReservations[index];
    historyOfReservations.remove(index);
}

void Hotel::addRoom(Room *room, Employee employee) {
    if (employee.GetPosition() != PositionType::Manager) {
        throw std::runtime_error("Access denied: employee role does not have permission for this feature");
    }
    rooms.push_back(room);
}

void Hotel::addEmployee(char *name, PositionType position, Employee employee) {
    if (employee.GetPosition() != PositionType::Manager) {
        throw std::runtime_error("Access denied: employee role does not have permission for this feature");
    }
    Employee* newEmployee = new Employee(name, position);
    employees.push_back(newEmployee);
}


void Hotel::analyzeCustomerActivity(Employee employee) const {
    if (employee.GetPosition() != PositionType::Manager) {
        throw std::runtime_error("Access denied: employee role does not have permission for this feature");
    }

    Vector<int> reservationCount;

    for (int i = 0; i < customers.size(); ++i) {
        reservationCount.push_back(0);
    }

    for (int i = 0; i < historyOfReservations.size(); ++i) {
        Customer* customer = historyOfReservations[i]->GetCustomer();

        for (int j = 0; j < customers.size(); ++j) {
            if (customers[j] == customer) {
                reservationCount[j]++;
                break;
            }
        }
    }

    std::cout << "Customer activity analysis:\n";
    for (int i = 0; i < customers.size(); ++i) {
        std::cout << "ID: " << customers[i]->GetID()
                  << ", Name: " << customers[i]->GetName()
                  << ", Reservations: " << reservationCount[i] << "\n";
    }

    int maxIndex = -1;
    int maxReservations = -1;
    for (int i = 0; i < reservationCount.size(); ++i) {
        if (reservationCount[i] > maxReservations) {
            maxReservations = reservationCount[i];
            maxIndex = i;
        }
    }

    if (maxIndex != -1) {
        std::cout << "\nMost loyal customer:\n";
        std::cout << "ID: " << customers[maxIndex]->GetID()
                  << ", Name: " << customers[maxIndex]->GetName()
                  << ", Reservations: " << reservationCount[maxIndex] << "\n";
    } else {
        std::cout << "No reservation history.\n";
    }
}
