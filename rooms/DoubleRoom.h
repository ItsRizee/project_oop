#ifndef DOUBLEROOM_H
#define DOUBLEROOM_H

#include "Room.h"

class DoubleRoom : public Room {
private:
    double price;
public:
    DoubleRoom(int number, bool isUnderRenovation);

    const char* GetType() const override;
    double CalculatePricePerNight(PricingStrategy* strategy) const override;
};

#endif
