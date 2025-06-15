// Никола Петров
// ФН: 3MI0600533
// GitHub: https://github.com/ItsRizee/project_oop

#include <iostream>
#include "hotel/Hotel.h"
#include "employees/Employee.h"
#include "rooms/Apartment.h"
#include "rooms/ConferenceRoom.h"
#include "rooms/DoubleRoom.h"
#include "rooms/LuxuryRoom.h"
#include "rooms/SingleRoom.h"

void showMenu(PositionType position) {
    std::cout << "\n=== Меню ===\n";
    if (position == PositionType::Manager) {
        std::cout << "1. Добавяне на стая\n";
    }
    if (position == PositionType::Receptionist || position == PositionType::Manager) {
        std::cout << "2. Регистрация на гост\n";
        std::cout << "3. Създаване на резервация\n";
        std::cout << "4. Преглед на налични стаи\n";
        std::cout << "5. Преглед на текущи резервации\n";
        std::cout << "6. Анулиране на резервация\n";
    }
    if (position == PositionType::Accountant || position == PositionType::Manager) {
        std::cout << "7. Изчисляване и преглед на приходи\n";
    }
    if (position == PositionType::Manager) {
        std::cout << "8. Преглед на клиентска активност и лоялност\n";
    }
    std::cout << "9. Смяна на длъжност\n";
    std::cout << "0. Изход\n";
}

void addRoom(Hotel* hotel, Employee* employee) {
    int number;
    bool underRenovation;

    while (true) {
        std::cout << "Номер на стаята: ";
        std::cin >> number;
        if (hotel->getRoomByNumber(number) != nullptr) {
            std::cout << "Стая с този номер вече съществува.\n";
        } else {
            break;
        }
    }

    std::cout << "Стаята в ремонт ли е? (1 = да, 0 = не): ";
    std::cin >> underRenovation;

    int roomType;
    bool validInput = false;
    Room* newRoom = nullptr;

    while (!validInput) {
        std::cout << "1. Единична стая" << std::endl;
        std::cout << "2. Двойна стая" << std::endl;
        std::cout << "3. Конферентна зала" << std::endl;
        std::cout << "4. Апартамент" << std::endl;
        std::cout << "5. Луксозна стая" << std::endl;
        std::cout << "Изберете вид стая: " << std::endl;
        std::cin >> roomType;

        switch (roomType) {
            case 1:
                newRoom = new SingleRoom(number, underRenovation);
                validInput = true;
                break;
            case 2:
                newRoom = new DoubleRoom(number, underRenovation);
                validInput = true;
                break;
            case 3:
                newRoom = new ConferenceRoom(number, underRenovation);
                validInput = true;
                break;
            case 4:
                newRoom = new Apartment(number, underRenovation);
                validInput = true;
                break;
            case 5:
                newRoom = new LuxuryRoom(number, underRenovation);
                validInput = true;
                break;
            default:
                validInput = false;
        }
    }

    hotel->addRoom(newRoom, employee);
}

void registerCustomer(Hotel* hotel, Employee* employee) {
    char name[100];
    char phone[20];
    char email[100];
    int id;

    std::cout << "Име на клиента: ";
    std::cin.ignore();
    std::cin.getline(name, 100);

    std::cout << "Телефонен номер: ";
    std::cin.getline(phone, 20);

    std::cout << "Имейл: ";
    std::cin.getline(email, 100);

    while (true) {
        std::cout << "ID на клиента: ";
        std::cin >> id;

        if (hotel->getCustomerById(id) != nullptr) {
            std::cout << "Клиент с това ID вече съществува.\n";
        } else {
            break;
        }
    }

    Customer* newCustomer = new Customer(name, phone, email, id, StatusType::Regular);
    hotel->addCustomer(newCustomer, employee);
}

void addReservation(Hotel* hotel, Employee* employee) {
    int id, customerId, roomNumber;
    int sDay, sMonth, sYear, eDay, eMonth, eYear;

    std::cout << "ID на резервацията: ";
    std::cin >> id;

    std::cout << "ID на клиента: ";
    std::cin >> customerId;

    Customer* customer = hotel->getCustomerById(customerId);
    if (!customer) {
        std::cout << "Клиент с този ID не съществува.\n";
    }

    std::cout << "Номер на стаята: ";
    std::cin >> roomNumber;

    Room* room = hotel->getRoomByNumber(roomNumber);
    if (!room) {
        std::cout << "Стая с този номер не съществува.\n";
    }

    std::cout << "Начална дата (ден месец година): ";
    std::cin >> sDay >> sMonth >> sYear;
    std::cout << "Крайна дата (ден месец година): ";
    std::cin >> eDay >> eMonth >> eYear;

    Date* startDate = new Date(sDay, sMonth, sYear);
    Date* endDate = new Date(eDay, eMonth, eYear);
    hotel->addReservation(id, customer, room, startDate, endDate, employee);
}

void cancelReservation(Hotel* hotel, Employee* employee) {
    int id;
    std::cout << "ID на резервацията, която искате да анулирате: ";
    std::cin >> id;
    hotel->cancelReservation(id, employee);
}

int main() {
    Hotel* hotel;
    char username[100];
    bool running = true;

    Employee* manager = new Employee("manager", PositionType::Manager);
    Employee* receptionist = new Employee("receptionist", PositionType::Receptionist);
    Employee* accountant = new Employee("accountant", PositionType::Accountant);

    hotel->addEmployee(manager, manager);
    hotel->addEmployee(receptionist, receptionist);
    hotel->addEmployee(accountant, accountant);

    Employee* employee = nullptr;

    while (running) {
        while (true) {
            std::cout << "\n=== Вход в системата ===\n";
            std::cout << "Потребителско име: ";
            std::cin.ignore();
            std::cin.getline(username, 100);

            employee = hotel->getEmployeeByUsername(username);
            if (employee == nullptr) {
                std::cout << "Невалидно потребителско име. Опитайте отново.\n";
            } else {
                break;
            }
        }

        PositionType position = employee->GetPosition();
        int choice;

        do {
            showMenu(position);
            std::cout << "Избор: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    if (position == PositionType::Manager) {
                        addRoom(hotel, employee);
                    } else std::cout << "Нямате достъп до тази функция.\n";
                    break;
                case 2:
                    if (position == PositionType::Receptionist || position == PositionType::Manager) {
                        registerCustomer(hotel, employee);
                    } else std::cout << "Нямате достъп до тази функция.\n";
                    break;
                case 3:
                    if (position == PositionType::Receptionist || position == PositionType::Manager) {
                        addReservation(hotel, employee);
                    } else std::cout << "Нямате достъп до тази функция.\n";
                    break;
                case 4:
                    if (position == PositionType::Receptionist || position == PositionType::Manager) {
                        hotel->showAvailableRooms(employee)
                    } else std::cout << "Нямате достъп до тази функция.\n";
                    break;
                case 5:
                    if (position == PositionType::Receptionist || position == PositionType::Manager) {
                        hotel->showReservations(employee);
                    } else std::cout << "Нямате достъп до тази функция.\n";
                    break;
                case 6:
                    if (position == PositionType::Receptionist || position == PositionType::Manager) {
                        cancelReservation(hotel, employee);
                    } else std::cout << "Нямате достъп до тази функция.\n";
                    break;
                case 7:
                    if (position == PositionType::Accountant || position == PositionType::Manager) {
                        hotel->calculateRevenue(employee);
                    } else std::cout << "Нямате достъп до тази функция.\n";
                    break;
                case 8:
                    if (position == PositionType::Manager) {
                        hotel->analyzeCustomerActivity(employee);
                    } else std::cout << "Нямате достъп до тази функция.\n";
                    break;
                case 9:
                    std::cout << "Изход от текущия акаунт.\n";
                    break;
                case 0:
                    running = false;
                    break;
                default:
                    std::cout << "Невалиден избор.\n";
                    break;
            }
        } while (choice != 0 && choice != 9);
    }

    std::cout << "Изход от системата.\n";
    return 0;
}