#include "LuxuryRoom.h"

LuxuryRoom::LuxuryRoom(int number, bool isUnderRenovation)
    : Room(number, isUnderRenovation) {
    price = 200;
}

const char* LuxuryRoom::GetType() const {
    return "LuxuryRoom";
}

double LuxuryRoom::CalculatePricePerNight(PricingStrategy* pricingStrategy) const {
    return pricingStrategy->calculate(price);
}