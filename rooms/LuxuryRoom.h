#ifndef LUXURYROOM_H
#define LUXURYROOM_H

#include "Room.h"

class LuxuryRoom : public Room {
private:
    double price;
public:
    LuxuryRoom(int number, bool isUnderRenovation);

    const char* GetType() const override;
    double CalculatePricePerNight(PricingStrategy* strategy) const override;
};

#endif
