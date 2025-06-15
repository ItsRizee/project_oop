#include "Hotel.h"

#include <cstring>
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

bool Hotel::isRoomAvailable(Room* room, const Date* startDate, const Date* endDate, Employee* employee) const {
    if (employee->GetPosition() != PositionType::Receptionist) {
        throw std::runtime_error("Отказан достъп: длъжността на служителя няма разрешение за тази функция");
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

void Hotel::addReservation(int id, Customer* customer, Room* room, Date* startDate, Date* endDate, Employee* employee) {
    if (employee->GetPosition() != PositionType::Receptionist) {
        throw std::runtime_error("Отказан достъп: длъжността на служителя няма разрешение за тази функция");
    }

    if (!roomExists(room, rooms)) {
        throw std::invalid_argument("Стаята не принадлежи на този хотел");
    }

    if (!isRoomAvailable(room, startDate, endDate, employee)) {
        throw std::invalid_argument("Стаята не е налична за избрания период.");
    }

    Reservation* newReservation = new Reservation(id, customer, room, startDate, endDate);
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

void Hotel::cancelReservation(int id, Employee* employee) {
    PositionType position = employee->GetPosition();
    if (position != PositionType::Receptionist && position != PositionType::Manager) {
        throw std::runtime_error("Отказан достъп: длъжността на служителя няма разрешение за тази функция");
    }

    int index = -1;
    for (int i = 0; i < reservations.size(); ++i) {
        if (reservations[i]->GetID() == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        throw std::invalid_argument("Резервацията с този идентификатор не съществува");
    }

    Date today;
    if (*reservations[index]->GetStartDate() < today) {
        throw std::invalid_argument("Не можете да отмените минала резервация");
    }

    Reservation* toDelete = reservations[index];
    reservations.remove(index);
    delete toDelete;

    for (int i = 0; i < historyOfReservations.size(); ++i) {
        if (historyOfReservations[i]->GetID() == id) {
            Reservation* histDelete = historyOfReservations[i];
            historyOfReservations.remove(i);
            delete histDelete;
            break;
        }
    }
}

void Hotel::addCustomer(Customer *customer, Employee *employee) {
    PositionType position = employee->GetPosition();
    if (position != PositionType::Receptionist && position != PositionType::Manager) {
        throw std::runtime_error("Отказан достъп: длъжността на служителя няма разрешение за тази функция");
    }

    customers.push_back(customer);
}

void Hotel::addRoom(Room *room, Employee* employee) {
    if (employee->GetPosition() != PositionType::Manager) {
        throw std::runtime_error("Отказан достъп: длъжността на служителя няма разрешение за тази функция");
    }

    rooms.push_back(room);
}

void Hotel::addEmployee(Employee* newEmployee, Employee *employee) {
    if (employee->GetPosition() != PositionType::Manager) {
        throw std::runtime_error("Отказан достъп: длъжността на служителя няма разрешение за тази функция");
    }
    employees.push_back(newEmployee);
}

Employee *Hotel::getEmployeeByUsername(char *username) const {
    for (int i = 0; i < employees.size(); i++) {
        if (strcmp(employees[i]->GetUsername(), username) == 0) {
            return employees[i];
        }
    }

    return nullptr;
}

Customer* Hotel::getCustomerById(int id) const {
    for (int i = 0; i < customers.size(); ++i) {
        if (customers[i]->GetID() == id) {
            return customers[i];
        }
    }
    return nullptr;
}

Room* Hotel::getRoomByNumber(int number) const {
    for (int i = 0; i < rooms.size(); ++i) {
        if (rooms[i]->GetNumber() == number) {
            return rooms[i];
        }
    }
    return nullptr;
}

void Hotel::showAvailableRooms(Employee* employee) const {
    PositionType position = employee->GetPosition();
    if (position != PositionType::Receptionist && position != PositionType::Manager) {
        throw std::runtime_error("Отказан достъп: длъжността на служителя няма разрешение за тази функция");
    }

    std::cout << "\n=== Налични стаи ===\n";

    for (int i = 0; i < rooms.size(); ++i) {
        Room* room = rooms[i];
        bool isOccupied = false;

        if (room->UnderRenovation()) continue;

        for (int j = 0; j < reservations.size(); ++j) {
            if (reservations[j] != nullptr && *(reservations[j]->GetRoom()) == *room) {
                Date* start = reservations[j]->GetStartDate();
                Date* end = reservations[j]->GetEndDate();
                Date today;

                if ((*start <= today) && (today <= *end)) {
                    isOccupied = true;
                    break;
                }
            }
        }

        if (!isOccupied) {
            std::cout << "Стая №" << room->GetNumber() << " - тип: " << room->GetType() << std::endl;
        }
    }
}

void Hotel::showReservations(Employee* employee) const {
    PositionType position = employee->GetPosition();
    if (position != PositionType::Receptionist && position != PositionType::Manager) {
        throw std::runtime_error("Отказан достъп: длъжността на служителя няма разрешение за тази функция");
    }

    std::cout << "\n=== Текущи резервации ===\n";

    for (int i = 0; i < reservations.size(); ++i) {
        if (reservations[i] != nullptr) {
            Reservation* res = reservations[i];
            std::cout << "Резервация ID: " << res->GetID()
                      << " | Клиент: " << res->GetCustomer()->GetName()
                      << " | Стая №" << res->GetRoom()->GetNumber()
                      << " | От: ";
            res->GetStartDate()->Print();
            std::cout << " | До: ";
            res->GetEndDate()->Print();
            std::cout << std::endl;
        }
    }
}


void Hotel::analyzeCustomerActivity(Employee* employee) const {
    if (employee->GetPosition() != PositionType::Manager) {
        throw std::runtime_error("Отказан достъп: длъжността на служителя няма разрешение за тази функция");
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

    std::cout << "Анализ на клиентстка активност:\n";
    for (int i = 0; i < customers.size(); ++i) {
        std::cout << "Идентификатор: " << customers[i]->GetID()
                  << ", Име: " << customers[i]->GetName()
                  << ", Резервации: " << reservationCount[i] << "\n";
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
        std::cout << "\nНай-лоялен клиент:\n";
        std::cout << "Идентификатор: " << customers[maxIndex]->GetID()
                  << ", Име: " << customers[maxIndex]->GetName()
                  << ", Резервации: " << reservationCount[maxIndex] << "\n";
    } else {
        std::cout << "Няма история на резервациите\n";
    }
}

void Hotel::calculateRevenue(Employee* employee) const {
    PositionType position = employee->GetPosition();
    if (position != PositionType::Accountant && position != PositionType::Manager) {
        throw std::runtime_error("Отказан достъп: длъжността на служителя няма разрешение за тази функция");
    }

    double dailyRevenue = 0;
    double monthlyRevenue = 0;
    double yearlyRevenue = 0;
    int totalNights = 0;

    struct RoomStats {
        const char* type;
        double revenue;
        int reservationCount;
    };

    const int MAX_TYPES = 5;
    RoomStats stats[MAX_TYPES] = {
        {"SingleRoom", 0, 0},
        {"DoubleRoom", 0, 0},
        {"ConferenceRoom", 0, 0},
        {"Apartment", 0, 0},
        {"LuxuryRoom", 0, 0}
    };

    Date today;

    for (int i = 0; i < reservations.size(); ++i) {
        Reservation* reservation = reservations[i];
        Date* start = reservation->GetStartDate();
        Date* end = reservation->GetEndDate();

        int nights = start->GetNights(*end);
        double price = reservation->CalculatePrice();

        if (start->GetDay() == today.GetDay() &&
            start->GetMonth() == today.GetMonth() &&
            start->GetYear() == today.GetYear()) {
            dailyRevenue += price;
        }

        if (start->GetMonth() == today.GetMonth() &&
            start->GetYear() == today.GetYear()) {
            monthlyRevenue += price;
        }

        if (start->GetYear() == today.GetYear()) {
            yearlyRevenue += price;
        }

        const char* roomType = reservation->GetRoom()->GetType();
        for (int j = 0; j < MAX_TYPES; ++j) {
            if (strcmp(stats[j].type, roomType) == 0) {
                stats[j].revenue += price;
                stats[j].reservationCount++;
                break;
            }
        }

        totalNights += nights;
    }

    std::cout << "\n=== Приходи ===\n";
    std::cout << "Днес: " << dailyRevenue << " лв\n";
    std::cout << "Този месец: " << monthlyRevenue << " лв\n";
    std::cout << "Тази година: " << yearlyRevenue << " лв\n";

    double maxRevenue = 0;
    const char* topRoomType = "";

    for (int i = 0; i < MAX_TYPES; ++i) {
        const char* nameBG = "";

        if (strcmp(stats[i].type, "SingleRoom") == 0)
            nameBG = "Единична стая";
        else if (strcmp(stats[i].type, "DoubleRoom") == 0)
            nameBG = "Двойна стая";
        else if (strcmp(stats[i].type, "ConferenceRoom") == 0)
            nameBG = "Конферентна зала";
        else if (strcmp(stats[i].type, "Apartment") == 0)
            nameBG = "Апартамент";
        else if (strcmp(stats[i].type, "LuxuryRoom") == 0)
            nameBG = "Луксозна стая";
        else
            nameBG = "Неизвестен тип";

        std::cout << nameBG << ": "
                  << stats[i].revenue << " лв, "
                  << stats[i].reservationCount << " резервации\n";

        if (stats[i].revenue > maxRevenue) {
            maxRevenue = stats[i].revenue;
            topRoomType = nameBG;
        }
    }

    std::cout << "\n🏆 Най-печеливш тип стая: " << topRoomType
              << " с приходи " << maxRevenue << " лв\n";

    std::cout << "\nОбщ брой нощувки: " << totalNights << "\n";
    std::cout << "Общо резервации: " << reservations.size() << "\n";

    double occupancy = 0;
    if (rooms.size() > 0) {
        occupancy = (double)totalNights / rooms.size();
    }

    std::cout << "Средна заетост (нощувки на стая): " << occupancy << "\n";
}