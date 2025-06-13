#ifndef APARTMENT_H
#define APARTMENT_H

#include "Room.h"

class Apartment : public Room {
private:
    double price;
public:
    Apartment(int number, bool isUnderRenovation);

    const char* GetType() const override;
    double CalculatePricePerNight(PricingStrategy* strategy) const override;
};

#endif
