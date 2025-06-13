#include "Room.h"

Room::Room(int number, bool isUnderRenovation, PricingStrategy* strategy)
    : number(number), isUnderRenovation(isUnderRenovation), pricingStrategy(strategy) {}

bool Room::underRenovation() const { return isUnderRenovation; }

void Room::setUnderRenovation(bool value) { isUnderRenovation = value; }

Room::~Room() {
    delete pricingStrategy;
}



// double Room::calculatePrice(const ReservationContext& context) const {
//     return pricingStrategy->calculate(*this, context);
// }