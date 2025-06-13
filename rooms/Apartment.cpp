#include "Apartment.h"

Apartment::Apartment(int number, bool isUnderRenovation)
    : Room(number, isUnderRenovation) {
    price = 150;
}

const char* Apartment::GetType() const {
    return "Apartment";
}

double Apartment::CalculatePricePerNight(PricingStrategy* pricingStrategy) const {
    return pricingStrategy->calculate(price);
}