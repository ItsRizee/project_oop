#ifndef SINGLEROOM_H
#define SINGLEROOM_H

#include "Room.h"

class SingleRoom : public Room {
private:
    double price;
public:
    SingleRoom(int number, bool isUnderRenovation);

    const char* GetType() const override;
    double CalculatePricePerNight(PricingStrategy* strategy) const override;
};

#endif