#include "./ConferenceRoom.h"

ConferenceRoom::ConferenceRoom(int number, bool isUnderRenovation)
    : Room(number, isUnderRenovation) {
    price = 100;
}

const char* ConferenceRoom::GetType() const {
    return "ConferenceRoom";
}

double ConferenceRoom::CalculatePricePerNight(PricingStrategy* pricingStrategy) const {
    return pricingStrategy->calculate(price);
}