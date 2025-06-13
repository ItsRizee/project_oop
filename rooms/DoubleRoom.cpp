#include "./DoubleRoom.h"

DoubleRoom::DoubleRoom(int number, bool isUnderRenovation)
    : Room(number, isUnderRenovation) {
    price = 80;
}

const char* DoubleRoom::GetType() const {
    return "Double Room";
}

double DoubleRoom::CalculatePricePerNight(PricingStrategy* pricingStrategy) const {
    return pricingStrategy->calculate(price);
}