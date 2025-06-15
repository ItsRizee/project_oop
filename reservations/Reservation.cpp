#include "Reservation.h"

#include <stdexcept>

#include "../pricing/PricingStrategyFactory.h"

bool Reservation::validInput(Customer *customer, Room *room, Date *startDate, Date *endDate) {
    if (!customer || !room || !startDate || !endDate)
        return false;

    Date today;
    if (*startDate < today || *endDate < today)
        return false;

    if (*startDate > *endDate)
        return false;

    return true;
}

Reservation::Reservation(int id, Customer *customer, Room *room, Date *startDate, Date *endDate) : id(id) {
    if (validInput(customer, room, startDate, endDate)) {
        this->customer = customer;
        this->room = room;
        this->startDate = startDate;
        this->endDate = endDate;
    } else {
        throw std::invalid_argument("Invalid arguments");
    }
}

int Reservation::GetID() const {
    return id;
}

Customer* Reservation::GetCustomer() const {
    return customer;
}

Room* Reservation::GetRoom() const {
    return room;
}

Date* Reservation::GetStartDate() const {
    return startDate;
}

Date* Reservation::GetEndDate() const {
    return endDate;
}

double Reservation::CalculatePrice() const {
    int nights = startDate->GetNights(*endDate);
    PricingStrategy* pricingStrategy = PricingStrategyFactory::createPricingStrategy(startDate, endDate);
    double price = nights * room->CalculatePricePerNight(pricingStrategy);
    return price - (price * customer->GetDiscount());
}
