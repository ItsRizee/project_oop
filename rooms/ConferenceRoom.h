#ifndef CONFERENCEROOM_H
#define CONFERENCEROOM_H

#include "Room.h"

class ConferenceRoom : public Room {
private:
    double price;
public:
    ConferenceRoom(int number, bool isUnderRenovation);

    const char* GetType() const override;
    double CalculatePricePerNight(PricingStrategy* strategy) const override;
};

#endif
