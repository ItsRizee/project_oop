#include "SingleRoom.h"

SingleRoom::SingleRoom(int number, bool isUnderRenovation)
    : Room(number, isUnderRenovation) {
    price = 50;
}

const char* SingleRoom::GetType() const {
    return "SingleRoom";
}

double SingleRoom::CalculatePricePerNight(PricingStrategy* pricingStrategy) const {
    return pricingStrategy->calculate(price);
}