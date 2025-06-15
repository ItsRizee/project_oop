#ifndef ROOM_H
#define ROOM_H

#include "../pricing/PricingStrategy.h"

class Room {
protected:
    int number;
    bool isUnderRenovation;

public:
    Room(int number, bool isUnderRenovation);
    virtual ~Room();

    bool UnderRenovation() const;
    void SetUnderRenovation(bool value);
    virtual const char* GetType() const = 0;
    virtual double CalculatePricePerNight(PricingStrategy* pricingStrategy) const = 0;

    bool operator==(const Room& other) const;
};

#endif
