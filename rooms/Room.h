#ifndef ROOM_H
#define ROOM_H

#include "../pricing/PricingStrategy.h"

class Room {
protected:
    int number;
    bool isUnderRenovation;
    PricingStrategy* pricingStrategy;

public:
    Room(int number, bool isUnderRenovation, PricingStrategy* strategy);
    virtual ~Room();

    bool underRenovation() const;
    void setUnderRenovation(bool value);

    virtual const char* getType() const = 0;

    //double calculatePrice(const ReservationContext& context) const;
};

#endif
