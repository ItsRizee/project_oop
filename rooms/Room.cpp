#include "Room.h"

Room::Room(int number, bool isUnderRenovation)
    : number(number), isUnderRenovation(isUnderRenovation) {}

bool Room::UnderRenovation() const {
    return isUnderRenovation;
}

void Room::SetUnderRenovation(bool value) {
    isUnderRenovation = value;
}

bool Room::operator==(const Room& other) const {
    return this->number == other.number;
}